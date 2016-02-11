/*
 ** client.c -- a stream socket client demo
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
#include <ctype.h>
#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*) sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*) sa)->sin6_addr);
}

int main(int argc, char *argv[]) {
	int Exit = 0;
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	char bufRec[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	int itteration = 0;
	int k = 0;
	if (argc != 2) {
		fprintf(stderr, "usage: client hostname\n");
		exit(1);
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and connect to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s,
			sizeof s);
	printf("client: connecting to %s\n", s);

		int i = 0;

		if (itteration == 0) {
			printf(
					"Please input your command. Type 'help' for help.\nREMOTEMACHINE$");
			fgets(buf, MAXDATASIZE - 1, stdin);
			itteration++;
		} else {
			printf("REMOTEMACHINE$");
			fgets(buf, MAXDATASIZE, stdin);
		}

		if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) p->ai_addr,
				p->ai_addrlen) == -1) {
			perror("send");
		}

		if ((numbytes = recv(sockfd, bufRec, MAXDATASIZE, 0)) == -1) {
			perror("recv");
			exit(1);
		}

		char str[15];
		sprintf(str, "%s", bufRec);
		k = atoi(str);
		for (i = k; i > 0; i--) {
			memset(&bufRec, 0, sizeof(bufRec));
			if ((numbytes = recv(sockfd, bufRec, MAXDATASIZE, 0)) == -1) {
				perror("recv");
				exit(1);
			}
			if(bufRec[0]!='\n')
			{printf("%s", bufRec);}
			printf("\n");
		}


	freeaddrinfo(servinfo); // all done with this structure

	close(sockfd);

	return 0;
}

