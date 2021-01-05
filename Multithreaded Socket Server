import socket
import os
from _thread import *
from threading import Thread


#Create the server socket 
ServerSideSocket = socket.socket()
host = '127.0.0.1'
port = 2004
ThreadCount = 0
try:
    ServerSideSocket.bind((host, port))
except socket.error as e:
    print(str(e))

print('Socket is listening..')
ServerSideSocket.listen(5)

#clientDict is used to keep clients in their proper group and resolve a bug related to variable values being changed across threads
clientDict = {}

#Create several lists that will be used to sort clients into the appropriate message groups based on the type of messages for which they register. 
msgType1 = []
msgType2 = []
msgType3 = []
#Maintain one master list of all clients currently connected to the server
activeClients = []

#Message Group 1 consists of every client which registered for Message Type 1. Every client except for the sender will receive each message.
#If a message's sender is the only client in the group, the message will be effectively discarded because it has no valid recipient 
def MsgGroup1(data,connection, msgType1):
    try:
        message = '< ' + address[0] + ' > : ' + data.decode('utf-8')
        
        for clients in msgType1:
            if clients != connection:
                clients.send(str.encode(message))
    except:
        connection.close()
 #Message Group 2 operates in the same way as Message Group 1
def MsgGroup2(data,connection, msgType2):
    try:
        message = '< ' + address[0] + ' > : ' + data.decode('utf-8')
    
        for clients in msgType2:
            if clients != connection:
                clients.send(str.encode(message))
    except:
        connection.close()
#Message Group 3 operates in the same way as Message Group 1 and 2
def MsgGroup3(data,connection, msgType3):
    try:
        message = '< ' + address[0] + ' > : ' + data.decode('utf-8')
  
        for clients in msgType3:
            if clients != connection:
                clients.send(str.encode(message))
    except:
        connection.close()
#Each new client that connects to the server is given its own thread so that the server can act as a switchboard for multiple clients
def multi_threaded_client(connection): 
    #Immediately prompt the client to register for a message type: either 1, 2, or 3
    Client.send(str.encode(' Enter Client Message Type: '))
    #Store the client's chosen message type in a variable so the client can be added to the correct group
    clientMsgTypes = Client.recv(1024)
    clientMsgTypes = clientMsgTypes.decode('utf-8')
    clientDict[ThreadCount] = clientMsgTypes

    #Add the new client to a message-type group so they can interface with other clients who registered for the same message type
    if clientDict[ThreadCount] == '1':
        msgType1.append(Client)
    elif clientDict[ThreadCount] == '2':
        msgType2.append(Client)
    elif clientDict[ThreadCount] == '3':
        msgType3.append(Client)
    
    while True:
        #The server listens for a message from the client. When it receives one, it checks to see what Message Group the client is in
        #and then passes the data to the appropriate Message Group function above so that the message can be sent to the other clients in the same group.
        data = connection.recv(2048)
        
        if data.decode('utf-8')=="Exit":
            connection.close()
            break
        if clientMsgTypes == "1":
            MsgGroup1(data,connection, msgType1)
        elif clientMsgTypes == "2":
            MsgGroup2(data,connection, msgType2)
        elif clientMsgTypes == "3":
            MsgGroup3(data,connection, msgType3)

        if not data:
            break
        
    connection.close()
    
while True:
    #Accept the connection from the client
    Client, address = ServerSideSocket.accept()
    print('Connected to: ' + address[0] + ':' + str(address[1]))

    #Add the new client to the master list of all connected clients
    activeClients.append(Client)
    
    #Create a new thread for the newly-connected client and then resume listening for more connections
    start_new_thread(multi_threaded_client, (Client, ))
    ThreadCount += 1
    print('Thread Number: ' + str(ThreadCount))
   
ServerSideSocket.close()

