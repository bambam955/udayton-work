# Testing

1. To test that high-priority processes do indeed run before low-priority processes, run the `test_starvation` program. Verify the low-priority child never gets a chance to run.
2. To test that processes of the same priority are scheduled in round-robin order, run `test_roundrobin`. Verify that the three children run one at a time over and over again.
3. To test priority inversion, run the `test_inversion` program. Verify that the high-priority process runs AFTER the low-priority one finishes, which means the mid-priority process should run first. Steps:
  - The low-priority process gets the first chance to get the file lock while the high-priority process is sleeping
  - When the high-priority process wakes up, it blocks, because the low-priority process has the lock
  - Then, because the mid-priority process is higher priority than the low-priority process, and the high-priority process is blocked, it gets to run for as long as it wants
  - After it finishes, the low-priority process gets to run as long as _it_ wants because it's still blocking the high-priority process
  - Finally, the low-priority process finishes and releases the file lock, which allows the high-priority process to complete 
4. To test that processes of the same priority that are ready to run do in fact run, run `test_equalpriority`. Verify the processes take turns running.

# Questions

## 1. How to make scheduler run in `O(m)` time?

I think the simplest way to improve the time efficiency of the algorithm would be to store a list of runnable processes in addition to the full list of all processes. The list of runnable processes would need to be managed wherever process states are set, but assuming this is done, the scheduler could just loop through this list and thus only ever look at runnable processes.

This would result in `O(m)` performance for the scheduler, since it would be looping through runnable processes instead of all processes.

The round-robin part of the algorithm could be maintained by either using queue semantics for the list of runnable processes, or by simply ensuring that the list is sorted by process ID, since those only ever increment. The first option is preferable because of the edge case where PIDs loop back to `0`.

## 2. How to make scheduler run in `O(log m)` time?

Instead of using a simple queue of runnable processes, we can use a binary heap of processes, which has `O(log m)` complexity for insertion and deletion.

The binary heap would be a max-heap in which the structure of the heap is determined by process PRIORITY. In this way, the highest priority process will be at the top of the heap and thus will be the first process that is run. Running the process would require deletion from the heap, which would take `O(log m)` time; and reinserting the process back into the heap (if it has not exited yet) would again take `O(log m)` time.

## 3. What will happen if the process that is chosen to run does not release `ptable.lock`?

If the process that is chosen to run does not release `ptable.lock` then the entire operating system will deadlock, because now no more processes can be run. The next time the scheduler tries to run a process, it will try to acquire the lock, and it will block, which means the whole OS will block.

## 4. Based on the entire source code of `proc.c`, how can a zombie process be created?

Processes automatically go through the zombie state when `exit()` is called, but it's such a small period of time that we wouldn't ever notice. When `exit()` is called, the parent of the exiting process is made runnable, so once that parent calls `wait()` then it will take all of its zombie children and clear out the data for new processes to fill.

However, if, for whatever reason, the parent does not call `wait()` immediately, the child process will be stuck in the zombie state because `wait()` is the only function where zombie processes are cleaned up.

If the parent process exits without EVER calling `wait()` then the parent of the zombie child will be set to the `init` process, which will try to clean it up by calling `wait()` as it is supposed to (see line 65 of `init.c`). So, I don't think there is a way for processes to be left as zombies indefinitely...unless we never get around to running the `init` process again.

## 5. Does xv6 use preemptive scheduling?

Yes, xv6 does use preemptive scheduling. We know this implicitly because we've talked in class about how a process runs for 6 milliseconds and then another process gets a chance to run, which obviously means that processes are not being run until they exit. We can also see this with the `ps` command that we implemented, which shows all the process info; if we didn't have preemptive scheduling then after running `long &; long &` we would never be able to run `ps` and get any output.

We can see the mechanism for preemptive scheduling in the kernel code, specifically at line 99 of `ktrap.c`. Every time the clock registers another tick, we check to see if the state of the current process is `RUNNING`. If it is, then we call `yield()`, which sets the process state to `RUNNABLE` and saves its context, then gets the scheduler ready to go again.
