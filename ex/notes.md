# Ideas

C: connection request
S: listen and accept requests
C: listen for a connection, wait for response, on acceptance...
C: send a command
S: receive a command
S: do the command
S: send a response (terminate?)
C: output response

## Part 1:

- Run the client-server programs from Beej's guide. Compile, run, verify.

## Part 2:

- Have the server execute "ls" everytime it gets a connection reqestion from the client. The output of "ls" goes to the console of the server. The server then terminates the connection.

## Part 3:

- Modify the modify the clients so that it accepts the three commands (list, check filename, and get filename) from the user, starts a connection per command, sends a message.
