#include<io.h>
#include<stdio.h>
#include<string.h>
#define MAXSIZE 200
void get_exe_file();
int main(void)
{
    
   
    get_exe_file("*");
    return 0;
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
					sprintf(next_dir_path,"%s/%s",dir_path,fileinfo.name);
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