#ifndef CMDSERVER_INCLUDE_H
#define CMDSERVER_INCLUDE_H

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



#define PORT "3522"             /* The defined port number to connect to. */

#define BACKLOG 10              /* What? */

// Define a struct to send data.
// We'll use this to send transmissions.

// MAKE SURE THAT THE DATA IS NULL-TERMINATED!
struct msg {
    size_t length;
    void*  data;
};

// ACCESSOR FUNCTIONS
inline size_t msglen(struct msg* m) {
    return(m->length);
}

inline void* msgdata(struct msg* m) {
    return(m->data);
}


// MUTATOR FUNCTIONS
inline void msgset(struct msg* m, void* data, size_t length) {
    m->data = data;
    m->length = length;
}

#endif // CMDSERVER_INCLUDE_H
