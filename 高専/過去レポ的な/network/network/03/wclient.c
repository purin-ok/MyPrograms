#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <winsock2.h>

#define SERVERPORTNUM 12345
#define SERVERIPADDR  "127.0.0.1"

int main(void)
{
  WSADATA wsaData;
  SOCKET sock;
  struct sockaddr_in server;
  char buf[32];
  int n;

  /* WinSock2 の初期化 */
  WSAStartup(MAKEWORD(2,0), &wsaData);

  /* ソケットの作成 */
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  /* 接続先情報の設定 */
  server.sin_family      = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVERIPADDR);
  server.sin_port        = htons(SERVERPORTNUM);

  /* サーバに接続 */
  connect(sock, (struct sockaddr *)&server, sizeof(server));

  /* サーバからデータを受信 */
  memset(buf, 0, sizeof(buf)); /* 配列の内容をゼロクリア */
  n = recv(sock, buf, sizeof(buf), 0);

  printf("%d, %s\n", n, buf);

  closesocket(sock);

  /* WinSock2 の終了処理 */
  WSACleanup();

  return 0;
}
