#include <stdio.h>
#include <stdlib.h>
#include <libsudo.h>
#include <libsudo.h>
#include <token.h>

int main(int argc, char *argv[]){
    char *pass = getenv("PASSWORD");
    if(!STREQ(getenv("TOKEN"),TOKEN)){
        return 1;
    }
    if(auth(pass)){
        unsetenv("PASSWORD");
        setuid(0);
        if(argv==1){
            return 0;
        }
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
