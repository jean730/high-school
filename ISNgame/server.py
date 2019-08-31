#!/bin/python3
import socket
import time
PORT=9996
sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
udpsock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind(("0.0.0.0",PORT))
udpsock.bind(('',PORT))
sock.setblocking(False)
udpsock.setblocking(False)
sock.listen(5)
connections=[]
tcpbuffers=[]
udpconnections=[]
addresses=[]
udpaddresses=[]
names=[]
while True:
    Clock = time.time()
###TCP###

    ##CONNECTION##
    try:
        connection,address = sock.accept()
        connection.setblocking(True)
        connections.append(connection)
        tcpbuffers.append("")
        #Get User Name#
        name = connection.recv(20).decode()
        names.append(name)
        print("New user:",name)
        connection.setblocking(False)
    
    ##No new user##
    
    except Exception as e:
        pass

    for i in connections:
        try:

    ##RECEIVE##
            tcpbuffers[connections.index(i)]=""
            canReceive=True
            while canReceive:
                try:
                    data=i.recv(1024).decode()
                    if data=="":
                        canReceive=False
                    else:
                        tcpbuffers[connections.index(i)]+=data
                except Exception as e:
                    canReceive=False


    ##PARSE TCP BUFFER##
            splittedbuffer = tcpbuffers[connections.index(i)].split(";")
            for buff in splittedbuffer:
                if buff!="":
        ##SEND##
                    print(buff)
                    for j in connections:
                        try:
                            j.send((names[connections.index(i)]+":"+buff+";").encode())
                        except:
                            #joueur déco :)
                            pass
        except Exception as e:
            #print(e)
            pass


###UDP###
    canReceive=True
    while(canReceive):
        try:
            data,addr = udpsock.recvfrom(1024)
            #print(data)
    ##CONNECTION##

            if data.decode()=="connect":
                udpconnections.append(addr)
                print("New UDP connection :",udpconnections)
            else:

    ##RECEIVE then SEND##
                client=0
                sender=udpconnections.index(addr)
                for i in udpconnections:
                    client=udpconnections.index(i)
                    udpsock.sendto((names[sender]+":"+data.decode()+";").encode(),i)
                    #print(names[client]+":"+data.decode()+";",i)

    #No data nor new connection#

        except Exception as e:
            #print(e)
            canReceive=False
            pass


    try:
        #print(round(0.01-(time.time()-Clock),4))
        time.sleep(0.01-(time.time()-Clock))
    except:
        print("Sleeping",time.time()-Clock,"seconds is impossible.\
              The program is not capable of time travel")
        pass

