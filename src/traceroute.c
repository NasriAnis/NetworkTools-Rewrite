#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>

void traceroute(char **tokens)
{
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sockfd < 0){
    printf("Socket Error");
    return;
  }

  int sockfd_received = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sockfd_received < 0){
    printf("Socket Error");
    return;
  }

  struct sockaddr_in dest_addr;
  memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  inet_pton(AF_INET, tokens[1], &dest_addr.sin_addr);

  char buffer[1080];

  for (int ttl = 1; ttl <= 30; ttl++) {
    setsockopt(sockfd_received, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
    sendto(sockfd_received, buffer, sizeof(buffer), 0,
          (struct sockaddr*)&dest_addr, sizeof(dest_addr));
  }
}
