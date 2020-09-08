#include "apue.h"
#include<fcntl.h>
#include<error.c>
#include <stdio.h>

int main(void)
{
        int oldfd, newfd;
        long length;
        char *buffer;

        oldfd=open("file",O_RDWR);

        FILE *fp = fdopen(oldfd, "rb");

        if(fp){
                fseek(fp, 0, SEEK_END);
                length = ftell(fp);
                printf("length: %ld\n", length);

                fseek(fp, 0, SEEK_SET);
                buffer = (char*)malloc(length);
                if(buffer){
                        fread(buffer, sizeof(char), length, fp);

                }
                fclose(fp);
        }

        newfd=open("newfile",O_RDWR|O_CREAT);
        FILE *newfp = fdopen(newfd, "w");

        if(newfp){
                for(int i=0;i<length;i++)
                {
                        if((*buffer)=='\0'){
                                buffer++;
                        }
                        else
                        {
                                fwrite(buffer,sizeof(char),sizeof(char),newfp);
                                buffer++;
                        }
                }
                //fwrite(buffer, sizeof(char), length, newfp);
        }
        else err_quit("newfp error");
        fclose(newfp);

        exit(0);

}

