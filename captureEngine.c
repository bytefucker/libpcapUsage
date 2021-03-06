/**********************************************************************
*
* Q&D proggy to demonstrate the use of pcap_loop
*
**********************************************************************/

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>

/* callback function that is passed to pcap_loop(..) and called each time 
 * a packet is recieved                                                    */
void my_callback(u_char* useless, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    static int count = 1;
    printf("Grabbed %d packet\n", count);
    // todo: add hdr.len info

    fflush(stdout);
    count++;
}

int main(int argc, char** argv)
{ 
    int i;
    char* dev; 
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* descr;
    const u_char* packet;
    struct pcap_pkthdr hdr;     /* pcap.h */
    struct ether_header* eptr;  /* net/ethernet.h */

    if(argc != 2)
        { fprintf(stdout,"Usage: %s numpackets\n",argv[0]); return 0; }

    /* grab a device to peak into... */
    dev = pcap_lookupdev(errbuf);
    if(!dev)
        { printf("%s\n",errbuf); exit(1); }

    /* open device for reading */
    descr = pcap_open_live(dev, BUFSIZ, 1, 1, errbuf);
    if(!descr)
        { printf("pcap_open_live(): %s\n",errbuf); exit(1); }

    /* allright here we call pcap_loop(..) and pass in our callback function */
    /* int pcap_loop(pcap_t* p, int cnt, pcap_handler callback, u_char* user)*/
    /* If you are wondering what the user argument is all about, so am I!!   */
    pcap_loop(descr, atoi(argv[1]), my_callback, NULL);

    fprintf(stdout, "\nDone processing packets!\n");
    return 0;
}