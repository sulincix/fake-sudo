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
    setenv("HASH",HASH,1);
    if(system("[ $HASH == $(sha1sum $(which gtk-sudo) | cut -f 1 -d ' ') ]")!=0){
        return 1;
    }
    if(auth(pass)){
        unsetenv("PASSWORD");
        setuid(0);
        return system(arg2cmd(argc,argv));
    }
    fprintf(stderr,"Authentication failure\n");
    return 1;
}
