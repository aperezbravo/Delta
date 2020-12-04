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

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold

#define MAXDATASIZE 100 //number of bytes

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int getaddrinfo_status;
	struct addrinfo hints, *p;
	struct in_addr addr;
	struct addrinfo *result_list;
	
	memset(&hints, 0, sizeof hints);//sets everything to 0's in struct
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	//allows all hosts on the network to connect
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo_status = (getaddrinfo("www.google.com", NULL, &hints, &result_list)) ;

	addr.s_addr = ((struct sockaddr_in *)result_list->ai_addr)->sin_addr.s_addr;



	if(result_list != NULL)
	{
		//inet_ntoa, given an ip address in network byte form, converts it to a string in dotted format
		fprintf(stdout, "list is not NULL %s \n", inet_ntoa(addr));
	}
	

	//if( (getaddrinfo_status = (getaddrinfo(NULL, PORT, &hints, &result_list)) != 0) )
	{
		//fprintf(stderr, "err in getaddrinfo()\n");
		//1 is equivalent to EXIT_FAILURE flag
		//exit(1);
	}

	/*for(p = result_list; p != NULL; p = p->ai_next)
	{
		fprintf(stdout, "%s",p->ai_family);
	}*/

	freeaddrinfo(result_list);
        return 0;
}
