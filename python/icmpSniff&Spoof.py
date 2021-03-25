#!/usr/bin/python3

from scapy.all import *

def spoofPkt(pkt):
    if ICMP in pkt and pkt[ICMP].type == 8:
        print("Original Packet.........")
        print("Source IP : ", pkt[IP].src)
        print("Destination IP : ", pkt[IP].dst)

        ip = IP(src=pkt[IP].dst, dst=pkt[IP].src, ihl=pkt[IP].ihl)
        ip.ttl = 99
        icmp = ICMP(type = 0, id = pkt[ICMP].id, seq = pkt[ICMP].seq)

        if pkt.haslayer(Raw):
            data = pkt[Raw].load
            newPkt = ip/icmp/data
        else:
            newPkt = ip/icmp

        print("Spoofed Packet.........")
        print("Source IP : ", newPkt[IP].src)
        print("Destination IP : ", newPkt[IP].dst)

        send(newPkt)

sniff(filter='icmp src host 10.0.2.15', prn = spoofPkt)
