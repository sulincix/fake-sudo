#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>

int main(int argc, char * argv[]){
    char *code=malloc(sizeof(char)*1024);
    int i=1;
    strcpy(code,"exec ");
    while(i<argc){
        strcat(code,argv[i]);
        strcat(code," ");
        i++;
    }
    char *cmd[]={"su","--preserve-environment","-c",code,NULL};
    setenv("USER","root",1);
    setenv("HOME","/root",1);
    return execvp(cmd[0], cmd);
}
