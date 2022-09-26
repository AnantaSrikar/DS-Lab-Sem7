/*
	Client side message application

	Author: Ananta Srikar
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	// TODO: Add command line arguments
	// Variables to initialize socket
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;

	int PORT = 8080;

	// Variables for storing communication
	char *hello = "Hello from client";
	char buffer[1024] = { 0 };
	char *IP = "127.0.0.1";

	// Attempt creation of a socket on client side
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\nSocket creation error\n");
		return -1;
	}

	// Setting structure variables for server connection
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address / Address not supported\n");
		return -1;
	}

	// Attempting server connection
	if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
	{
		printf("\nConnection Failed\n");
		return -1;
	}

	// Sending message to server
	for(int i = 0; i < 5; i++)
	{
		char outgoing[20];

		printf("[Client]: ");
		scanf("%s", outgoing);
		send(sock, outgoing, strlen(outgoing), 0);

		// TODO: break loop when BYE is recieved

		// Recieveing message from server
		valread = read(sock, buffer, 1024);
		printf("[Server]: %s\n", buffer);
	}

	// closing the connected socket
	close(client_fd);
	return(0);
}