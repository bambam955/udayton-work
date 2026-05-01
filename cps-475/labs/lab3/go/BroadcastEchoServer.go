/* Simple EchoServer in GoLang by Phu Phung, customized by Bennett Moore for SecAD*/
package main

import (
	"fmt"
	"net"
	"os"
)

const BUFFERSIZE int = 1024

var all_client_conns = make(map[net.Conn]string) // global
var newclient_chan = make(chan net.Conn)
var lostclient_chan = make(chan net.Conn)

func main() {
	if len(os.Args) != 2 {
		fmt.Printf("Usage: %s <port>\n", os.Args[0])
		os.Exit(0)
	}
	port := os.Args[1]
	if len(port) > 5 {
		fmt.Println("Invalid port value. Try again!")
		os.Exit(1)
	}
	server, err := net.Listen("tcp", ":"+port)
	if err != nil {
		fmt.Printf("Cannot listen on port '" + port + "'!\n")
		os.Exit(2)
	}
	fmt.Println("EchoServer in GoLang developed by Phu Phung, SecAD, revised by Bennett Moore")
	fmt.Printf("EchoServer is listening on port '%s' ...\n", port)
	go func() {
		for {
			client_conn, _ := server.Accept()
			newclient_chan <- client_conn
		}	
	}()
	for {
		select {
			case client_conn := <- newclient_chan:
				all_client_conns[client_conn] = client_conn.RemoteAddr().String()
				
				welcomeMsg := fmt.Sprintf("A new client '%s' connected!\n# of connected clients: %d\n",
					client_conn.RemoteAddr().String(), len(all_client_conns))
				fmt.Println(welcomeMsg)
				sendToAll([]byte (welcomeMsg))
				go client_routine(client_conn)

			case client_conn := <- lostclient_chan:
				delete(all_client_conns, client_conn)

				byeMsg := fmt.Sprintf("A client '%s' DISCONNECTED!\n# of connected clients: %d\n",
					client_conn.RemoteAddr().String(), len(all_client_conns))
				fmt.Println(byeMsg)
				sendToAll([]byte (byeMsg))
		}
	}
}

func client_routine(client_conn net.Conn) {
	var buffer [BUFFERSIZE]byte
	go func() {
		for {
			byte_received, read_err := client_conn.Read(buffer[0:])
			if read_err != nil {
				fmt.Println("Error in receiving...")
				lostclient_chan <- client_conn
				return
			}
			// _, write_err := client_conn.Write(buffer[0:byte_received])
			// if write_err != nil {
			// 	fmt.Println("Error in sending...")
			// 	return
			// }
			// fmt.Printf("Received data: %sEchoed back!\n", buffer)
			sendToAll(buffer[0:byte_received])
		}
	}()
}

func sendToAll(data []byte) {
	for client_conn, _ := range all_client_conns {
		_, write_err := client_conn.Write(data)
		if write_err != nil {
			fmt.Println("Error in sending...")
			continue
		}
	}
	fmt.Printf("Send data: %s to all clients!\n", data)
}
