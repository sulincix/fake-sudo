#include <stdio.h>
#include <stdlib.h>
#include <libsudo.h>
#include <libsudo.h>

int main(int argc, char *argv[]){
    if(auth("")){
        char *cmd[argc];
        for(int i=0;i<argc-1;i++){
            cmd[i] = argv[i+1];
        }
        cmd[argc-1] = NULL;
        execvp(which(argv[1]),cmd);
    }
    fprintf(stderr,"Authentication failure\n");
    return 1;
}
