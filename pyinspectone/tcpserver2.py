#!/usr/bin/python3
import socket
import _thread
import sys, time

class SocketServer(socket.socket):
    clients = []

    def __init__(self):
        socket.socket.__init__(self)
        #To silence- address occupied!!
        self.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.bind(('0.0.0.0', int(sys.argv[3])))
        self.listen(5)

    def run(self):
        print(f"Server{sys.argv[5]} started")
        try:
            self.accept_clients()
        except Exception as ex:
            print(ex)
        finally:
            print("Server closed")
            for client in self.clients:
                client.close()
            self.close()

    def accept_clients(self):
        while 1:
            (clientsocket, address) = self.accept()
            #Adding client to clients list
            self.clients.append(clientsocket)
            #Client Connected
            self.onopen(clientsocket)
            #Receiving data from client
            _thread.start_new_thread(self.recieve, (clientsocket,))

    def recieve(self, client):
        while 1:
            time.sleep(3)
            data = client.recv(1024)
            answer = data.decode('utf-8', 'ignore').encode("utf-8")
            if data == b'':
                break 
            #Message Received
            if self.onmessage(client, answer) == 2:
                break
        #Removing client from clients list
        self.clients.remove(client)
        #Client Disconnected
        self.onclose(client)
        #Closing connection with client
        client.close()
        #Closing thread
        _thread.exit()
        print(self.clients)

    def broadcast(self, message):
        #Sending message to all clients
        for client in self.clients:
            client.send(message)

    def onopen(self, client):
        pass

    def onmessage(self, client, message):
        pass

    def onclose(self, client):
        pass

class inspectone(SocketServer):

	def __init__(self):
		SocketServer.__init__(self)

	def onmessage(self, client, message):
		print(f"client sent Message:", message.decode().strip('\n'))
		if message.decode().strip('\n').lower() ==  sys.argv[2].lower():
			client.send(b"[+]Success!\n")
			client.send(sys.argv[4].encode())
			return 1
		else:
			client.send(b"[-]Failure, disconnecting...\n")
			return 2

	def onopen(self, client):
		client.send(sys.argv[1].encode())
		client.send(b"\n")

	def onclose(self, client):
		print(f"{client.getpeername()} Disconnected")

def main():	
	if len(sys.argv) != 6:
		print(f"5 Arguments required: ./inspectone QUESTION, ANSWER, PORT, FLAG, SERVERID")
		exit()

	server = inspectone()
	server.run()

if __name__ == "__main__":
	main()
