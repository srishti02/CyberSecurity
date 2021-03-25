#!/usr/bin/python3

from scapy.all import *

ipHdr = IP(src = "127.0.0.1", dst = "127.0.0.1")
udpHdr = UDP(sport = 9091, dport = 9090)
data = "Hello !"

pkt = ipHdr/udpHdr/data
pkt.show()
send(pkt,verbose=3)

