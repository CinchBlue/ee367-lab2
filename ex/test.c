#include <stdio.h>
#include <stdlib.h>

int main() {
    int i = 0;
    for(; i < 10; ++i) {
         if (fork() == 0) { /* child */
             printf("Hello CHILD: %d\n", i);
             exit(EXIT_SUCCESS);
         } else { /* parent  */
             printf("Hello PARENT: %d\n", i);
             wait();
         }
    }
    /*
    We're going to use a pipe.
        - pipe() requires a PID array of two elements.
        - fd[0] is the read-end of the pipe.
        - fd[1] is the write-end of the pipe.

    */

    /*
    The network ID:
        - Have your:
            - IP address!!!
            - TCP port number!!!
    */

    /*
    The lab assignment:
        - 
    */
} 
