import argparse
import socket
import sys

# Define all the arguments.
parser = argparse.ArgumentParser(description="A UDP client.")
parser.add_argument("message", help="The message to send to the server.")
parser.add_argument("server_ip", help="The IP address of the server.")
parser.add_argument("server_port", type=int, help="The port number of the server.")
parser.add_argument("connection_id", type=int, help="The 4-digit ID number for the connection.")


def try_connection(connection_id: int, args) -> bool:
    # Initialize the socket.
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.settimeout(60)

    # Send the message to the server.
    message: str = f"{args.message} {connection_id}"
    client_socket.sendto(message.encode(), (args.server_ip, args.server_port))

    # Wait for a response.
    success = False
    try:
        # If we receive a message, parse it out and figure out whether the
        # connection attempt was successful or not.
        server_raw_res, server_address = client_socket.recvfrom(2048)
        server_res = server_raw_res.decode()
        server_res_code = server_res.split()[0]
        if server_res_code == "OK":
            print(f"Connection established {connection_id} {server_address[0]} {server_address[1]}")
            success = True
        elif server_res_code == "RESET":
            print(f"Connection Error {connection_id}")
        else:
            print(f"Unknown response code: {server_res_code}")
    except socket.timeout:
        print(f"Error: No response from server within {int(client_socket.gettimeout() or 0)} seconds")
    
    client_socket.close()
    # Return the result of the connection attempt.
    return success


def is_valid_cid(cid) -> bool:
    return (1000 <= cid <= 9999)


def get_valid_connection_id():
    # Iterate as many times as it takes for the user to input a proper ID.
    while True:
        try:
            cid = int(input("Enter a new connection ID: "))
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
            print("Connection failed. Enter a new 4-digit connection ID.")
            connection_id = get_valid_connection_id()

    print("Connection Failure")
    sys.exit(1)

if __name__ == "__main__":
    main()
