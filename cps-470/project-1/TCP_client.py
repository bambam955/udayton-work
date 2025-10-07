import argparse
import socket
import sys

# Parse all the arguments.
parser = argparse.ArgumentParser(description="A TCP client.")
parser.add_argument("message", help="The message to send to the server.")
parser.add_argument("server_ip", help="The IP address of the server.")
parser.add_argument("server_port", type=int, help="The port number of the server.")
parser.add_argument("connection_id", type=int, help="The ID number for the connection.")
args = parser.parse_args()


def tryConnection(connectionId: int) -> bool:
    # Initialize the socket.
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.settimeout(60)
    clientSocket.connect((args.server_ip, args.server_port))

    # Send the message to the server.
    message: str = f"{args.message} {connectionId}"
    clientSocket.send(message.encode())

    # Wait for a response.
    success = False
    try:
        # If we receive a message, parse it out and figure out whether the
        # connection attempt was successful or not.
        serverRawResp = clientSocket.recv(1024)
        serverResp = serverRawResp.decode()
        serverRespCode = serverResp.split(' ', 1)[0]
        if serverRespCode == "OK":
            print(f"Connection established {connectionId} {args.server_ip} {args.server_port}")
            success = True
        elif serverRespCode == "RESET":
            print(f"Connection Error {connectionId}")
        else:
            print(f"Unknown response code: {serverRespCode}")
    except socket.timeout:
        print(f"Error: No response from server within {int(clientSocket.timeout)} seconds")
    
    clientSocket.close()
    # Return the result of the connection attempt.
    return success


# Attempt a connection 3 times before declaring it a complete failure.
connectionId = args.connection_id
for i in range(3):
    if tryConnection(connectionId):
        sys.exit(0)
    elif i < 2:
        try:
            connectionId = int(input("Enter a new connection ID: "))
        except ValueError:
            print("Invalid input.")
            sys.exit(1)

print("Connection Failure")
sys.exit(1)
