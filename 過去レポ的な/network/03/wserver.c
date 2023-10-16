#include <winsock2.h>

#define SERVERPORTNUM 12345


int main(void)
{
  WSADATA wsaData;
  SOCKET sock, sock0;

  struct sockaddr_in addr;
  struct sockaddr_in client;
  int len;

  /* WinSock2 の初期化 */
  WSAStartup(MAKEWORD(2,0), &wsaData);

  /* ソケットの作成 */
  sock0 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  /* ソケットの設定 */
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port        = htons(SERVERPORTNUM);

  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

  /* クライアントからの接続要求待ちに入る */
  listen(sock0, 5);

  /* TCPクライアントからの接続要求を受け付ける */
  while(1) {
    len  = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);
    send(sock, "HELLO", 5, 0);

    closesocket(sock);
  }

  closesocket(sock0);
  WSACleanup();
  return 0;
}