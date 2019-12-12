/* 
  Name - BufferOverflowDemo.C 
  Date - 1/1/2010
  Programmer - R. R. Brooks

  Purpose - Show very simple buffer overflow and how to get
  it working using emacs/gdb.
 
  Input - Input a string.

  Output - Some statements allowing students to see what is
  going wrong.

 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void InputStringNoCheck(void)
{
  char buffer[]={'@','@','@','@','@','\x00'};
  int  input;
  int  i=0;

  printf("Buffer= %s\n",buffer);
  input=getchar();
  
  while(input != (int)'\n'){
    printf("input=%c, binary=%x, i=%d\n",input,input,i);
    buffer[i++]=input;
    printf("Buffer= %s\n",buffer);
    input=getchar();
  }
  buffer[i]=0;
  printf("Buffer= %s\n",buffer);
}

void recursion(int i)
{
  if(i>0){
    printf("recurse=%d\n",i);
    recursion(i-1);
    printf("recurse=%d\n",i);
  }else{
    InputStringNoCheck();
  }
}

int main(int argc, char **argv)
{
  int recurse=6;

  printf("Before recursion\n");
  recursion(recurse);
  printf("After recursion\n");
  return(1);
}
