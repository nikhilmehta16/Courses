// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char hello[1024] = "Hello from client\0";
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
    while(strlen(hello)!=1){
        send(sock, hello, strlen(hello), 0);
        valread = read(sock, buffer, 1024);
        printf("%s\n Nikhil", buffer);
        memset(buffer, 0, 1024);
        printf("Enter message: ");
        scanf("%s", hello);
    }
	// send(sock, hello, strlen(hello), 0);
	// printf("Hello message sent\n");
	// valread = read(sock, buffer, 1024);
	// printf("%s\n", buffer);
	return 0;
}
