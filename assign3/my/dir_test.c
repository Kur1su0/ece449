/* virus.c
 * Aim: find all uninfected file and infected them by 
 *      1. replace oldprogram with dec.exe
 *      2. insert *.exe:virus.exe and *.exe:oldprogram.exe
 *
 *
 */

#define MAX_SIZE 200


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <dirent.h>
#include <errno.h>

#include <stdio.h>

#include <stdlib.h>

#include <sys/dir.h>

#include <sys/stat.h>

#include <string.h>


//判断是否为目录

int IS_DIR(const char* path)
{
         struct stat st;
         lstat(path, &st);
		 return S_ISDIR(st.st_mode);
}


//遍历文件夹de递归函数
void List_Files_Core(const char *path, int recursive)
{
         DIR *pdir;
         struct dirent *pdirent;
         char temp[256];
         pdir = opendir(path);
         if(pdir){              
		    while(pdirent = readdir(pdir)){
             //跳过"."和".."

                if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
                    continue;

                sprintf(temp, "%s/%s", path, pdirent->d_name);
				printf("%s\n", temp);
            //当temp为目录并且recursive为1的时候递归处理子目录
                if(IS_DIR(temp) && recursive){
                List_Files_Core(temp, recursive);
                }

            }

        }
		else{
            printf("opendir error:%s\n", path);

        }
        closedir(pdir);


}

//遍历文件夹的驱动函数


void List_Files(const char *path, int recursive)

{

    int len;
    char temp[256];
    //去掉末尾的'/'
    len = strlen(path);
    strcpy(temp, path);
    if(temp[len - 1] == '/') temp[len -1] = '\0';
    if(IS_DIR(temp)){
    //处理目录
        List_Files_Core(temp, recursive);
    }
    else{  //输出文件
    printf("%s\n", path);

    }

}


int main(int argc, char** argv)
{
    if(argc != 2){
        printf("Usage: ./program absolutePath\n");
        exit(0);
    }
    List_Files(argv[1], 1);
    return 0;

}


