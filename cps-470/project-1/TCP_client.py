import argparse
import socket
import sys

# Define all the arguments.
parser = argparse.ArgumentParser(description="A TCP client.")
parser.add_argument("message", help="The message to send to the server.")
parser.add_argument("server_ip", help="The IP address of the server.")
parser.add_argument("server_port", type=int, help="The port number of the server.")
parser.add_argument("connection_id", type=int, help="The 4-digit ID number for the connection.")


def try_connection(connection_id: int, args) -> bool:
    # Initialize the socket.
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.settimeout(60)
    success = False
    
    # Start the try-catch block up here to catch any errors from connect().
    try:
        client_socket.connect((args.server_ip, args.server_port))

        # Send the message to the server.
        message: str = f"{args.message} {connection_id}"
        client_socket.send(message.encode())

        # Wait for a response.
        # If we receive a message, parse it out and figure out whether the
        # connection attempt was successful or not.
        server_raw_res = client_socket.recv(1024)
        server_res = server_raw_res.decode()
        server_res_code = server_res.split()[0]
        if server_res_code == "OK":
            print(f"Connection established {connection_id} {args.server_ip} {args.server_port}")
            success = True
        elif server_res_code == "RESET":
            print(f"Connection Error: {connection_id}: received RESET")
        else:
            print(f"Unknown response code: {server_res_code}")
    
    # Handle errors for a refused connection. This can occur if the server is not running
    # when the client boots up.
    except ConnectionRefusedError:
        print(f"Connection Error: connection refused by server at {args.server_ip}:{args.server_port}")
    # Handle timeout errors on the data-receive portion of the process.
    except socket.timeout:
        print(f"Connection Error: {connection_id}: no response from server within {int(client_socket.gettimeout() or 0)} seconds")

    client_socket.close()
    # Return the result of the connection attempt.
    return success


def is_valid_cid(cid) -> bool:
    return (1000 <= cid <= 9999)


def get_valid_connection_id():
    # Iterate as many times as it takes for the user to input a proper ID.
    while True:
        try:
            cid = int(input("Enter new connection ID: "))
            if is_valid_cid(cid):
                return cid
            else:
                print("Connection ID must be a 4-digit number.")
        except ValueError:
            print("Invalid input. Please enter a number.")


def main():
    args = parser.parse_args()

    # Validate initial connection ID.
    connection_id: int = args.connection_id
    if not is_valid_cid(connection_id):
        print(f"Invalid connection ID {connection_id}. Must be a 4-digit number.")
        connection_id = get_valid_connection_id()

    # Attempt a connection 3 times before declaring it a complete failure.
    for i in range(3):
        if try_connection(connection_id, args):
            sys.exit(0)

        if i < 2:
            connection_id = get_valid_connection_id()

    print("Connection Failure")
    sys.exit(1)

if __name__ == "__main__":
    main()
