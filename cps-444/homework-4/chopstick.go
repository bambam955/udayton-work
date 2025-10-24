package main

import "sync"

type Chopstick struct {
	mutex sync.Mutex
}

// All that really needs to happen to "pick up" a chopstick is to lock its mutex
// so that no other philosophers can pick it up at the same time.
func (c *Chopstick) PickUp() {
	c.mutex.Lock()
}

// Once a philosopher is done eating, they can put down the chopstick, which releases
// the mutex so another philosopher can use it.
func (c *Chopstick) PutDown() {
	c.mutex.Unlock()
}
