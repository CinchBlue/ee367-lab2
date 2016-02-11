#include "client_main.h"

#include <stdio.h>
#include <string.h>
#include <memory.h>

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



/*
** parse_client_choice()
**      Parses a string and returns the correct client choice.
**
**      str
**          The string to parse. We use <string.h> to do so.
**
**      CLIENT_CHOICE(return)
**          The enum value of the choice the user input. Can be invalid.
*/
CLIENT_CHOICE parse_client_choice(char* str) {
    /* 
    ** Remove the front whitespace. Find the first character to start parsing.
    */
    /* While the current character is not a letter or the end... */
    while (isspace(*str) && (*str) != '\0') {
        /* Increment the pointer to the next character. */
        ++str;
        printf("STR POINTER: %p\n", str);
    }
    
    int i = strlen(str);
    printf("STRLEN OF BEGIN TOKEN PARSE: %d\n", i);

    /* CLIENT_CHOICE_INVALID: We reached the end of the string. */
    if ( (*str) == '\0' ) {
        return CLIENT_CHOICE_INVALID;
    } 
    /* CONTINUE: Only if:
    **      - The character is the first non-whitespace and is a letter.
    **      - The character is not the end of the string
    */

    /**************************************************************************
    ** BEGIN: PARSING STRING
    **************************************************************************/

    /* Compare the string repeatedly to each of the possiblities. */
    /* Cannot use switch(str) unfortunately. */

    /* Match to the possibilites, one by one. 0 means true. */
    if (strncmp(str, "list", sizeof("list")-1) == 0) {
        return CLIENT_CHOICE_LIST;
    } else if (strncmp(str, "check", sizeof("check")-1) == 0) {
        return CLIENT_CHOICE_CHECK;
    } else if (strncmp(str, "display", sizeof("display")-1) == 0) {
        return CLIENT_CHOICE_DISPLAY;
    } else if (strncmp(str, "download", sizeof("download")-1) == 0) {
        return CLIENT_CHOICE_DOWNLOAD;
    } else if (strncmp(str, "quit", sizeof("quit")-1) == 0) {
        return CLIENT_CHOICE_QUIT;
    } else if (strncmp(str, "help", sizeof("help")-1) == 0) {
        return CLIENT_CHOICE_HELP;
    } else {
        /* INVALID: Could not match the string to an input. */
        return CLIENT_CHOICE_INVALID;
    }

    /**************************************************************************
    ** END: PARSING STRING
    **************************************************************************/
    
    /*    
    ** All execution paths end in the if-else branches above. No tail return.
    */
} 


/*
** prompt()
**      Prompts the user for input.
**
**      str
**          The prompt to put before asking for input.
**      buffer
**          The character buffer to write to.
**      maxsize
**          The maximum number of bytes to writer to the buffer.
**      (int)RETURN
**          0 in the case of no error.
**          -1 in the case where the buffer cannot hold all of the input.
**              OR in the case of a read error.
*/ int prompt(const char* str, char* buffer, int maxsize) {
    /* Print out the message first. */
    printf("%s", (char*)str);
    /* Get the input using fgets() */
    if (fgets(buffer, maxsize, stdin) == NULL) {
        /* ERROR: Read did not occur correctly. Do not trust buffer. */
        fprintf(stderr, "ERROR: prompt() encountered a read error.\n");
        return -1;
    } else {
        return 0;
        #ifdef DEBUG
        printf("prompt() read in: %s\n", buffer);
        #endif
    }
}


/* Not responsible for closing the socket. */
int client_main(int sockfd, char* * const buffer, int buffer_maxsize ) {

    

}

int main() {

    char buf[MAXDATASIZE];              // The input buffer.
    char tokens[2][MAXDATASIZE];        // The tokens buffer. We only need 2 so far.

    // Prompts the user for input into a character buffer up to a maximum size.
    // Note that the string length will end up being the (maxsize-1)
    prompt("client367: ", buf, 256);

    // Tokenizes the input into tokens.

    // Take a token.
    //char* strtok_saveptr1 = NULL;
    //do {    
    //    strtok_saveptr1 = strtok_r(buf, 
        

    printf("PARSED INPUT: %d\n", parse_client_choice(buf));

    printf("Got: %s\n", buf);
    return 0;
}
