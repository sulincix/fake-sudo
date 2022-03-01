#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsudo.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]){
    if(argc<2){
        fprintf(stderr,"usage: sudo [command]\n");
        return 1;
    }
    if(auth("") == 1){
        setenv("USER","root",1);
        setenv("HOME","/root",1);
        setenv("PATH","/bin:/usr/bin:/sbin/:/usr/sbin",1);
        setuid(0);
        if(getuid()!=0){
            fprintf(stderr,"Failed to set uid. (setuid error)\n");
            return 7;
        }
        char *cmd[argc];
        for(int i=0;i<argc-1;i++){
            cmd[i] = argv[i+1];
        }
        cmd[argc-1] = NULL;
        execve(which(argv[1]),cmd,envp);
    }
    fprintf(stderr,"Authentication failure\n");
    return 1;
}
