#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

unsigned short calculate_checksum(void *ptr, int nbytes);

void ping(char **tokens)
{
  // create a raw socket (IPv4, RAW, ICMP) ********************************************

  int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  if (sockfd < 0){
    printf("Error : Did you run with root ?");
    return;
  }

  // From linux code we find this structure *******************************************

  // Internet domain sockets
  // #include <netinet/in.h>
  //
  // struct sockaddr_in {
  //   sa_family_t     sin_family;     /* AF_INET */
  //   in_port_t       sin_port;       /* Port number */
  //   struct in_addr  sin_addr;       /* IPv4 address */
  // };

  struct sockaddr_in destination_address;
  memset(&destination_address, 0, sizeof(destination_address));

  destination_address.sin_family = AF_INET;
  inet_pton(AF_INET, tokens[1], &destination_address.sin_addr);

  // Crafting an ICMP header **********************************************************

  // from inet code we find these :
  // https://github.com/leostratus/netinet/blob/master/ip_icmp.h

  // #define	ICMP_ECHO		8		/* echo service */
  //
  //  /*
  // * Structure of an icmp header.
  // */
  //  struct icmphdr {
  //    u_char	icmp_type;		/* type of message, see below */
  //    u_char	icmp_code;		/* type sub code */
  //    u_short	icmp_cksum;		/* ones complement cksum of struct */
  //  };

  struct icmphdr icmp_header;
  memset(&icmp_header, 0, sizeof(icmp_header));

  icmp_header.type = ICMP_ECHO;
  icmp_header.code = 0;

  // these are unions from linux
  icmp_header.un.echo.id = getpid();
  icmp_header.un.echo.sequence = 1;

  icmp_header.checksum = calculate_checksum(&icmp_header, sizeof(icmp_header));

  // send packet *************************************************************************

  if (sendto(sockfd, &icmp_header, sizeof(icmp_header), 0,
     (const struct sockaddr *)&destination_address, sizeof(destination_address)) <= 0) {
    perror("sendto error");
    return;
  }

  // receive the reply *******************************************************************

  char buff[1080];
  struct sockaddr_in source_address;
  socklen_t address_len = sizeof(source_address);

  if (recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&source_address, &address_len) <= 0){
    perror("recvfrom error");
    return;
  }

  // inet_ntoa : (Internet Network to ASCII)
  // converts a 32-bit IPv4 network byte order address
  // into a dotted-decimal string (e.g., "192.168.0.1")

  else {
    printf("Received reply from %s : \n", inet_ntoa(source_address.sin_addr));
  }

  close(sockfd);
  return;
}

unsigned short calculate_checksum(void *b, int len)
{
  unsigned short *buf = b;
  unsigned int sum = 0;
  unsigned short result;
  for (sum = 0; len > 1; len -= 2) sum += *buf++;
  if (len == 1) sum += *(unsigned char *)buf;
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  result = ~sum;
  return result;
}

