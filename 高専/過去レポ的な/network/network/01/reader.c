/*********************************************************************/
/*               reader.c                                            */
/* このプログラムは、TCP接続を行うクライアントです。                 */
/* 起動すると、20000番ポートでサーバと接続して、データを読み取ります */
/*                                                                   */
/*   使い方:   reader (サーバのIPアドレス)                           */
/*********************************************************************/

/* ヘッダファイルのインクルード */
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVERPORTNUM 20000 /* サーバのポート番号 */


int main(int argc, char *argv[])
{
  int csocket;               /* ソケットのディスクリプタ */
  struct sockaddr_in server; /* サーバのアドレス */
  char msg[255];

  /* ソケットの準備 */
  csocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  /* ソケットのセッティング */
  memset(&server, 0, sizeof(server));
  server.sin_family      = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port        = htons(SERVERPORTNUM);

  /* サーバとの接続 */
  connect(csocket, (struct sockaddr *)&server, sizeof(server));

  /* データの読み込み */
  memset(&msg, '\0', sizeof(msg));
  while (recv(csocket, msg, sizeof(msg)-1, 0) > 0) {
     /* 文字列をそのまま表示するのでめいっぱいは受信せず，
        1バイトだけ小さくサイズ指定 → 文字列終端(\0) が入る */
    printf("%s", msg);
    memset(&msg, '\0', sizeof(msg));
  }

  /* ソケットのクローズ */
  close(csocket);

  return 0;
}
