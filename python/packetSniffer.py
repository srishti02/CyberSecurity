#!/usr/bin/python3

from scapy.all import *

#APPROACH-1

#pkt = sniff(iface='lo',
#        filter='icmp or udp',
#        count=10)
#
#pkt.summary()

#APPROACH-2
def processPacket(pkt):
#    pkt.show()
    if pkt.haslayer(IP):
        ip = pkt[IP]
        print("IP : {} --> {}".format(ip.src,ip.dst))

    if pkt.haslayer(TCP):
        tcp = pkt[TCP]
        print("TCP port : {} --> {}".format(tcp.sport,tcp.dport))

    elif pkt.haslayer(UDP):
        udp = pkt[UDP]
        print("UDP port : {} --> {}".format(udp.sport,udp.dport))

    elif pkt.haslayer(ICMP):
        icmp = pkt[ICMP]
        print("ICMP type : {}".format(icmp.type))

    else:
        print("Other")

#f = 'udp and dst portrange 50-55 or icmp'

sniff(iface='lo', filter = '', prn=processPacket);
