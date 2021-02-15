#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <linux/if_packet.h>

int main()
{
  int PACKET_LEN = 512;
  char buffer[PACKET_LEN];
  struct sockaddr saddr;
  struct packet_mreq mr;

  // create the raw socket
  int sock = socket(AF_INET, SOCK_RAW, htons(ETH_P_ALL));

  // turn on promiscous mode
  mr.mr_type = PACKET_MR_PROMISC;
  setsockopt(sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr));

  //getting packets
  while(1)
  {
    int dataLen = recvfrom(sock, buffer, PACKET_LEN, 0, &saddr, (socklen_t*)sizeof(saddr));
    if(dataLen)
      printf("Got a packet !\n%s\n",buffer);
  }
  close(sock);
  return 0;
}
