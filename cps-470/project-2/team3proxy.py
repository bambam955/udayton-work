import socket
from urllib.parse import urlparse
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
    # Print the received message.
    print(f"\n{message}")

    # Extract the desired filename from the given message.
    try:
        requested_url = message.split()[1]
    except IndexError:
        cli_sock.close()
        continue
    # Handle browser requests where the URL is prefixed with /.
    # We need to manually specify the HTTP protocol here.
    if requested_url.startswith('/'):
        url_to_parse = 'http:/' + requested_url
    else:
        url_to_parse = requested_url
    print('Requested URL:', url_to_parse)
    parsed_url = urlparse(url_to_parse)
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
    
    # The file wasn't cached...we'll need to fetch it from the real server.
    except FileNotFoundError:
        try:
            # Create a socket on the proxy server for requesting the file from the real web server.
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

            # Read and parse response headers. These come through first.
            response_headers = {}
            status_line = req_sock_stream.readline().decode().strip() # The very first line, before the headers
            while True:
                line = req_sock_stream.readline().decode().strip()
                if not line:
                    break
                if ': ' in line:
                    key, value = line.split(': ', 1)
                    # Save the header key-value pair to the dictionary
                    response_headers[key.lower()] = value

            # Check the Content-Length header.
            content_length = int(response_headers.get('content-length', 0))
            print(f'Content-Length: {content_length}')

            # Send status and headers to client.
            cli_sock.sendall((status_line + '\r\n').encode())
            for key, value in response_headers.items():
                cli_sock.sendall(f'{key}: {value}\r\n'.encode())
            cli_sock.sendall(b'\r\n')

            # Read and send body based on Content-Length, if available.
            # Doing this ensures that we read the exact amount of bytes needed, no more, no less,
            # which prevents the read() call from blocking.
            # Write everything in the body to the cache file.
            cache_file = open(cache_filename, "wb")
            if content_length > 0:
                bytes_read = 0
                while bytes_read < content_length:
                    chunk_size = min(1024, content_length - bytes_read)
                    data = req_sock_stream.read(chunk_size)
                    if not data:
                        break
                    cli_sock.sendall(data)
                    cache_file.write(data)
                    bytes_read += len(data)
            else:
                # If the Content-Length header wasn't specified then just read until there is no more data.
                while True:
                    data = req_sock_stream.read(1024)
                    if not data:
                        break
                    cli_sock.sendall(data)
                    cache_file.write(data)
            
            cache_file.close()
            req_sock_stream.close()
            req_sock.close()
            print('\033[1;32mRetrieved from web server!\033[0m')
        
        except Exception as e:
            print(f"\033[1;31mIllegal request: {e}\033[0m")
            cli_sock.sendall(("HTTP/1.1 404 Not Found\r\n\r\n").encode())  
    
    # For some reason there was an error while reading the cached file or sending it back.
    # Just return a 404.
    except IOError:
        cli_sock.sendall("HTTP/1.1 404 Not Found\r\n\r\n".encode())

    # Close up the client socket.
    cli_sock.close()
