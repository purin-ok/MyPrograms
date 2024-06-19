/* サーバプログラムの例　その２ */
/* server */

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
#endif

#define SERVERPORTNUM   20040  /* 各自試すときは、20000+名簿番号 にする */
#define MAXNUM          10
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
  SOCKET s, csock;
#else
  int s, csock;
#endif

  int portnum = SERVERPORTNUM;
  struct sockaddr_in addr, caddr;
  int  caddr_len, rc;
  char buf[BUFLEN+1];
  char *html1 = "HTTP/1.1 200 OK\n\n";
  char *html2 =
        "<html><head></head><body><H1>SAMPLE PAGE</H1></body></html>\n";

#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,0), &wsaData);
#endif

  if (argc>1) {
    portnum = atoi(argv[1]);
    if (portnum < 1) portnum = SERVERPORTNUM;
  }

  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (IS_INVALID_SOCKET(s)) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port        = htons(portnum);

  IS_INVALID_SOCKET(s);

  if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(s, MAXNUM) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  while (1) {
    caddr_len = sizeof(caddr);
    csock = accept(s, (struct sockaddr *)&caddr, &caddr_len);
    if ((rc = recv(csock, buf, BUFLEN, 0)) > 0) {
      /* 接続してきたクライアントの情報を表示 */
      printf("CLIENT ADDRESS: %s\n", inet_ntoa(caddr.sin_addr));
      /* クライアントからのメッセージを受信して表示 */
      buf[rc] = '\0'; /* 受信した文字列の最後にNULLを追加 */
      printf("REQUEST STRING: %s\n", buf);
    }

    send(csock, html1, strlen(html1), 0); /*メッセージをクライアントに送信*/
    send(csock, html2, strlen(html2), 0); /*メッセージをクライアントに送信*/
    IS_CLOSE_SOCKET(csock);
  }
  IS_CLOSE_SOCKET(s);

#ifdef _WIN32
  WSACleanup();
#endif

  return 0;
}
