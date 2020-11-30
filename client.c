/*
** client.c -- a stream socket client demo
** client resource request base code from Beej's gGuide to Network Programming 
** https://beej.us/guide/bgnet/html//index.html#client-server-background
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    //(1)keeps track of the file descriptor pertaining to thae socket
    int sockfd, numbytes;  
    //buf is where payload lives and can be stripped down for echh header/trailer
    char buf[MAXDATASIZE];
    //addrinfo is the C data structure used to represent addresses and hostnames within the networking API 
    //essentialy it is a struct from an address family (name space) 
    struct addrinfo hints, *servinfo, *p;
    int rv;
    //buffer used to convert IPV4/6 addresses to human readable code/strings
    //INET6_ADDRSTRLEN defined the length of IPV6
    //*use INET_ADDRSTRLEN for IPV4
    char s[INET_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    //The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c which is just the size set reserved.
    //*hints is our first struct type addrinfo
    memset(&hints, 0, sizeof hints);
    //reduce any iverhead, specify the family
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    //rv is a simple integer
    //getaaddrinfo(const char *node, const char *serveice,
    //const struct addrinfo **res);
    //returns list of addresses strutures saved in to servinfo
    //a 0 signified the function was successful
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through linked list of all the results inside servinfo 
    //list and connect to the one we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        //int socket() (1)int domain, (2)int type, (3)int protocol;
        //creates an endpoint for communications and returns a file descriptor to it
        //returns -1 upon error
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        //connect() (1)file descriptor (2)struct sockaddr (3)socklen_t
        //attempts establish a connection to the address specified in the 2ng arg
        //successful cinnection returns a 0, -1 on error
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    //if this condition is hit, we have cycled through the list return in
    //servinfo to no avail connecting to an address
    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    //converts IPV4/6 addresses from binary to text
    //inet_ntop() (1)address family (2)address structure (3)buffer to save 
    //the str in to (4)size of buffer
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    //frees memory dynamically allcoated for the linked list returned by 
    //getaddrinfo in servinfo
    freeaddrinfo(servinfo); // all done with this structure

    //recv() (1)file descriptor (2)buffer (3)length of buffer (4)flags used
    //returns the number of bytes recieved, if there is an error
    //returns -1
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    //clear the buffer
    buf[numbytes] = '\0';

    printf("client: received '%s'\n",buf);

    //close the socket
    close(sockfd);

    return 0;
}
