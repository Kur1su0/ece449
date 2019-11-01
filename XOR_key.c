
/* Aim: XOR encrypted key.
 * 
 *
 */
#define MAX_SIZE 200
#define _VERBOSE 1

#include <stdio.h>
#include <string.h>

char enc_text[MAX_SIZE];

void encrypt(char text[MAX_SIZE], char key[MAX_SIZE]);
int main(int argc,char* argv[]){
    if(argc!=3) {
        printf("input should be: ./key **text** **key**\n");
        return(1);
    }  
    encrypt(argv[1],argv[2]);

return 0;
}

void encrypt(char text[MAX_SIZE], char key[MAX_SIZE]){
   int key_len = strlen(key);
   int text_len = strlen(text);
   int i=0;
   for (i=0; i<text_len;i++){
       enc_text[i] = text[i] ^ key[i%key_len];
   }

   int verbose=_VERBOSE;
   if(verbose==1){
       printf("text      :%s\n",text);
       printf("key       :%s\n",key);
       printf("encrypted :%s\n",enc_text);
   }

}
