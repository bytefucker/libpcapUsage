/* main.c
   
   To compile:
   >gcc main.c -o main -lpcap

   To run: 
   a) run with sudo or
   b) sudo chmod 777 /dev/bpf*

   Looks for an interface, and lists the network ip
   and mask associated with that interface.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>   /* assume we have libpcap installed */
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
  char* dev;  /* name of the device to use */ 
  char* net;  /* dot notation of the network address */
  char* mask; /* dot notation of the network mask    */
  int ret;    /* return code */
  char errbuf[PCAP_ERRBUF_SIZE];
  bpf_u_int32 netp;   /* ip          */
  bpf_u_int32 maskp;  /* subnet mask */
  struct in_addr addr;

  /* ask pcap to find a valid device for use to sniff on */
  dev = pcap_lookupdev(errbuf);

  /* error checking */
  if(!dev)
  {
   printf("%s\n",errbuf);
   exit(1);
  }

  /* print out device name */
  printf("Device: %s\n",dev);

  /* ask pcap for the network address and mask of the device */
  ret = pcap_lookupnet(dev,&netp,&maskp,errbuf);

  if(ret == -1)
  {
   printf("%s\n",errbuf);
   exit(1);
  }

  /* get the network address in a human readable form */
  addr.s_addr = netp;
  net = inet_ntoa(addr);

  if(!net)/* thanks Scott :-P */
  {
    perror("inet_ntoa");
    exit(1);
  }

  printf("Address: %s\n",net);

  /* do the same as above for the device's mask */
  addr.s_addr = maskp;
  mask = inet_ntoa(addr);
  
  if(!mask)
  {
    perror("inet_ntoa");
    exit(1);
  }
  
  printf("Mask: %s\n",mask);

  return 0;
}