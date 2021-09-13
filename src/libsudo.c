#include <unistd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wslblock.c>

int STREQ(char* a, char* b){
    return strcmp(a,b) == 0;
}
char *arg2cmd(int argc,char* argv[]){
    size_t size = 1;
    for(int i=0;i<argc-1;i++){
        size += strlen(argv[i+1])+1;
    }
    char *cmd=malloc(size*sizeof(char));
    strcpy(cmd,"");
    for(int i=0;i<argc-1;i++){
        strcat(cmd,argv[i+1]);
        strcat(cmd," ");
    }
    return cmd;
}
int auth(char* pass){
    wsl_block();
    uid_t uid = getuid();
    char *unencrypted="", *encrypted="", *correct="";
    if(uid != 0){
        setuid(0);
        if(getuid()!=0){
            fprintf(stderr,"Failed to set uid. (setuid error)\n");
            return 7;
        }
        struct spwd *sp = getspnam ("root");
        correct = sp->sp_pwdp;
        if(STREQ(pass,"")){
            pass = getpass ("Password:");
        }
        unencrypted = pass;
        encrypted = crypt (unencrypted, correct);
    }
    setenv("USER","root",1);
    setenv("HOME","/root",1);
    return uid == 0 || STREQ (encrypted, correct);
}
