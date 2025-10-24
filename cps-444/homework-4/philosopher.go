package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Philosopher struct {
	index          int
	Name           string
	table          *Table
	leftChopstick  *Chopstick
	rightChopstick *Chopstick
	timesAte       int
}

func (p *Philosopher) Init(index int, name string, table *Table, left, right *Chopstick) {
	p.index = index
	p.Name = name
	p.table = table
	p.leftChopstick = left
	p.rightChopstick = right
}

func (p *Philosopher) Dine(w *sync.WaitGroup) {
	defer w.Done()

	p.log("is seated")

	for p.table.IsSet {
		p.eat()
		p.think()
	}

	p.log(fmt.Sprintf("ate %d times.", p.timesAte))
}

var waiterMutex sync.Mutex

func (p *Philosopher) eat() {
	p.log("is hungry")

	waiterMutex.Lock()

	p.leftChopstick.PickUp()
	p.rightChopstick.PickUp()
	defer p.leftChopstick.PutDown()
	defer p.rightChopstick.PutDown()

	waiterMutex.Unlock()

	p.log("started eating")
	time.Sleep(time.Duration(rand.Intn(4)+1) * 100 * time.Millisecond)
	p.timesAte++
}

func (p *Philosopher) think() {
	p.log("is thinking")
	time.Sleep(time.Duration(rand.Intn(4)+1) * 100 * time.Millisecond)
}

// This mutex allows for serialization of logging from all the philosophers.
var logMutex sync.Mutex

func (p *Philosopher) log(output string) {
	logMutex.Lock()
	defer logMutex.Unlock()
	fmt.Printf("%-10s %s\n", p.Name, output)
}
