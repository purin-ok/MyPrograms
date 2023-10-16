#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 
#include <winsock2.h> 
#define IS_INVALID_SOCKET(s) ((s) == INVALID_SOCKET)
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#define IS_INVALID_SOCKET(s) ((s) < 0) 
#endif

#define RCVBUFSIZE 32

void DieWithError(char *errorMessage);

int main(int argc, char *argv[])
{
	#ifdef _WIN32
	SOCKET sock;
	#else
	int sock;
	#endif
	struct sockaddr_in echoServAddr;
	unsigned short echoServPort;
	char *servIP;
	char *echoString;
	char echoBuffer[RCVBUFSIZE];
	int echoStringLen;
	int bytesRcvd, totalBytesRcvd;

	#ifdef _WIN32 
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2,0), &wsaData);
	#endif

	if ((argc < 3) || (argc > 4))
	{
		fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>}\n", argv[0]);
		exit(1);
	}

	servIP = argv[1];
	echoString = argv[2];

	if (argc == 4)
		echoServPort = atoi(argv[3]);
	else
		echoServPort = 7;

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (IS_INVALID_SOCKET(sock))
		DieWithError("socket() failed");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("connect() failed");

	echoStringLen = strlen(echoString);

	if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
		DieWithError("send() sent a different number of bytes than expected");


	totalBytesRcvd = 0;
	printf("Received: ");
	while (totalBytesRcvd < echoStringLen)
	{
		if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
			DieWithError("recv() failed or connection closed prematurely");
		totalBytesRcvd += bytesRcvd;
		echoBuffer[bytesRcvd] = '\0';
		#ifdef _WIN32
			printf("%s",echoBuffer);
		#else
			printf(echoBuffer);
		#endif
	}

	printf("\n");

	#ifdef _WIN32 
		closesocket(sock);
		WSACleanup(); 
	#else 
		close(sock); 
	#endif

	return 0;
}

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(EXIT_FAILURE);
}
