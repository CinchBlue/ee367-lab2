Client/Server Conventions
=========================

* Both the client and server are set up such that most of their actual
  behavior will be spend in the client_main() and server_main() functions.
  They both inherit the socket file descriptors needed to communicate with
  each other.
  * By doing so, we decouple most of the raw networking setup from the actual
    logic of programming the behavior of the server.


Client
------

* The client_main.h file exposes the actions that the client can take in the
  form of the CLIENT_CHOICE enum. Otherwise, there is only one function
  exposed.

* Behind the scenes, the client_main.c file holds many additional helper
  functions in order to accomplish its goals. For example, there is a
  string tokenizing function as well as a parsing function for the first token
  in order to interpret slightly different commands as the correct command.
  * For example, "TAB-SPACE-SPACElist" and "listTAB-TAB-TAB" are both "list"
    but the amount of whitespace must be taken into consideration. We have
    leveraged part of the C standard library in order to perform some of the
    parsing (specifically, strtok_r()).


Server
------

* The server_main() function is intended to spawn an additional child process
  for each command it decides to execute.

* Note: the server will terminate a request after handling a connection.
