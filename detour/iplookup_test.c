#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    int                     status;
    struct addrinfo         hints;
    struct addrinfo*        servinfo;
    char*                   node; 
    const char* service = "3522";

    /* Must have at least 2 arguments to run the program and look up the
    ** second argument as the "name of the host" */
    if (argc < 2) {
        fprintf(stderr, "usage: exec hostname\n");
        return 1;
    }



    /* Set the hints address info to empty. */
    memset(&hints, 0, sizeof(hints));       
    hints.ai_family     =   AF_UNSPEC;      /* IPv4 and IPv6 agnostic */
    hints.ai_socktype   =   SOCK_STREAM;    /* TCP stream sockets. */
    hints.ai_flags      =   AI_PASSIVE;     /* Fill in IP for us. */


    /* Get our OWN address info. */
    if ((status = getaddrinfo(argv[1],         /* Name of the host */
                              service,      /* Port/service */
                              &hints,
                              &servinfo)) != 0) {
        /* On error, print the error message. */
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    /* Print out the IP addresses of the address we looked up. */
    printf("IP addresses for %s:\n\n", argv[1]);
    
    struct addrinfo* p;
    /* Iteration through a linked list until we hit the NULL end marker. */
    for(p = servinfo; p != NULL; p = p->ai_next) {
        void* addr;
        char* ipver;

        /* Get the pointer to the address itself,
        ** which are different fields in IPv4 and IPv6:
        */
        if (p->ai_family == AF_INET) { /* IPv4 */
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {  /* IPv6 */
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        /* Convert the IP to a readable string using inet_ntop() */
        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(p->ai_family,
                  addr,
                  ipstr,
                  sizeof(ipstr));
        printf("  %s: %s\n", ipver, ipstr);
    }

    /* Free the addrinfo struct ONCE WE ARE DONE. */
    freeaddrinfo(servinfo);

    return 0;
}
