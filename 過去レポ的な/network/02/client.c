/* クライアントプログラムの例　その２ */
/* client <IPアドレス> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <errno.h>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#define SERVERPORTNUM 80
#define BUFLEN        1024

#ifdef _WIN32
#define IS_INVALID_SOCKET(x) ((x) == INVALID_SOCKET)
#define IS_CLOSE_SOCKET(s) closesocket(s)
#else
#define IS_INVALID_SOCKET(x) ((x) < 0)
#define IS_CLOSE_SOCKET(s) close(s)
#endif

int main(int argc, char *argv[])
{
#ifdef _WIN32
  SOCKET s;
#else
  int s;
#endif

  struct sockaddr_in addr;
  struct in_addr addr2;
  char *getcmd = "GET / HTTP/1.0\r\n\r\n";
  char buf[BUFLEN+1];
  int portnum = SERVERPORTNUM, rc;
  struct hostent *pe;

#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,0), &wsaData);
#endif

  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (IS_INVALID_SOCKET(s)) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  if (argc > 1) {
    pe = gethostbyname(argv[1]);
    if (pe == NULL) {
      printf("host not found\n");
      exit(EXIT_SUCCESS);
    }
    memcpy(&addr2.s_addr, pe->h_addr_list[0], pe->h_length);
    addr.sin_addr.s_addr = inet_addr(inet_ntoa(addr2));
  }

  addr.sin_family      = AF_INET;
  if(argc > 2){	
  	addr.sin_port        = htons(atoi(argv[2]));
  }else{ 
  	addr.sin_port        = htons(SERVERPORTNUM);
  }

  if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  if (send(s, getcmd, strlen(getcmd), 0) < 0) {
    perror("send");
    exit(EXIT_FAILURE);
  }

  while ((rc = recv(s, buf, BUFLEN, 0)) > 0) {
    buf[rc] = '\0';
    printf("%s", buf);
  }
  IS_CLOSE_SOCKET(s);

#ifdef _WIN32
  WSACleanup();
#endif

  return 0;
}
