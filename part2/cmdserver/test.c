#include "cmdserver_common.h"
#include <string.h>

int main() {

  struct msg m;

  msgset(&m, (void*)("Hello world!"), sizeof("Hello world!"));

  printf("m.data    = %s\n", (char*)msgdata(&m));
  printf("m.length  = %zd\n", msglen(&m));

  return 0;
}
