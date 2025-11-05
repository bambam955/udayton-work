import socket
from urllib.parse import urlparse
import sys
import argparse

# Define all the arguments.
parser = argparse.ArgumentParser(description="A TCP-based proxy web server.")
parser.add_argument("server_ip", help="The IP address of the proxy server.")
parser.add_argument("server_port", type=int, help="The port number of the server.")
args = parser.parse_args()

# Create a server socket, bind it to the given IP address and port, and start listening.
server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_sock.bind((args.server_ip, args.server_port))
server_sock.listen(1)

while True:
    # Wait to receive a request from a client.
    print('\n\033[1;36m================= READY TO SERVE =================\033[0m')
    cli_sock, addr = server_sock.accept()
    print('Received connection from:', addr)
    message = cli_sock.recv(1024).decode()
    if not message:
        cli_sock.close()
        continue
    # Print the message.
    print(f"\n{message}")

    # Extract the desired filename from the given message.
    # TODO: make this work with browsers and not just CURL.
    try:
        requested_url = message.split()[1]
    except IndexError:
        cli_sock.close()
        continue
    parsed_url = urlparse(requested_url)
    raw_filename = (parsed_url.netloc + parsed_url.path)
    print('Requested file:', raw_filename)
    cache_filename = raw_filename.replace("/", "_").replace(":", "_")
    
    # Check whether the requested file is cached. If it is we can return it immediately.
    try:
        f = open(cache_filename, "rb")
        outputdata = f.read()
        f.close()
        # We found the file! Send a response message, including the cached file.
        cli_sock.sendall(("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n").encode())
        cli_sock.sendall(outputdata)
        print('\033[1;32mRead from cache!\033[0m')
    
    # The file wasn't cached...
    except FileNotFoundError:
        try:
            # Create a socket on the proxy server for requesting the file from the actual web server.
            req_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

            # Figure out the exact hostname and port number to use.
            hostn = parsed_url.netloc  
            path = parsed_url.path     
            if path == "":
                path = "/"
            print(f'Connecting to {hostn}...')
            port = 80
            if ":" in hostn:
                host, port_str = hostn.split(":", maxsplit=1)
                port = int(port_str)
            else:
                host = hostn
            
            # Connect the request socket.
            req_sock.connect((host, port))

            # Create a temporary file on this socket and ask for the file requested by the client.
            req_sock_stream = req_sock.makefile('rwb' , buffering = 0)
            req_sock_stream.write(("GET " + path + " HTTP/1.1\r\nHost: " + hostn + "\r\n\r\n").encode())
            req_sock_stream.flush()
            
            # Read data from the request socket until the entire file has been received.
            # As data is received, write it to both the new cached file and the socket between the proxy and the client.
            cache_file = open(cache_filename, "wb")
            while True:
                data = req_sock_stream.read(1024)
                if data:
                    cli_sock.sendall(data)
                    cache_file.write(data)
                else:
                    break
            cache_file.close()
            req_sock_stream.close()
            req_sock.close()
        
        except Exception as e:
            print(f"Illegal request: {e}")
            cli_sock.sendall(("HTTP/1.1 404 Not Found\r\n\r\n").encode())  
    
    # For some reason there was an error while reading the cached file or sending it back.
    # Just return a 404.
    except IOError:
        cli_sock.sendall("HTTP/1.1 404 Not Found\r\n\r\n".encode())

    # Close up the client socket.
    cli_sock.close()
