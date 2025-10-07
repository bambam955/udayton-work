import argparse
import socket
import time
import threading
import sys

parser = argparse.ArgumentParser(description="A TCP server.")
parser.add_argument("server_ip", help="The IP address of the server.")
parser.add_argument("server_port", type=int, help="The port number of the server.")
args = parser.parse_args()


connectionIDs = {}

def connIdsCleaup():
    while True:
        time.sleep(5)
        current = time.time()
        to_remove = [k for k, v in connectionIDs.items() if current - v >= 60]
        for k in to_remove:
            del connectionIDs[k]

threading.Thread(target=connIdsCleaup, daemon=True).start()


def restartConnTimer():
    conn_timer = threading.Timer(300, sys.exit, args=(1,))
    conn_timer.start()
conn_timer = threading.Timer(300, sys.exit, args=(1,))


serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind(('', args.server_port))
serverSocket.listen(1)
while True:
    connectionSocket, addr = serverSocket.accept()
    clientMsg = connectionSocket.recv(1024).decode()

    clientConnId = int(clientMsg.split(' ', 1)[1])

    restartConnTimer()

    response = ""
    if clientConnId not in connectionIDs:
        connectionIDs[clientConnId] = time.time()
        response = f"OK {clientConnId} {addr[0]} {addr[1]}"
    else:
        response = f"RESET {clientConnId}"

    connectionSocket.send(response.encode())
    connectionSocket.close()
