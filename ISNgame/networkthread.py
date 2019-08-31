from stepdebug import *
import threading
import socket
import time
class network(threading.Thread):
    def __init__(self,gameObject):
        threading.Thread.__init__(self)
        self.debug = StepDebug()
        self.debug.prefix="Network: "
        self.debug.enabled(False)
        self.gameObject = gameObject
        sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.tcpbuffer=""
        udpsock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        try:
            sock.connect((self.gameObject.Address,self.gameObject.Port))
            sock.send(self.gameObject.localPlayer.Name.encode())
            sock.setblocking(False)
            self.gameObject.socket = sock
            udpsock.sendto("connect".encode(),(self.gameObject.Address,self.gameObject.Port))
            udpsock.setblocking(False)
            self.gameObject.udpsocket = udpsock
            print(udpsock)
            time.sleep(1)
        except Exception as e:
            print("Failed to connect :",e)
    def run(self):
        while self.gameObject.Running:
            TCPsendBuffer=""
            UDPsendBuffer=""
            self.tcpbuffer=""
            self.udpbuffer=""
            Clock = time.time()
            self.debug.resetsteps()
            #print("Network ",self.gameObject)
            if self.gameObject.RenderOutStream!="":
                for i in self.gameObject.RenderOutStream.split(";"):
                    if i!="":
                        TCPsendBuffer+="r:"+i+";"
            if self.gameObject.PhysicsOutStream!="":
                for i in self.gameObject.PhysicsOutStream.split(";"):
                    if i!="":
                        UDPsendBuffer+="p:"+i+";"
            self.gameObject.RenderOutStream=""
            self.gameObject.PhysicsOutStream=""
            self.gameObject.socket.send(TCPsendBuffer.encode())
            self.gameObject.udpsocket.sendto(UDPsendBuffer.encode(),(self.gameObject.Address,self.gameObject.Port))
            #print("Running")
            self.debug.step()
            canReceive=True
            while(canReceive):
                try:
                    self.udpbuffer+=self.gameObject.udpsocket.recvfrom(1024)[0].decode()
                    splittedbuffer = self.udpbuffer.split(";")
                    for buff in splittedbuffer:
                        if buff!="":
                            data=buff.split(":")
                            if self.gameObject.localPlayer.Name != data[0] and data[1]=="p":
                                self.gameObject.PhysicsInStream+=data[0]+":"+data[2]+";"
                except Exception as e:
                    canReceive=False
            try:
                self.debug.step()
                self.tcpbuffer+=self.gameObject.socket.recv(1024).decode()

                splittedbuffer = self.tcpbuffer.split(";")
                for buff in splittedbuffer:
                    if buff!="":
                        data=buff.split(":")
                        if self.gameObject.localPlayer.Name != data[0] and data[1]=="r":
                            self.gameObject.RenderInStream+=data[2]+";"
                self.debug.step()
            except Exception as e:
                self.debug.step()
                #print(e)
                ##No data##
                pass
            self.debug.step()
            try:
                time.sleep(0.01-(time.time()-Clock))
            except:
                print("The program is not capable of time travel : Cannot sleep",time.time()-Clock,"seconds")
                pass
