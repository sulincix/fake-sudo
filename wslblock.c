#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wsl_block(){
   FILE* f=fopen("/proc/version","r");
   char line[1024];
   fscanf(f,"%s",&line);
   if(strstr(line,"Microsoft") != NULL || strstr(line,"microsoft") != NULL || strstr(line,"WSL") != NULL){
      exit(1);
    }
   fclose(f);
   //using shell
   if(0!=system("cat /proc/cpuinfo | grep \"microcode\" | grep \"0xffffffff\" &>/dev/null")){
      exit(1);
   }
}
