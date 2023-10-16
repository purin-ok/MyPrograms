#include <stdio.h>       /* printf()、fprintf()に必要 */
#include <stdlib.h>      /* atoi()に必要 */
#include <string.h>      /* memset()に必要 */

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>  /* socket()、bind()、connect()に必要 */
#include <arpa/inet.h>   /* sockaddr_in、inet_ntoa()に必要 */
#include <unistd.h>      /* close()に必要 */
#endif /* _WIN32 */

#ifdef _WIN32
#define IS_INVALID_SOCKET(s) ((s) == INVALID_SOCKET)
#else
#define SOCKET int
#define IS_INVALID_SOCKET(s) ((s) < 0)
#define closesocket(s) close(s)
#endif /* _WIN32 */

#define MAXPENDING 5     /* 未処理の接続要求の最大値 */
#define RCVBUFSIZE 32    /* 受信バッファのサイズ */


void DieWithError(char *errorMessage);  /* エラー処理関数 */
void HandleTCPClient(SOCKET clntSocket);   /* TCPクライアントの処理関数 */
SOCKET CreateTCPServerSocket(unsigned short port); /* TCPサーバソケットを作成 */
SOCKET AcceptTCPConnection(SOCKET servSock);  /* TCP接続要求を受け付ける */


int main(int argc, char *argv[])
{
    SOCKET servSock;                     /* サーバのソケットディスクリプタ */
    SOCKET clntSock;                     /* クライアントのソケットディスクリプタ */
    unsigned short echoServPort;      /* サーバのポート番号 */
#ifdef _WIN32
    WSADATA wsaData;
#else
    pid_t processID;                  /* fork()が返すプロセスID */
    unsigned int childProcCount = 0;  /* 子プロセスの数 */
#endif

#ifdef _WIN32
    WSAStartup(MAKEWORD(2,0), &wsaData);
#endif /* _WIN32 */


  if (argc != 2)    /* 引数の数が正しいか確認 */
  {
      fprintf(stderr, "Usage: %s <Server Port>", argv[0]);
      exit(EXIT_FAILURE);
  }

  echoServPort = atoi(argv[1]); /* 1つ目の引数： ローカルポート */

  servSock = CreateTCPServerSocket(echoServPort);

  for (;;) /* 処理を繰り返し実行 */
  {
      clntSock = AcceptTCPConnection(servSock);
#ifdef _WIN32 /* fork を使わず、反復サーバとして動作 */
      HandleTCPClient(clntSock);
      closesocket(clntSock);
#else /* Linux では fork を使って並行サーバとして動作 */
      /* 子プロセスのフォークとエラーを報告 */
    if ((processID = fork()) < 0) DieWithError("fork() failed");
    else if (processID == 0) /* 子プロセスの場合 */
    {
         closesocket(servSock);   /* 待ち受け中のソケットを子プロセスがクローズ */
         HandleTCPClient(clntSock);

         exit(EXIT_SUCCESS);           /* 子プロセスを終了 */
    }

    printf("with child process: %d\n", (int) processID);
    closesocket(clntSock);       /* 子のソケットディスクリプタを親がクローズ */
    childProcCount++;      /* 未回収の子プロセスの数をインクリメント */

    while (childProcCount) /* 全ゾンビをクリーンアップ */
    {
        processID = waitpid((pid_t) -1, NULL, WNOHANG); /* ノンブロッキングで実行 */
        if (processID < 0) /* waitpid()のエラーを確認 */
            DieWithError("waitpid() failed");
        else if (processID == 0)  /* ゾンビが存在しない */
            break;
        else
            childProcCount--;  /* 子プロセスを回収 */
    }
#endif /* _WIN32 */
  }
  /* この部分には到達しない */
}


SOCKET CreateTCPServerSocket(unsigned short port)
{
    SOCKET sock;                        /* 作成するソケット */
    struct sockaddr_in echoServAddr; /* ローカルアドレス */

    /* 着信接続要求に対するソケットを作成 */
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (IS_INVALID_SOCKET(sock))
        DieWithError("socket() failed");

    /* ローカルのアドレス構造体を作成 */
    memset(&echoServAddr, 0, sizeof(echoServAddr));    /* 構造体をゼロで埋める */
    echoServAddr.sin_family = AF_INET;                /* インターネットアドレスファミリ */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* ワイルドカードを使用 */
    echoServAddr.sin_port = htons(port);              /* ローカルポート */

    /* ローカルアドレスへバインド */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* 着信接続要求のリスン中というマークをソケットに付ける */
    if (listen(sock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    return sock;
}


SOCKET AcceptTCPConnection(SOCKET servSock)
{
    SOCKET clntSock;                   /* クライアントのソケットディスクリプタ */
    struct sockaddr_in echoClntAddr; /* クライアントのアドレス */
    int clntLen;           /* クライアントのアドレス構造体の長さ */

    /* 入出力パラメータのサイズをセット */
    clntLen = sizeof(echoClntAddr);

    /* クライアントからの接続要求を待つ */
    clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen);
    if (IS_INVALID_SOCKET(clntSock))
        DieWithError("accept() failed");

     /* clntSockはクライアントに接続済み */

     printf ("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

     return clntSock;
}


void HandleTCPClient(SOCKET clntSocket)
{
  char echoBuffer[RCVBUFSIZE];  /* エコー文字列のバッファ */
  int recvMsgSize;  /* 受信メッセージのサイズ */

  /* クライアントからの受信メッセージ */
  if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    DieWithError("recv() failed");

  /* 受信した文字列を送信し、転送が終了していなければ次を受信する */
  while (recvMsgSize > 0) /* ゼロは転送の終了を意味する */
  {
    /* メッセージをクライアントにエコーバックする */
    if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
      DieWithError("send() failed");

    /* 受信するデータが残っていないか確認する */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
      DieWithError("recv() failed");
  }

  closesocket(clntSocket);  /* クライアントソケットをクローズする */
}

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(EXIT_FAILURE);
}
