// Adapted from:
// https://mariusbancila.ro/blog/2017/01/16/dining-philosophers-in-cpp11/

#include <array>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <string_view>

constexpr int no_of_philosophers = 5;

// A "fork" represents a shared resource that the philosophers have to share.
// This is easily implemented as a mutex, so that the fork can be "picked up" by locking it.
struct fork
{
    std::mutex mutex;
};

// The table contains the array of forks, plus a flag to let the philosophers know when to start and stop eating.
struct table
{
    std::atomic<bool> is_set{false};
    std::array<fork, no_of_philosophers> forks;
};

// A "philosopher" represents a concurrent task that is running.
// For as long as the table is set, a philosopher will go back and forth between eating and thinking.
struct philosopher
{
private:
    std::string const name;
    table const &dinnertable;
    fork &left_fork;
    fork &right_fork;
    std::thread lifethread;
    std::mt19937 rng{std::random_device{}()};
    int times_ate = 0;

public:
    philosopher(std::string n, table const &t, fork &l, fork &r) : name(n), dinnertable(t), left_fork(l), right_fork(r),
                                                                   lifethread(&philosopher::dine, this)
    {
    }
    // Merge the sub-thread back into the main thread.
    ~philosopher()
    {
        lifethread.join();
    }

    void print(std::string text)
    {
        // This mutex is used to serialize prints. Without this lock, the output
        // from multiple philosophers may become jumbled together.
        static std::mutex print_mutex;
        std::lock_guard<std::mutex> cout_lock(print_mutex);
        std::cout << std::left << std::setw(10) << std::setfill(' ')
                  << name << text << std::endl;
        // cout_lock is automatically destructed here and releases print_mutex
    }

    // Eat and think in a continuous loop once the table has been set.
    void dine()
    {
        while (!dinnertable.is_set)
            ;
        do
        {
            eat();
            think();
        } while (dinnertable.is_set);
        
        // Debug how many times the philsopher got to eat in his lifetime.
        print(" ate " + std::to_string(times_ate) + " times.");
    }
    
    // When a philosopher "eats", he must get access to TWO forks (shared resources) from the table.
    // However, first he must get permission to eat from the "waiter", which is a shared mutex among
    // all the threads that makes it so only one philosopher can be eating at a time.
    void eat()
    {
        // This mutex acts a waiter. It effectively prevents more than one philosopher from picking up forks at a time.
        // THESE ARE THE TWO LINES I ADDED!!!
        static std::mutex waiter_mutex;
        std::lock_guard<std::mutex> eat_lock(waiter_mutex);

        static thread_local std::uniform_int_distribution<> dist(1, 6);

        left_fork.mutex.lock();
        print(" acquired left fork");
        
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng) * 50));

        right_fork.mutex.lock();
        print(" acquired right fork");

        std::lock_guard<std::mutex> left_lock(left_fork.mutex, std::adopt_lock);
        std::lock_guard<std::mutex> right_lock(right_fork.mutex, std::adopt_lock);

        print(" started eating.");
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng) * 50));
        print(" finished eating.\n");
        times_ate++;

        // left_lock and right_lock are automatically destructed here 
        // and release their respective mutexes
    }

    // Put the thread to sleep for some time while the philosopher "thinks"
    // (does other tasks not involving the shared resources).
    void think()
    {
        static thread_local std::uniform_int_distribution<> wait(1, 6);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 150));
        print(" is thinking ");
    }
};

void dine()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Dinner started!" << std::endl;
    {
        table table;
        std::array<philosopher, no_of_philosophers> philosophers{
            {
                {"Aristotle", table, table.forks[0], table.forks[1]},
                {"Descartes", table, table.forks[1], table.forks[2]},
                {"Kant", table, table.forks[2], table.forks[3]},
                {"Nietzsche", table, table.forks[3], table.forks[4]},
                {"Plato", table, table.forks[4], table.forks[0]},
            }};
        table.is_set = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        table.is_set = false;
    }
    std::cout << "Dinner done!" << std::endl;
}

int main()
{
    dine();
    return 0;
}
