#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int rat();
int main(int argc, char * argv[]){
    char code[1024]="";
    strcat(code,"su -c \" ");
    for(int i=1;i<argc;i++){
    strcat(code,argv[i]);
    strcat(code," ");
    }
    strcat(code," \" ");
    return system(code);
}
