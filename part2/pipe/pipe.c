#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void error(char* s);
char* data = "Some input data\n";

int main() {

    int in[2][2], out[2][2], n, pid;
    char buf[255];

    int process_no = 0;

    while (process_no < 2) {
         /* in A pipe, xx[0] is for reading, xx[1] is for writing */
         if (pipe(in[process_no]) < 0)
             error("pipe in");
         if (pipe(out[process_no]) < 0)
             error("pipe out");

         /* This is the child process. */
         if ((pid=fork()) == 0) {
             int no = process_no;
             /* Close stdin, stdout, stderr */
             close(0);
             close(1);
             close(2);
             /* make the pipes our new stdin, stdout, and stderr */
             dup2(in[no][0], 0);
             dup2(out[no][1], 1);
             dup2(out[no][1], 2);

             /* Close the other ends of the pipes that the parent will use, because
              * if we leave these open in the CHILD, the child/parent will not get
              * an EOF when the parent/child closes their end of the pipe.
              */

             close(in[no][1]);
             close(out[no][0]);

             /* Over-write the child process with the hexdump binary */
             execl("/usr/bin/hexdump", "hexdump", "-C", (char*)NULL);
             error("Could not exec hexdump.");
         }
         printf("Spawned 'hexdump -C' as a child process at pid %d\n", pid);

         /* This is the parent process */
         /* Close the pipe ends that the child uses to read from / write to so that
          * when we close the others, the EOF will be transmitted properly.
          */
         close(in[process_no][0]);
         close(out[process_no][1]);

         printf("<- %s", data);
         /* Write some data to the childs input */
         write(in[process_no][1], data, strlen(data));

         /* Because of the small amount of data, the child may block unless we close
          * its input stream. This sends an EOF to the child on its stdin.
          */
         close(in[process_no][1]);

         /* Read back any output */
         n = read(out[process_no][0], buf, 250);
         buf[n] = 0;
 
         printf("-> %s", buf);
            
         ++process_no;
    }

    exit(0);
}

void error(char* s) {
    perror(s);
    exit(1);
}
