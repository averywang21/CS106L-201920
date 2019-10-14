
// =========================  C++ Way  ==============================

#include <iostream>

int hello_cpp() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}

// =========================  C Way  ==============================

#include "stdio.h"
#include "stdlib.h"

int hello_c() {
    printf("%s", "Hello, world!\n");
    return EXIT_SUCCESS;
}


// =========================  Assembly Way  ==============================

#include "stdio.h"
#include "stdlib.h"

/*
 * Wrapper function for convenience
 */
void myputs(char *s) {
    puts(s);
}

/*
 * This will probably not work on your computer.
 * Assembly is not at all portable; a good
 * reason to avoid using it!
 *
 * Those of you who have taken 107 should
 * be able to somewhat see what is happening here.
 */
int hello_as() {
    /* The assembly literally writes the hex representation
     * of as big a portion of the string as it can into the addresses
     * at range rsp to rsp + 0xd. That range is exactly 12 bytes long
     * as there are 12 characters in the "Hello, wordl!" string.
     */
    asm("sub    $0x20,%rsp\n\t"
        "movabs $0x77202c6f6c6c6548,%rax\n\t"   // moves "Hello, w" portion to mem at $rsp
        "mov    %rax,(%rsp)\n\t"
        "movl   $0x646c726f, 0x8(%rsp)\n\t"     // moves "orld"  portion to mem at $rsp + 8
        "movw   $0x21, 0xc(%rsp)\n\t"           // moves "!" portion to mem at $rsp + 12
        "movb   $0x0,0xd(%rsp)\n\t"             // moves string null terminator to mem at $rsp + 13
        "leaq    (%rsp),%rax\n\t"               // loads address of $rsp as first argument to puts
        "mov    %rax,%rdi\n\t"
        "call  __Z6myputsPc\n\t"                // calls puts
        "add    $0x20, %rsp\n\t"
    );
    return EXIT_SUCCESS;
}


int main() {
    hello_cpp();
    hello_c();
    hello_as();
}
