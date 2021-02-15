#!/usr/bin/python3

import socket

IP = "0.0.0.0"
PORT = 9090

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM);
sock.bind((IP,PORT))

while True:
    data, (ip,port) = sock.recvfrom(1024)
    print("Sender: {} and port : {}".format(ip,port))
    print("Received msg : {}".format(data))
