#include <stdio.h>
#include <string.h>
#include <pcap/pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>

void processPacket(u_char* args, 
    const struct pcap_pkthdr* header,
    const u_char* packet)
{
  printf("Received a packet!\n");
  struct ether_header *eth = (struct ether_header*)packet;

  if(ntohs(eth->ether_type) == 0x800)
  {
    struct ipheader* ip = (struct ipheader*)(packet + sizeof(struct ether_header));
    printf("From : %s\n", inet_ntoa(ip->iph_sourceip));
    printf("To : %s\n", inet_ntoa(ip->iph_destip));

    switch(ip->iph_protocol)
    {
      case IPPROTO_TCP:
        printf("Protocol : TCP\n");
        break;

      case IPPROTO_UDP:
        printf("Protocol : UDP\n");
        break;

      case IPPROTO_TCP:
        printf("Protocol : ICMP\n");
        break;

      default:
        printf("Protocol : Others\n");
        break;
    }
  }
}

int main()
{
  pcap_t* handle;
  char errbuf[PCAP_ERBUF_SIZE];
  struct bpf_program fp;
  char filter_exp[] = "udp or icmp";
  bpf_u_int32 net;

  // Open live pcap session on NIC with interface name
  handle = pcap_open_live("enp0s3", 8192, 1 /*promiscuous mode*/, 1000, errbuf);

  // Compile filter_exp into BPF psuedo code
  pcap_compile(handle, &fp, filter_exp,0, net);
  if(pcap_setfilter(handle, &fp) != 0)
  {
    pcap_perror(handle, "Error");
    exit(1);
  }

  // capture packets
  pcap_loop(handle, -1, processPacket, NULL);

  // close the handle
  pcap_close(handle);
  return 0;
}
