#ifndef CMDSERVER_HANLDER_H 
#define CMDSERVER_HANDLER_H

#include <string.h>

#include "cmdserver_common.h"

int server_main(int socket_fd);

/*
size_t msglen(struct msg* m);           /* Returns the length of the data. */
void*  msgdata(struct msg* m);          /* Returns the data (void*) */
void   msgset(
    struct msg* m,
    void* data,
    size_t length
);                                      /* A set function to combine assigns */
*/
#endif /* CMDSERVER_HANDLER_H */
