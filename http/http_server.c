#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#define PORT    8080
#define TRUE    1
#define FALSE   0

int main() 
{
    //variable definations
    	struct sockaddr_in server_address;
        FILE *html_data;
        char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
        char response_data[1024];
        int server_socket;
        int client_socket;

	// open a file to serve
	
	html_data =  fopen("index.html", "r");


	fgets(response_data, 1024, html_data);

	
	strcat(http_header, response_data);

	// create a socket 
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
    /* debugging code
        socket_fd = socket(domain, type, protocol)
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    */
	
	// define the address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	while(42) {
		client_socket = accept(server_socket, NULL, NULL);
        printf("test1 : %d\n", client_socket);
		send(client_socket, http_header, sizeof(http_header), 0);
        printf("test %s\n", http_header);
		close(client_socket);
	}
	return 0;
}