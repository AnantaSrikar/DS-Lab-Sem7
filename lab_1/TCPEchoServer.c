/*
	Server side message with socket programming
	Author: Ananta Srikar
*/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	// TODO: Add command line arguments
	// Variables to initialize socket
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	int PORT = 8080;

	// Variables for storing communication
	char buffer[1024] = { 0 };
	char* hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// Start listening for a TCP connection
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	printf("Waiting for a client to connect\n");
	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	printf("Client connection recieved!\n");

	// TODO: print the client that is connected (port number atleast)

	// Start exchanging messages till the client wants to break up :p
	while(1)
	{
		valread = read(new_socket, buffer, 1024);
		printf("[Client]: %s\n", buffer);

		// Exit the server when we say bye
		if(strcmp(buffer, "BYE") == 0)
		{
			send(new_socket, "BYE", 4, 0);
			break;
		}

		// Get user input to be sent to client
		char outgoing[20];
		printf("[Server]: ");
		scanf("%s", outgoing);

		// Send the message to client
		send(new_socket, outgoing, strlen(outgoing), 0);
	}

	// closing the connected socket
	close(new_socket);

	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
