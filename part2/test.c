#include <stdio.h>

int main() {
    char buf[256];
   
    // const pointer to character array buffer
    char* * const ptr_buf = (char** const)&buf;

    char* * const * const ptr_ptr_buf = (char** const * const)ptr_buf;

    printf("%s\n", *ptr_buf);

    return 0;
}
