package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Philosopher struct {
	Name string
	// Tell the philosopher which chopsticks to use.
	// Left vs right is arbitrary, there just has to be two.
	leftChopstick  *Chopstick
	rightChopstick *Chopstick
	// Track how many times a philosopher eats. It's fun to see who the glutton is...
	timesAte int
}

// Who am I?
func (p *Philosopher) Init(name string, left, right *Chopstick) {
	p.Name = name
	p.leftChopstick = left
	p.rightChopstick = right
}

// Tell the philosopher to begin dining.
// The stop channel is how he knows when dinner is done,
// and the WaitGroup is how the host knows when the philosopher leaves.
func (p *Philosopher) Dine(stop <-chan struct{}, w *sync.WaitGroup) {
	defer w.Done()

	// Log that the philosopher sat down at the table and is ready to eat.
	p.log("is seated")

	// This loop runs forever until the host ends dinner.
	for {
		select {
		// If there is a stop signal, then leave the table.
		case <-stop:
			p.log(fmt.Sprintf("satisfied. Meals eaten: %d.", p.timesAte))
			p.log("left the table.")
			return
		// Eat and then think, over and over again as long as there's no stop signal.
		default:
			p.eat()
			p.think()
		}
	}
}

// This waiter makes sure that philosophers pick up their chopsticks in an orderly manner.
// We would not want a philosopher to pick up the left chopstick and then get beaten by
// another philosopher to the right chopstick, as the result would be all philosophers holding
// a left chopstick and no one able to eat.
var waiterMutex sync.Mutex

func (p *Philosopher) eat() {
	// He's waiting on the waiter to tell him to pick up chopsticks...
	p.log("is hungry")
	waiterMutex.Lock()

	// The waiter approved! Pick up both chopsticks, then notify the waiter he can
	// go serve someone else.
	p.leftChopstick.PickUp()
	p.rightChopstick.PickUp()
	defer p.leftChopstick.PutDown()
	defer p.rightChopstick.PutDown()
	waiterMutex.Unlock()

	// Time to eat! Some eat faster than others.
	p.log("started eating")
	time.Sleep(time.Duration(rand.Intn(4)+1) * 100 * time.Millisecond)
	// Keep track of meal count.
	p.timesAte++
}

// After philosophers eat, they now have enough energy to think.
// Some are more philosophical than others and think for longer periods of time...
func (p *Philosopher) think() {
	p.log("is thinking")
	time.Sleep(time.Duration(rand.Intn(4)+1) * 100 * time.Millisecond)
}

// We have to make sure the philosophers don't talk over each other,
// or else we end up with a very jumbled conversation.
var logMutex sync.Mutex

func (p *Philosopher) log(output string) {
	logMutex.Lock()
	defer logMutex.Unlock()
	fmt.Printf("%-10s %s\n", p.Name, output)
}
