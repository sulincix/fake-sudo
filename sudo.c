#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>

int main(int argc, char * argv[]){
   int i=0;
   int size=0;
   for(i=0;i<argc;i++){
   	size=size+(sizeof(char)*strlen(argv[i]));
   }
   size=size+sizeof(char);
   char *code=malloc(size);
   strcpy(code,"exec ");
   for(i=1;i<argc;i++){
        strcat(code,argv[i]);
        strcat(code," ");
    }
    char *cmd[]={"su","-s","/bin/sh","--preserve-environment","-c",code,NULL};
    setenv("USER","root",1);
    setenv("HOME","/root",1);
    return execvp(cmd[0], cmd);
}
