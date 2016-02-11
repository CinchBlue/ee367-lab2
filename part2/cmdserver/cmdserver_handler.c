#include "cmdserver_handler.h"

/*
** We have created our own <msg> struct to hold data to be sent and received.
**
** struct msg {
**      size_t length;
**      void*  data;
** };
**
*/



/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/



/*
** The purpose of the function below is to do most of the behavior-related
** processing with the client.
**
** In other words, put the real communication code here. 
*/




/*
** - Returns 0 on normal termination; -1 or less on an ERROR.
*/
int server_main(int socket_fd) { 

  /* 
  ** - We have just accepted the connnection. No messages have been sent back
  **   back and forth yet.
  **
  ** - Do any initial behavior, and then go into the main loop
  **.
  ** - Use recv() and send() to read and write data.
  */
  struct msg message;
  msg.data = (void*)("Hello world!");
  msg.length = sizeof("Hello world!");

  if (send(socket_fd, msg.data, msg.length, 0) == -1) {
      perror("send");
  
      // Close our socket (REMEMBER TO DO THIS!)
      close(new_fd);
      exit(0);
  }
}
