#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wslblock.c>

int main(int argc, char * argv[]){
   int i=0;
   int size=0;
   wsl_block();
   for(i=0;i<argc;i++){
   	size=size+(sizeof(char)*(strlen(argv[i])+1));
   }
   size=size+(6*sizeof(char));
   char *code=malloc(size);
   strcpy(code,"exec ");
   for(i=1;i<argc;i++){
        strcat(code,argv[i]);
        strcat(code," ");
    }
    umask(0022);
    if(getenv("NOENV")!=NULL){
        char* display=getenv("DISPLAY");
        clearenv();
        setenv("DISPLAY",display,1);
        setenv("TERM","sudo",1);
    }
    setenv("USER","root",1);
    setenv("HOME","/root",1);
    setenv("PATH","/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/sbin:/usb/sbin",1);
    if(getenv("FAKEROOT")!=NULL){
        char *cmd[]={"unshare","-ru","/bin/sh","-c",code,NULL};
        return execvp(cmd[0], cmd);

    }else if (getenv("NOROOT")!=NULL){
        char *cmd[]={"/bin/sh","-c",code,NULL};
        return execvp(cmd[0], cmd);
    }else{
        char *cmd[]={"su","-s","/bin/sh","-p","-c",code,NULL};
        return execvp(cmd[0], cmd);
    }
}