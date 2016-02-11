#ifndef CLIENT_MAIN_H
#define CLIENT_MAIN_H


#include "common.h"

/*
**
** 1. sockfd - the socket of the server.
** 2. buffer - a constant pointer to the character array buffer set in client.c
** 3. buffer_max-size - the max size of the buffer
*/


/*
** enum of all the choices the client can make.
*/
typedef enum { 
    CLIENT_CHOICE_INVALID,
    CLIENT_CHOICE_LIST,
    CLIENT_CHOICE_CHECK,
    CLIENT_CHOICE_DISPLAY,
    CLIENT_CHOICE_DOWNLOAD,
    CLIENT_CHOICE_QUIT,
    CLIENT_CHOICE_HELP
} CLIENT_CHOICE;                                 


int client_main(int sockfd, char* * const buffer, int buffer_maxsize ); 

#endif /* CLIENT_MAIN_H */
