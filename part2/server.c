/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>              /* IO                       */
#include <stdlib.h>             /* STANDARD LIBRARY         */
#include <unistd.h>             /* POSIX DEFINITIONS        */
#include <errno.h>              /* ERROR MACROS w/ STATIC MEMORY LOCATION FOR 
                                   ERRORS */
#include <string.h>             /* STRING MANIPULATION AND MEMORY */
#include <sys/types.h>          /* USED FOR DATA TYPES FOR STANDARD LIBRARY  */
#include <sys/socket.h>         /* PROBABLY THE SOCKET      */
#include <netinet/in.h>         /* INPUT TYPE HEADER FOR INTERNET STUFF */
#include <netdb.h>              /* NETWORK DATABASE OPERATIONS -- LOOKUP 
                                   and DNS I think    */
#include <arpa/inet.h>          /* INTERNET STUFF?? used for host network
                                   endian conversions       */
#include <sys/wait.h>           /* POSIX wait and fork for processes -
                                   Windows problems     */
#include <signal.h>             /* Used for POSIX signals for Linux.    */

/******************************************************************************
**
** BEGIN: USER INCLUDES 
**
******************************************************************************/

#include "common.h"
#include "server_main.h"
#include "client_main.h"        /* So we have the enum CLIENT_CHOICE */

/******************************************************************************
**
** END: USER INCLUDES
**
******************************************************************************/


void sigchld_handler (int s) {
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    
    /*
    ** - Loop until children exist and children have not yet changed state,
    **   or an error occurs.
    ** - Do not block.
    */
    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6
void* get_in_addr(struct sockaddr* sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    } else {
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
}

int main(void) {
    // listen on sock_fd, new connection on new_fd
    int             sockfd, new_fd;
    struct          addrinfo hints, *servinfo, *p;
    // connector's address information
    struct          sockaddr_storage their_addr;     
    socklen_t       sin_size;
    struct sigaction    sa;
    int             yes = 1;
    char            s[INET6_ADDRSTRLEN];
    int             rv;

    // Set the IP address lookup struct data.
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Get the IP address info.
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        // CONTINUE: The server has connected. 
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }
        
        // ERROR: setting the soct options didn't work.
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        
        // ERROR: Could not bind to socket. 
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);     // all done with this structure

    // ERROR: Server could not bind.
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    // ERROR: Listen did not work.
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    // WHAT.
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    /*
    ** THE MAIN LOOP WHERE WE ARE READY TO ACCEPT STUFF DO STUFF HERE.   
    */
    int num_connections = 0;

    int pipe_in[MAXCONNECTIONS][2];
    int pipe_out[MAXCONNECTIONS][2];

    // Registry of which connection spots are open or closed. This is a bool.
    int pipe_taken[MAXCONNECTIONS]; 
    // It is empty, initially. Set all to 0.
    memset((void*)pipe_taken, 0, sizeof(int)*MAXCONNECTIONS);
    
    while (1) { // main accept() loop
        /* Stall if we have reached maximum connections. */

        int k;
        

            // Release the connection from pipe_taken[pipe_no].
           // pipe_taken[pipe_no] = 0;





        k=0; 
        for(; k < MAXCONNECTIONS; ++k)
            printf("%d", pipe_taken[k]);
            printf("\n");


        if  (num_connections+1 > MAXCONNECTIONS) {
            printf("server367: Max amount of connections reached; ");
            printf("waiting for a disconnect\n");

            /* ERROR: Wait failed. Error. */
            if (wait(NULL) < 0) {
                fprintf(stderr, "ERROR: wait() failed\n");
                exit(3);
            } else {
                --num_connections;
            }
        }

        sin_size = sizeof(their_addr);

        // Accept a connection from a socket.
        new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);
        // ERROR: ACCEPTING DID NOT WORK!
        if (new_fd == -1) {
            perror("accept");
            continue;
        } else {
            /* Upon accepting a connection, increment the connection counter. */
            ++num_connections;
        }

	    /* Log the current connection number for the child. */
        /* Find an open spot. */
        int current_connection_no;
        {
            int j = 0;
            /* We'll do a basic linear search. */
            for(; j < MAXCONNECTIONS && pipe_taken[j] == 1; ++j);
            printf("server367: new opening for connection found at slot %d\n", j);
            /* Set the current connection number when a spot is found. */
            current_connection_no = j;
            /* Increase the total amount of connections. */
            ++num_connections;
            j = 0;
        }
        /* Reserve the found slot. */ 
        pipe_taken[current_connection_no] = 1; 

        k=0; 
        for(; k < MAXCONNECTIONS; ++k)
            printf("%d", pipe_taken[k]);
            printf("\n");

        // Convert the IP address to a string.
        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s,
            sizeof(s));
        printf("server367: got connection from %s\n", s);

        /* Create pipes to communicate with the child process here. */
        /* In a pipe, xx[0] is for reading, xx[1] is for writing */
        if (pipe(pipe_in[current_connection_no]) < 0) {
            perror("pipe in");
            exit(2);
        }
        if (pipe(pipe_out[current_connection_no]) < 0) {
            perror("pipe out");
            exit(2);
        }

        int pid = fork();
        /*
        ** THIS IS WHERE WE BEGIN TO INTERACT WITH CONNECTIONS.
        ** THE PROGRAM FLOW SHOULD GO INTO SOME SORT OF PROCEDURE FUNCTION.
        ** 
        ** PASS BY REFERENCE!!!!!!
        */
        if (pid == 0) { // this is the child process

            int pipe_no = current_connection_no;
            // First, close the parent process' socket.
            close(sockfd);
        
            /* Close the stdout and stderr sockets. */
            close(0);
            close(1);
            close(2);
            /* Make the pipe to the parent out stdin, stdout and stderr. */
            dup2(pipe_in[pipe_no][0], 0);
            dup2(pipe_out[pipe_no][1], 1); 
            dup2(pipe_out[pipe_no][1], 2);
            /* Close one side of the read/write pipes. */
            close(pipe_in[pipe_no][1]);
            close(pipe_out[pipe_no][0]);

            // Send a message; check for an error.
            if (send(new_fd, "Hello, world!", 14, 0) == -1)
                perror("send");
             
/******************************************************************************
*******************************************************************************
******************************************************************************/
            /*
            **
            ** server_main is where we handle connections with clients.
            **
            ** HERE IS WHERE WE HAVE OUR MAIN LOOP
            */
            int server_main_return = -1;
            if (server_main_return = server_main(new_fd) != 0) {
                fprintf(
                    stderr,
                    "server367: ERROR(%d): Abnormal termination of connection with client.\n",
                    server_main_return
                );
            } else {
                fprintf(stdout, "server367: OK: Successful termination of connection\n");
            } 

            fprintf(stdout, "server367: Releasing pipe[%d]\n", pipe_no);

            // Close our parent-child pipes to flush. 
            close(pipe_in[pipe_no][0]);
            close(pipe_out[pipe_no][1]);
            // Close our socket (REMEMBER TO DO THIS!)
            close(new_fd);
            


            exit(0);
        }    

/******************************************************************************
** PARENT
******************************************************************************/
        
        // PARENT: 



        // PARENT: Close our reference to the child process' socket.
        close(new_fd);  // parent doesn't need this 
        /* Parent also needs to close one side of the in/out sockets. */
        close(pipe_in[current_connection_no][0]);
        close(pipe_out[current_connection_no][1]);

        char buffer[512] = "\0"; 
        {
            int i = 0; 
	        /* Go through the connections, check for reads. */
            for (; i < MAXCONNECTIONS; ++i) {
		 
		        if (pipe_taken[i] == 1) { 
		        	printf("\tserver367: Pipe[%d] is occupied.\n", i);
                    read(pipe_out[i][0], buffer, 512); 
                    buffer[512] = '\0';
                    fprintf(stdout, "\t(%s): %s", s, buffer);
		        }
            } i = 0;
        }
    }

/******************************************************************************
*******************************************************************************
******************************************************************************/

    return 0;
}
