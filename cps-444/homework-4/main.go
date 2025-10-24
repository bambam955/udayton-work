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
	scanner := bufio.NewScanner(os.Stdin)
	var philoNames []string
	fmt.Println("Enter philosopher names (^D to end): ")

	for scanner.Scan() {
		text := scanner.Text()
		philoNames = append(philoNames, strings.TrimSpace(text))
	}

	// Set the table for the philosophers to start dining
	dinnertime(philoNames)
}

func dinnertime(names []string) {
	time.Sleep(1 * time.Second)
	fmt.Println("Dinner started!")

	table := new(Table)

	for range len(names) {
		table.Chopsticks = append(table.Chopsticks, new(Chopstick))
	}
	table.IsSet = true

	var wg sync.WaitGroup
	for i, name := range names {
		p := new(Philosopher)
		p.Init(i, name, table, table.Chopsticks[i], table.Chopsticks[(i+1)%len(names)])

		wg.Add(1)
		go p.Dine(&wg)
	}

	time.Sleep(10 * time.Second)
	table.IsSet = false
	wg.Wait()
	fmt.Println("Dinner is over!")
}
