** server.c -- a stream socket server demo
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
#include <ctype.h>

#define PORT "3490"  // the port users will be connecting to
#define MAXDATASIZE 100
#define BACKLOG 10	 // how many pending connections queue will hold

void sigchld_handler(int s) {
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*) sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*) sa)->sin6_addr);
}

int main(void) {
	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
				== -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections...\n");

	while (1) {  // main accept() loop
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
				get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
		printf("server: got connection from %s\n", s);

		if (!fork()) { // this is the child process
			close(sockfd); // child doesn't need the listener
			socklen_t addr_len;
			char buffer[MAXDATASIZE];
			char buffer2[MAXDATASIZE][MAXDATASIZE];
			//char buffer3[MAXDATASIZE][MAXDATASIZE];
			addr_len = sizeof their_addr;
			int numbytes = 0;
			FILE *out;
			FILE *popen();
			int i, j;


				numbytes = 0;
				if ((numbytes = recvfrom(new_fd, buffer, MAXDATASIZE, 0,
						(struct sockaddr *) &their_addr, &addr_len)) == -1) {
					perror("recvfrom");
				}
				buffer[numbytes] = '\0';
				printf("listener: got packet from %s\n",
						inet_ntop(their_addr.ss_family,
								get_in_addr((struct sockaddr *) &their_addr), s,
								sizeof s));
				printf("listener: packet is %d bytes long\n", numbytes);
				printf("listener: packet contains\n");

				for (i = 0; i < numbytes; i++) {
					printf("%c", buffer[i]);
					if (buffer[i] == ' ') {
						j = i;
						i = numbytes;
					}
				}


				if (!(out = popen(buffer, "r"))) {
					printf("error");
				}
				int count = 0;
				while (fgets(&buffer2[count][0], MAXDATASIZE, out) != NULL || count<100) {
					printf("%s", &buffer2[count][0]);
					count++;
				}

				char str[15];
				sprintf(str, "%d", count);

				if (sendto(new_fd, str, strlen(str)-1, MSG_CONFIRM,
						(struct sockaddr *) &their_addr, addr_len) == -1) {
					perror("send");
				}

				i=0;
				while(i<count)
				{
				sleep(2);

				if (sendto(new_fd, &buffer2[i][0], strlen(&buffer2[i][0])-1, MSG_CONFIRM,
						(struct sockaddr *) &their_addr, addr_len) == -1) {
					perror("send");
				}
				i++;
				}
				pclose(out);


			close(new_fd);
			exit(0);
		}
		close(new_fd);  // parent doesn't need this
	}

	return 0;
}

