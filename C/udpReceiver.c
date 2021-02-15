#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>

void main()
{
  struct sockaddr_in client;
  struct sockaddr_in server;

  int receivedLen;
  char buf[1500];

  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset((char*)&server, 0 , sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(9090);

  if(bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    error("ERROR on binding!");

  while(1)
  {
    bzero(buf, 1500);
    recvfrom(sock,buf,1500-1,0,(struct sockaddr*)&client, &receivedLen);
    printf("%s\n",buf);
  }
  close(sock);
}
