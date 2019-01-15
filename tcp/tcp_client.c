/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:01:40 by mmakatsh          #+#    #+#             */
/*   Updated: 2019/01/07 14:53:59 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
//will allow us to use som apis
#include <sys/types.h>
#include <sys/socket.h>

//we need structures to store add info
#include <netinet/in.h>

//main function

int main(){

	/*
	 *		step 1: create a cleant
	 */

	int network_socket; //use an integer var to hold  the socket descriptor

	/*
	 *		->call the socket function then store the results in the network_socket integer
	 *		->the first param is the domain
	 *		->second param is the socket type
	 *		->third and last param specifies the protocol
	 */

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	/*
	 * 		specify an address for the socketo
	 */

	struct sockaddr_in server_address;
	
	//set the family of the address so that it knows what type of the address
	server_address.sin_family = AF_INET;

	//specify the port that we are gonna connect to
	server_address.sin_port = htons(9002);

	//specify the actual address |it is a structure holding another structre that is why we use the
	server_address.sin_addr.s_addr = INADDR_ANY;

	
	//connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	//connect returns an int val 0->true -1->connection error we use that value for error handling
	int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	//check for error
	if (connection_status == -1)
	{
		printf("Connection error can not reach the socket\n");
		printf("please ensure that the port you are connecting to is correct");
	}	

	//once we get the connection we recieve or send data
	
	char server_response[1024];
	recv(network_socket, &server_response, sizeof(server_response), 0 );

	//printout the server's response
	printf("The server sent the data: %s\n", server_response);

	//and then close the socket
	close(network_socket);

		return (0);
}
