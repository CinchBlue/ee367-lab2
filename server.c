#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEBUG 1
#define MYPORT "4950"    // the port users will be connecting to

#define MAXBUFLEN 100



int sockfd, new_fd;
struct addrinfo hints, *servinfo, *p;
int rv;
int numbytes;
struct sockaddr_storage their_addr;
char buf[MAXBUFLEN];
char *test="test";
char bufParcedCommand[MAXBUFLEN];
char bufParcedArg[MAXBUFLEN];
socklen_t addr_len;
char s[INET6_ADDRSTRLEN];
int socketOpen = 0;
char buffer[MAXBUFLEN];

void parse();
void error(char *s);
void pipeCreate();
void act();
void help();
void xmit();

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*) sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*) sa)->sin6_addr);
}



int main(void) {

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	if (DEBUG == 1) {
		printf("1 sockfd=%d\n",sockfd);
	}
	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		} else {
			socketOpen = 1;
		}

		break;
	}

	if (DEBUG == 1) {
		printf("2 sockfd=%d\n",sockfd);
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	} else {
		socketOpen = 1;
	}



	printf("listener: waiting to recvfrom...\n");

	if (DEBUG == 1) {
		printf("3 sockfd=%d\n",sockfd);
	}

	if( sendto( sockfd, test, strlen(buffer), 0, (struct sockaddr *) &their_addr, addr_len) == -1)
			{
			perror("send");
		    }

	while (socketOpen == 1) {
		if (DEBUG == 1) {
			printf("4 sockfd=%d\n",sockfd);
		}
		act();
	}

	return 0;
}

void recieve() {
	addr_len = sizeof their_addr;
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0,
			(struct sockaddr *) &their_addr, &addr_len)) == -1) {
		perror("recvfrom");
		if (DEBUG == 1) {
			printf("5 sockfd=%d\n",sockfd);
		}
		recieve();
	}
	printf("listener: got packet from %s\n",
			inet_ntop(their_addr.ss_family,
					get_in_addr((struct sockaddr *) &their_addr), s, sizeof s));
	printf("listener: packet is %d bytes long\n", numbytes);
	buf[numbytes] = '\0';
	printf("listener: packet contains \"%s\"\n", buf);
}

void socketClose() {
	close(sockfd);
	socketOpen = 0;
}

void act() {
	if (DEBUG == 1) {
		printf("6 sockfd=%d\n",sockfd);
	}

	int i = 0;
	char bufShort[3];

	if (DEBUG == 1) {
		printf("7 sockfd=%d\n",sockfd);
	}
	recieve();

	for (i = 0; i < 4; i++) {
		bufShort[i] = buf[i];
	}

	if (DEBUG == 1) {
		printf("8 sockfd=%d\n",sockfd);
	}
	if (strcmp(bufShort, "quit")) {
		socketClose();
	}
	if (DEBUG == 1) {
		printf("9 sockfd=%d\n",sockfd);
	}
	if (strcmp(bufShort, "list")) {
		parse();
		pipeCreate();
	}
	if (DEBUG == 1) {
		printf("10 sockfd=%d\n",sockfd);
	}
	if (strcmp(bufShort, "chec")) {
		parse();
		pipeCreate();
	}
	if (DEBUG == 1) {
		printf("11 sockfd=%d\n",sockfd);
	}
	if (strcmp(bufShort, "down")) {
		parse();
		pipeCreate();
	}
	if (DEBUG == 1) {
		printf("12 sockfd=%d\n",sockfd);
	}
	if (strcmp(bufShort, "help")) {
		help();
	}
	if (DEBUG == 1) {
		printf("13 sockfd=%d\n",sockfd);
	}
	xmit();
}

void parse() {
	int i = 0;
	int j = 0;
	if (DEBUG == 1) {
		printf("14 sockfd=%d\n",sockfd);
	}
	while (buf[i] != ' ' && i < 250) {
		bufParcedCommand[i] = buf[i];
		i++;
	}
	if (DEBUG == 1) {
		printf("15 sockfd=%d\n",sockfd);
	}
	j = i + 2;
	while (buf[j] != '>' && i < 250) {
		bufParcedArg[j] = buf[j];
		j++;
	}
	if (DEBUG == 1) {
		printf("16 sockfd=%d\n",sockfd);
	}
}

void xmit() {
	close(sockfd);
	if (DEBUG == 1) {
			printf("27 sockfd=%d\n",sockfd);
		}
	//if (send(sockfd, buffer, strlen(buffer), 0) == -1)
		//perror("send");
	if( sendto( sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &their_addr, addr_len) == -1)
		{
		perror("send");
	    }
}

void help() {

}

void pipeCreate() {
	int in[2], out[2], n, pid;
	//In a pipe, xx[0] is for reading, xx[1] is for writing

	if (DEBUG == 1) {
			printf("17 sockfd=%d\n",sockfd);
		}
	if (pipe(in) < 0)
		error("pipe in");
	if (pipe(out) < 0)
		error("pipe out");

	if (DEBUG == 1) {
			printf("18 sockfd=%d\n",sockfd);
		}
	if ((pid = fork()) == 0) {
//This is the child process

// Close stdin, stdout, stderr
		close(0);
		close(1);
		close(2);
//make our pipes, our new stdin,stdout and stderr
		dup2(in[0], 0);
		dup2(out[1], 1);
		dup2(out[1], 2);

		if (DEBUG == 1) {
				printf("19 sockfd=%d\n",sockfd);
			}
// Close the other ends of the pipes that the parent will use, because if
// we leave these open in the child, the child/parent will not get an EOF
// when the parent/child closes their end of the pipe.
//
		close(in[1]);
		close(out[0]);

		if (DEBUG == 1) {
				printf("20 sockfd=%d\n",sockfd);
			}
//Over-write the child process with the hexdump binary
		execl("/bin/sh", "sh", "-C", (char *) NULL);
		error("could not open shell");
		if (DEBUG == 1) {
				printf("21 sockfd=%d\n",sockfd);
			}
	}

//printf("Spawned 'hexdump -C' as a child process at pid %d\n", pid);

//This is the parent process
// Close the pipe ends that the child uses to read from / write to so
// the when we close the others, an EOF will be transmitted properly.
//
	close(in[0]);
	close(out[1]);

	if (DEBUG == 1) {
			printf("22 sockfd=%d\n",sockfd);
		}

	printf("<- %s", bufParcedCommand);
//Write some data to the childs input
	write(in[1], bufParcedCommand, strlen(bufParcedCommand));

	if (DEBUG == 1) {
			printf("23 sockfd=%d\n",sockfd);
		}

// Because of the small amount of data, the child may block unless we
// close it's input stream. This sends an EOF to the child on it's
// stdin.
//

	if (DEBUG == 1) {
			printf("24 sockfd=%d\n",sockfd);
		}

	close(in[1]);

	if (DEBUG == 1) {
			printf("25 sockfd=%d\n",sockfd);
		}

// Read back any output
	n = read(out[0], buffer, 250);
	buffer[n] = 0;
	printf("-> %s", buffer);

	if (DEBUG == 1) {
			printf("26 sockfd=%d\n",sockfd);
		}
}

void error(char *s) {
	perror(s);
	exit(1);
}

/*
 #define PORT "3490"  // the port users will be connecting to

 #define BACKLOG 10     // how many pending connections queue will hold


 void sigchld_handler(int s) {
 // waitpid() might overwrite errno, so we save and restore it:
 int saved_errno = errno;

 while (waitpid(-1, NULL, WNOHANG) > 0)
 ;

 errno = saved_errno;
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

 freeaddrinfo(servinfo); // all done with this structure

 if (p == NULL) {
 fprintf(stderr, "server: failed to bind\n");
 exit(1);
 }

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
 if (send(new_fd, "Hello, world!", 13, 0) == -1)
 perror("send");





 close(new_fd);
 exit(0);
 }
 close(new_fd);  // parent doesn't need this
 }

 return 0;
 }





 void error(char *s);
 char *data = "Some input data\n";
 void pipe();


 void pipe()
 {
 int in[2], out[2], n, pid;
 char buf[255];

 //In a pipe, xx[0] is for reading, xx[1] is for writing
 if (pipe(in) < 0) error("pipe in");
 if (pipe(out) < 0) error("pipe out");

 if ((pid=fork()) == 0) {
 //This is the child process

 // Close stdin, stdout, stderr
 close(0);
 close(1);
 close(2);
 //make our pipes, our new stdin,stdout and stderr
 dup2(in[0],0);
 dup2(out[1],1);
 dup2(out[1],2);

 // Close the other ends of the pipes that the parent will use, because if
 // we leave these open in the child, the child/parent will not get an EOF
 // when the parent/child closes their end of the pipe.
 //
 close(in[1]);
 close(out[0]);

 //Over-write the child process with the hexdump binary
 execl("/usr/bin/hexdump", "hexdump", "-C", (char *)NULL);
 error("Could not exec hexdump");
 }

 printf("Spawned 'hexdump -C' as a child process at pid %d\n", pid);

 //This is the parent process
 // Close the pipe ends that the child uses to read from / write to so
 // the when we close the others, an EOF will be transmitted properly.
 //
 close(in[0]);
 close(out[1]);

 printf("<- %s", data);
 //Write some data to the childs input
 write(in[1], data, strlen(data));

 // Because of the small amount of data, the child may block unless we
 // close it's input stream. This sends an EOF to the child on it's
 // stdin.
 //
 close(in[1]);

 // Read back any output
 n = read(out[0], buf, 250);
 buf[n] = 0;
 printf("-> %s",buf);
 exit(0);
 }

 void error(char *s)
 {
 perror(s);
 exit(1);
 }


 */
