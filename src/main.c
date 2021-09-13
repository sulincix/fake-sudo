#include <stdio.h>
#include <stdlib.h>
#include <libsudo.h>
#include <libsudo.h>

int main(int argc, char *argv[]){
    if(auth("")){
        return system(arg2cmd(argc,argv));
    }
    fprintf(stderr,"Authentication failure\n");
    return 1;
}
