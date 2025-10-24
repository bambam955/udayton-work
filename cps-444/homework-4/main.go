package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"sync"
	"time"
)

func main() {
	// Read in the names of the philosophers.
	scanner := bufio.NewScanner(os.Stdin)
	var philoNames []string
	fmt.Println("Enter philosopher names (^D to end): ")
	for scanner.Scan() {
		text := scanner.Text()
		philoNames = append(philoNames, strings.TrimSpace(text))
	}

	// Invite the philosophers to dinner!
	dinnertime(philoNames)
}

func dinnertime(names []string) {
	// Wait for a second before starting everything...
	time.Sleep(1 * time.Second)
	fmt.Println("Dinner started!")

	// Create all of the chopsticks.
	var table []*Chopstick
	for range len(names) {
		table = append(table, new(Chopstick))
	}

	// This channel will be used to tell the philosophers dinner is over.
	// All we have to do is close it and they'll know.
	kill := make(chan struct{})

	// This WaitGroup will be used to make sure no philosophers get left behind when dinner is over.
	var wg sync.WaitGroup
	wg.Add(len(names))

	// Say hello to the philosophers!
	for i, name := range names {
		p := new(Philosopher)
		// Tell them which chopsticks to use
		p.Init(name, table[i], table[(i+1)%len(names)])
		// Have them sit at the table and get ready to eat
		go p.Dine(kill, &wg)
	}

	// Dinner lasts for 10 seconds. It's pretty short.
	time.Sleep(10 * time.Second)

	// Dinner is over! Everybody stop eating!!!
	close(kill)
	wg.Wait()
	fmt.Println("Dinner is over!")
}
