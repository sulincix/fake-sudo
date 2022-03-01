#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsudo.h>
#include <libsudo.h>
int is_live();
int main(int argc, char *argv[]){
    if(argc<2){
        fprintf(stderr,"usage: sudo [command]\n");
        return 1;
    }
    if(auth("") != 7 || is_live()){
        setenv("USER","root",1);
        setenv("HOME","/root",1);
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
        execvp(which(argv[1]),cmd);
    }
    fprintf(stderr,"Authentication failure\n");
    return 1;
}
// no password for live (for debian/ubuntu)
int is_live(){
    FILE* ff=fopen("/proc/cmdline","r");
   char *line;
   fscanf(ff,"%s",&line);
   if(strstr(line,"boot=live") != NULL || strstr(line,"boot=casper") != NULL){
       return 1;
   }
   return 0;
}
