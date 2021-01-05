import socket
from threading import Thread
import sys

ClientMultiSocket = socket.socket()

host = '127.0.0.1'
port = 2004

print('Waiting for connection response')
#Connect to the server which is listening for connections
try:
    ClientMultiSocket.connect((host, port))
except socket.error as e:
    print(str(e))
#The "sendMessage" function is used for prompting the user for input, encoding the messsage, and then passing it along to the server
def sendMessage():
    while True:
        print("\n>Send Message: \n")
        Input = input()
        if Input:
            ClientMultiSocket.send(str.encode(Input))
            print(">Message Sent!")
#The "receiveMessages" function listens for input from the server as it passes along messages from other clients in the same message-type group
#It runs on a separate thread to allow the client to send and receive messages concurrently
def receiveMessage():
    while True:
        
        message = ClientMultiSocket.recv(1024).decode('utf-8')
        if not message:
            sys.exit(0)
        else:
            print("\n***New Message Received: ", message)
            #The following print statement was added for improved formatting
            print("\n>Send Message: \n")

#Upon connection to the server, the server immediately prompts the client to register for the "type" of messages it will send and receive. 
#For simplicity, there are only 3 accepted message "types", and these are represented by the integers 1, 2, and 3. 
#Currently, a client may register for only one message type.     
clientMsgType = input(ClientMultiSocket.recv(1024).decode('utf-8'))
ClientMultiSocket.send(str.encode(clientMsgType))

#Activate the thread for receiveMessages so that the client can listen for messages from other clients while sending messages of its own
Thread(target=receiveMessage, args=( )).start()

while True:
    sendMessage()

ClientMultiSocket.close()
