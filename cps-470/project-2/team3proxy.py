import argparse
import socket
import sys

# Define all the arguments.
parser = argparse.ArgumentParser(description="A TCP-based proxy web server.")
parser.add_argument("server_ip", required=True, help="The IP address of the proxy server.")
parser.add_argument("server_port",required=True, type=int, help="The port number of the server.")

def main():
    args = parser.parse_args()

    # Create a server socket, bind it to a port and start listening
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
    server_socket.bind(("", args.server_port))
    server_socket.listen(1)

    # Begin waiting for connections.
    while True:
        # Start receiving data from the client
        print('Ready to serve...')
        tcp_cli_sock, addr = server_socket.accept()
        print('Received a connection from:', addr)
        message = tcp_cli_sock.recv(1024).decode()
        print(message)

        # Extract the filename from the given message
        print(message.split()[1])
        filename = message.split()[1].partition("/")[2]
        print(filename)

        fileExist = "false"
        fileToUse = "./" + filename
        print(fileToUse)

        try:
            # Check whether the file exists in the cache
            f = open(fileToUse[1:], "r")
            outputData = f.readlines()
            fileExist = "true"

            # Proxy server finds a cache hit and generates a response message
            tcp_cli_sock.send("HTTP/1.0 200 OK\r\n")
            tcp_cli_sock.send("Content-Type:text/html\r\n")

            # Fill in start.
            # Fill in end.

            print('Read from cache')
        # Error handling for file not found in cache
        except IOError:
            if fileExist == "false":
                # Create a socket on the proxy server
                c = "" # fill in start. fill in end.
                hostn = filename.replace("www.", "", 1)
                print(hostn)
                try:
                    # Connect the socket to port 80
                    # Fill in start. fill in end.
                    # Create a temporary file on this socket and ask port 80 for the file requested by the client.
                    fileObj = c.makefile('r', 0)
                    fileObj.write("GET    " + "http://" + filename + "HTTP/1.0\n\n")
                    # Read the response into buffer
                    # Fill in start. fill in end.
                    # Create a new file in the cache for the requested file.
                    # Also send the response in the buffer to client socket and the corresponding file in the cache.
                    tmpFile = open("./" + filename, "wb")
                    # Fill in start. fill in end.
                except:
                    print("Illegal request")
            else:
                # HTTP response message for file not found
                # Fill in start. Fill in end.
                pass
        
        tcp_cli_sock.close()

# Fill in start.
# Fill in end.
