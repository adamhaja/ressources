#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LISTEN_PORT 11222

int main() {
  char buf[64];

  int sock;
  int peersock;
  struct sockaddr_in my_addr;
  int reuse = 1;

  if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    perror("socket");
    return(1);
  }

  if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
    perror("setsockopt");
    return(1);
  }

  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(LISTEN_PORT);
  my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if(bind(sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
    perror("bind");
    return(1);
  }

  if(listen(sock, 5) == -1) {
    perror("listen");
    return(1);
  }

  if((peersock = accept(sock, NULL, 0)) == -1) {
    perror("accept");
    return(1);
  }

  if(read(peersock, buf, 500) == -1) {
    printf("Error: %d", errno);
    perror("read");
    return(1);
  }

  printf("%s", buf);

  return(0);
}

