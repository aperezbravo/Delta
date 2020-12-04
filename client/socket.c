/*
** server.c -- a stream socket server demo
** server connectivity base code from Beej's gGuide to Network Programming 
** https://beej.us/guide/bgnet/html//index.html#client-server-background
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define BACKLOG 10   // how many pending connections queue will hold

#define MAXDATASIZE 100 //number of bytes


int main(void)
{
	int socketfd = socket(AF_INET, SOCK_DGRAM, 0);

	if(socketfd == -1)
	{
		fprintf(stderr, "error occured creating socket \n");
		exit(1);
	}
	else
	{
		fprintf(stdout, "endpoint established \n");
	}

	/*socklen_t addrlen;
	struct sockaddr_in host2, client;
	//struct in_addr host2_addr;
	uint16_t port = 3490;
	char buf[MAXDATASIZE];

	host2.sin_family = AF_INET;
	host2.sin_port = htons(port);
	//listen to any udp traffic coming in through port 3490, the ipaddress
	//does not matter with the INADDR_ANY flag set
	host2.sin_addr.s_addr = INADDR_ANY;

	int binding_state = bind(socketfd , (struct sockaddr *) &host2, sizeof host2);

	if(binding_state == -1)
	{
		fprintf(stderr, "error occured while binding \n");
		exit(1);
	}
	else
	{
		fprintf(stdout, "binding initiated\n");
	}

	int length = sizeof(client);
	int recvfrom_state;
	recvfrom_state = recvfrom(socketfd, (char *) buf, MAXDATASIZE - 1, 0, (struct sockaddr *) &client, &length );

	if(recvfrom_state == -1)
	{
		fprintf(stderr, "error occured while recv'ng message\n");
		exit(1);
	}
	else
	{
		fprintf(stdout, "ipaddress from sender is:%s\n", inet_ntoa(client.sin_addr));
	}
	*/
	
        return 0;
}
