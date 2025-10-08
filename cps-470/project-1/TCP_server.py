import argparse
import socket
import sys
import threading
import time

# Define all the arguments.
parser = argparse.ArgumentParser(description="A TCP server.")
parser.add_argument("server_ip", help="The IP address of the server.")
parser.add_argument("server_port", type=int, help="The port number of the server.")

connection_ids = {}

def main():
    args = parser.parse_args()
    
    # Start the background process that periodically cleans out stale connection IDs.
    threading.Thread(target=cleanup_conn_ids, daemon=True).start()

    # Initialize the server socket.
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("", args.server_port))
    server_socket.listen(1)
    # If there is no activity for 5 minutes then the server exits.
    server_socket.settimeout(5 * 60)

    # Begin waiting for connections.
    while True:
        try:
            connection_socket, client_addr = server_socket.accept()
            client_req = connection_socket.recv(1024).decode()
            client_conn_id = int(client_req.split()[1])

            res = ""
            # Check to see if the client's connection ID was used already.
            # If not, return "OK". If so, return "RESET".
            if client_conn_id not in connection_ids:
                connection_ids[client_conn_id] = time.time()
                res = f"OK {client_conn_id} {client_addr[0]} {client_addr[1]}"
            else:
                res = f"RESET {client_conn_id}"

            connection_socket.send(res.encode())
            connection_socket.close()

        # Exit the program if there is no activity.
        except socket.timeout:
            sys.exit(1)


def cleanup_conn_ids():
    while True:
        time.sleep(5)
        current = time.time()
        # Get a list of all the IDs whose timestamps are at least a minute old.
        to_remove = [k for k, v in connection_ids.items() if current - v >= 60]
        for k in to_remove:
            del connection_ids[k]


if __name__ == "__main__":
    main()
