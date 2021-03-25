#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>

void sendRawIpPacket(struct iphdr* ip)
{
  struct sockaddr_in destInfo;
  int enable = 1;

  // create a raw socket
  int sock = socket(AF_INET,SOCK_RAW,IPPROTO_RAW);

  setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable));

  //destination info
  memset((char*)&destInfo, 0 , sizeof(destInfo));
  destInfo.sin_family = AF_INET;
  destInfo.sin_addr.s_addr = inet_addr("10.0.2.15");
  destInfo.sin_port = htons(9090);

  // send the packet
  printf("Sending spoofed IP Packet..\n");
  if(sendto(sock, ip, ntohs(ip->tot_len), 0,(struct sockaddr *)&destInfo,sizeof(destInfo)) < 0)
  {
    perror("Packet not sent!\n");
    return;
  }
  printf("Packet Sent Successfully!");
  close(sock);
}

int main()
{
  char buffer[1024];
  memset(buffer,0,1024);

  //Find starting point of each layer
  struct iphdr *ip = (struct iphdr*) buffer;
  struct udphdr *udp = (struct udphdr*)(buffer + sizeof(struct iphdr));
  char* data = buffer + sizeof(struct iphdr) + sizeof(struct udphdr);

  //add UDP data
  char *msg = "Hello Server.\n";
  int dataLen = strlen(msg);
  strncpy(data,msg,dataLen);

  //Construct UDP header
  udp->uh_sport = htons(9999);
  udp->uh_dport = htons(9090);
  udp->uh_ulen = htons(sizeof(struct udphdr) + dataLen);
  udp->uh_sum = 0;

  //Construct IP Header
  ip->version = 4;
  ip->ihl = 5;
  ip->ttl = 20;
  ip->saddr = inet_addr("1.2.3.4");
  ip->daddr = inet_addr("10.0.2.15");
  ip->protocol = IPPROTO_UDP;
  ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + dataLen);

  // send out constructed packet
  sendRawIpPacket(ip);
  return 0;
}
