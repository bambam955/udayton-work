import argparse
import socket
import os

# Define all the arguments.
parser = argparse.ArgumentParser(description="A TCP-based proxy web server.")
parser.add_argument("server_ip", help="The IP address of the proxy server.")
parser.add_argument("server_port", type=int, help="The port number of the server.")

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

        file_path = filename
        print(file_path)

        if os.path.exists(file_path):
            # Check whether the file exists in the cache
            f = open(file_path, "r")
            file_contents = f.readlines()

            # Proxy server finds a cache hit and generates a response message
            tcp_cli_sock.send("HTTP/1.0 200 OK\r\n".encode())
            tcp_cli_sock.send("Content-Type:text/html\r\n".encode())
            tcp_cli_sock.send("".join(file_contents).encode())
            # TODO: need to send anything else back??

            print('Read from cache')

        # Error handling for file not found in cache...
        else:
            print('FILE WAS NOT IN CACHE')
            # Create a socket on the proxy server
            c_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            c_sock.settimeout(60)
            hostn = filename.split("/")[0].replace("www.", "", 1)
            path = "/" + "/".join(filename.split("/")[1:]) if "/" in filename else "/"
            print(hostn)
            print(path)

            try:
                # Connect the socket to port 80
                c_sock.connect((hostn, 80))
                # c_sock.send(message.encode())
                f = c_sock.makefile('wb', 0)
                # f.write("GET    http://" + filename + "HTTP/1.0\r\n")
                lines = message.split('\r\n')
                lines[0] = "GET " + path + " HTTP/1.0"
                for i in range(1, len(lines)):
                    if lines[i].startswith("Host: "):
                        lines[i] = "Host: " + hostn
                        break
                modified_message = "\r\n".join(lines) + "\r\n"
                f.write(modified_message.encode())
                server_raw_res = b''
                while True:
                    chunk = c_sock.recv(1024)
                    if not chunk:
                        break
                    server_raw_res += chunk
                server_res = server_raw_res.decode()
                print(server_res)
                tcp_cli_sock.send(server_raw_res)






                

                # Fill in start. fill in end.
                # Create a temporary file on this socket and ask port 80 for the file requested by the client.
                # fileObj = c.makefile('r', 0)
                # fileObj.write("GET    " + "http://" + filename + "HTTP/1.0\n\n")
                # Read the response into buffer
                # Fill in start. fill in end.
                # Create a new file in the cache for the requested file.
                # Also send the response in the buffer to client socket and the corresponding file in the cache.
                # tmpFile = open("./" + filename, "wb")
                # Fill in start. fill in end.
            except:
                print("Illegal request")
        
        tcp_cli_sock.close()

    print('CLOSING CONN SOCKET')
    server_socket.close()

# Fill in start.
# Fill in end.

main()
