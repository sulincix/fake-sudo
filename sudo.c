#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
    char code[1024]="";
	strcat(code,"su --preserve-environment --command \" ");	
    int i=1;
    while(i<argc){
        strcat(code,argv[i]);
        strcat(code," ");
        i++;
    }
    strcat(code," \" ");
    return system(code);
}
