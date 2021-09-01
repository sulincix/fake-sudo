#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wsl_block(){
   FILE* f=fopen("/proc/version","r");
   FILE* ff=fopen("/proc/cpuinfo","r");
   char line[1024];
   fscanf(f,"%s",&line);
   if(strstr(line,"Microsoft") != NULL || strstr(line,"microsoft") != NULL || strstr(line,"WSL") != NULL){
      fputs("Fucking WSL environment not allowed!\n",stderr);
      while(1);
    }
   fclose(f);
   //using shell
   int i=1;
   while(i){
       fscanf(ff,"%s",&line);
       if(strstr(line,"microcode") != NULL){
           i = 0;
           if(strstr(line,"0xffffffff") != NULL) {
               fputs("Fucking WSL environment not allowed!\n",stderr);
               while(1);
           }
       }
   }
}
