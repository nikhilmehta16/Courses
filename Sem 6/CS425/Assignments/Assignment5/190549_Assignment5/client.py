"""
Run server.py before client.py
Use python3 to start the server
Use only 1 server side and as many client on server
"""

import socket
import select
from sys import *

serverPort = 12001
host_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
host_server.connect(('localhost', serverPort))

while True:

	sockets_list = [stdin, host_server]

	read_sockets,write_socket, error_socket = select.select(sockets_list,[],[])
    # print (read_sockets)
	for socks in read_sockets:
		if socks == host_server:
			message = socks.recv(2048)
			print (message.decode())
		else:
			message = stdin.readline()
			host_server.send(message.encode())
			stdout.write("You-->")
			stdout.write(message)
			stdout.flush()
server.close()
