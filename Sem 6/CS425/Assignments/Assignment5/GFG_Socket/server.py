
import socket
from _thread import *

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serverPort = 12001
server.bind(("localhost", serverPort))
server.listen()

list_of_clients = []

def clientthread(conn, addr):
    send_str = "Welcome "+addr[0]+" to chat-server" 
    conn.send(send_str.encode())

    while True:
            try:
                message = conn.recv(2048).decode()
                if message:
                    
                    print (addr[0] + "--> " + message)

                    message_to_send = addr[0] + "-->" + message
                    for clients in list_of_clients:
                        if clients!=conn:
                            try:
                                clients.send(message_to_send.encode())
                            except:
                                clients.close()
                                if conn in list_of_clients:
                                    list_of_clients.remove(conn)

                else:
                    print("Connection removed: ",conn)
                    if conn in list_of_clients:
                        list_of_clients.remove(conn)
                    break

            except:
                continue

while True:
	conn, addr = server.accept()
	list_of_clients.append(conn)
	print (addr[0] + " Connected :)")
	start_new_thread(clientthread,(conn,addr))	

conn.close()
server.close()
