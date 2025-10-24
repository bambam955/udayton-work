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
	time.Sleep(1 * time.Second)
	fmt.Println("Dinner started!")

	var table []*Chopstick
	for range len(names) {
		table = append(table, new(Chopstick))
	}

	kill := make(chan struct{})

	var wg sync.WaitGroup
	wg.Add(len(names))
	for i, name := range names {
		p := new(Philosopher)
		p.Init(name, table[i], table[(i+1)%len(names)])
		go p.Dine(kill, &wg)
	}

	time.Sleep(10 * time.Second)
	close(kill)
	wg.Wait()
	fmt.Println("Dinner is over!")
}
