/*********************************************************************/
/*                  netclock.c                                       */
/* このプログラムは、時刻を返答するネットワークサーバです。          */
/* 起動すると、20000番ポートで接続を待ち受けます。                   */
/* 各自で試すときは、20000+名簿番号のポートを使うように変更すること。*/
/* その場合、reader.c の方も変更する必要があります。                 */
/*   使い方：  netclock                                              */
/*                      Ctrl-Cキーの入力でプログラムが停止します。   */
/*********************************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVERPORTNUM 20000  /* サーバのポート番号 */
#define MAXNUM           10  /* 最大接続数 */

int main()
{
  int serversocket;           /* サーバのソケットディスクリプタ */
  int clientsocket;           /* クライアントのソケットディスクリプタ */
  struct sockaddr_in server;  /* サーバのアドレス */
  struct sockaddr_in client;  /* クライアントのアドレス */
  unsigned int cl;
  time_t t;
  char msg[255];

  /* サーバ側のソケットの準備 */
  serversocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  /* ソケットのセッティング */
  memset(&server, 0, sizeof(server));
  server.sin_family      = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);      /* htonl は long 型用 */
  server.sin_port        = htons(SERVERPORTNUM);   /* htons は short型用 */
  bind(serversocket, (struct sockaddr *)&server, sizeof(server));

  /* サーバソケットを接続待ち受け状態にする */
  listen(serversocket, MAXNUM);

  /* クライアントに対応する */
  while(1) {
    cl = sizeof(client);
    clientsocket = accept(serversocket, (struct sockaddr *)&client, &cl);
    /* 時刻の処理 */
    time(&t);
    strcpy(msg, ctime(&t));
    printf("%s\n", msg);  /* サーバ側画面にメッセージを表示 */
    send(clientsocket, msg, strlen(msg), 0);
    /* 接続終了 */
    close(clientsocket);
  }
  return 0;
}