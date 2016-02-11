#include "client_main.h"

#include <stdio.h>
#include <string.h>
#include <memory.h>

 
/*
** tokenize_input()
**      Takes a string buffer and a 2D array of tokens such that the dimensions
**      of the buffer are [0..str_maxsize-1] and the dimensions of the token
**      array is [0..num_of_tokens*token_maxsize]
**
**      buf
**          The string to parse.
**      str_maxsize
**          The maximum size of the <buf> string.
**      tokens
**          The address of the 2D array
**      token_maxsize
**          The maximum size of a single token buffer.
**
*/
int tokenize_input(char* buf, int str_maxsize, char* tokens, int token_maxsize,
                   int token_no) {
    // Use the saveptr to be able to execute more than 1 strtok_r()
    // in parallel.
    char* strtok_saveptr1 = NULL;
    // i set the <token_count> to -1 in order to have the scheme used for
    // the incrementation below.
    int token_count = -1;
    // take a token.
    char* temp = strtok_r(
                buf,
                " \t\n\v\f\r",
                &strtok_saveptr1
            );
    // here, we use the whitespace characters as delimiters.
    while ( temp != NULL && (++token_count) < token_no) {
        // every time we make a new token, increment the token count.
        // copy the token to the tokens buffer.
        memcpy(
            &tokens[token_count*token_maxsize],
            temp,
            ((strlen(temp)+1) > token_maxsize) ?
                (token_maxsize) :
                (strlen(temp)+1)
        );
        // make sure that the pointer to the strtok_r() string is null
        // while still reading in tokens.
        temp = strtok_r(NULL, " \t\n\v\f\r", &strtok_saveptr1);
    }

    return token_count;
}


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
    int i = strlen(str);

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
    if (strncmp(str, "list", strlen(str)) == 0) {
        return CLIENT_CHOICE_LIST;
    } else if (strncmp(str, "check", strlen(str)) == 0) {
        return CLIENT_CHOICE_CHECK;
    } else if (strncmp(str, "display", strlen(str)) == 0) {
        return CLIENT_CHOICE_DISPLAY;
    } else if (strncmp(str, "download", strlen(str)) == 0) {
        return CLIENT_CHOICE_DOWNLOAD;
    } else if (strncmp(str, "quit", strlen(str)) == 0) {
        return CLIENT_CHOICE_QUIT;
    } else if (strncmp(str, "help", strlen(str)) == 0) {
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
/*
** client_main()
**      The main loop for the client.
**      It is called when the server and client have established a connection.
**      Use this as a sort of "main" for the client's interaction with the
**      server.
**      This function is not responsible for closing the socket file descript-
**      or. It is instead handled by the main() function for the client.
**
**      sockfd
**          The socket file descriptor for the server.
**          At the start of this function, both the in and out data connections
**          remain open.
**      buffer
**          A pointer to the buffer of characters that is passed to the
**          function. Use this and only this buffer for storing data INCOMING
**          from the server.
**      buffer_maxsize
**          The maximum size of the INCOMING data buffer.
*/
int client_main(int sockfd, char* buffer, int buffer_maxsize ) {
    /* Start in an INVALID state for the client choice. */
    CLIENT_CHOICE client_choice = CLIENT_CHOICE_INVALID;
    /* Assume normal termination client_main(). Change upon ERROR. */
    int return_status = 0;

    int numbytes = 0;
    // If the number of bytes indicates a FAIL condition, exit. 
    if ((numbytes = recv(sockfd, buffer, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        return 1;
    }

    // This will fill up the [0:MAXDATASIZE-2] index, actually.

    // It will receive [MAXDATASIZE-1] bytes (but we use zero-indexing so yeah)
    
    // Make sure that the last byte is NULL or \0 terminated.
    // This will set the VERY last byte in the array to NULL to make it easier
    // to parse using strings.
    buffer[numbytes] = '\0';
    printf("client: received '%s'\n", buffer);




    /* Set a zero-length string as the default value for the console buffer. */
    char console_buffer[MAXDATASIZE];
    char tokens[2][MAXDATASIZE];

    /* Set the buffers to 0. */
    memset(console_buffer, 0, sizeof(char)*MAXDATASIZE);
    memset(tokens, 0, sizeof(char)*2*MAXDATASIZE);

    /**************************************************************************
    ** WELCOME PROMPT: 
    **************************************************************************/
    printf("Welcome to the EE367 Client/Server Project!   \n");
    printf("================= COMMANDS ==================\n");
    printf("(list, check <file name>, display <file name>,\n");
    printf(" download <file name>, quit, help)\n\n");

    /**************************************************************************
    **  MAIN LOOP:
    **************************************************************************/
    do {
        /* Set the buffers to 0. */
        memset(console_buffer, 0, sizeof(char)*MAXDATASIZE);
        memset(tokens, 0, sizeof(char)*2*MAXDATASIZE);
        /* Ask for input with the prompt. */
        prompt("client367: ", console_buffer, MAXDATASIZE);
        /* Parse the prompt into tokens. */
        int token_count = tokenize_input(
           console_buffer,
           MAXDATASIZE,
           (char*)(tokens),
           MAXDATASIZE,
           2
        );
        /* Get the command asked for: */
        client_choice = parse_client_choice(tokens[0]);




        /* Send the appropriate data according to the command. */
        switch (client_choice) {
            case CLIENT_CHOICE_LIST:
                //if (client_list(sockfd, buffer, buffer_maxsize) < 0) { }
                break;
            
            case CLIENT_CHOICE_CHECK:
                //if (client_check(sockfd, buffer, buffer_maxsize) < 0) { }
                break;

            case CLIENT_CHOICE_DISPLAY:
                //if (client_display(sockfd, buffer, buffer_maxsize) < 0) { }
                break;

            case CLIENT_CHOICE_DOWNLOAD:
                //if (client_download(sockfd, buffer, buffer_maxsize) < 0) { }
                break;

            case CLIENT_CHOICE_QUIT:
                printf("Quitting program...\n");
                break;

            case CLIENT_CHOICE_HELP: 
                //client_help(); 
                break;

            case CLIENT_CHOICE_INVALID:
            default:
                printf("Invalid input. Please input a valid command.\n");
                break;
        }

        /* Continue to loop until we quit. */
    } while (client_choice != CLIENT_CHOICE_QUIT);

    return return_status;
}


/*
** A test main() for debugging functions within this C file.
*/
#ifdef DEBUG
int main() {

    char buf[MAXDATASIZE];              // The input buffer.
    char tokens[2][MAXDATASIZE];        // The tokens buffer. We only need 2 so far.

    // Prompts the user for input into a character buffer up to a maximum size.
    // Note that the string length will end up being the (maxsize-1)
    prompt("client367: ", buf, 256);

    // Tokenizes the input into tokens.
    int token_count = tokenize_input(
        buf,
        MAXDATASIZE,
        (char*)(tokens),
        MAXDATASIZE,
        2
    );

    printf("TOKEN COUNT: %d\n", token_count);


    printf("TOKEN0: %s\n", tokens[0]);
    printf("TOKEN1: %s\n", tokens[1]);
    
    // Note that the strtok_r() function will modify the original string!!!
    printf("ORIGINAL INPUT? NOPE, TY strtok_r(): %s\n", buf);

    printf("PARSED FIRST KEYWORD: %d\n", parse_client_choice(tokens[0]));

    printf("Got: %s\n", buf);



    return 0;
}
#endif /* DEBUG */
