#include <unistd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wslblock.c>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef ENABLE_PAM
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#endif

int STREQ(char* a, char* b){
    return strcmp(a,b) == 0;
}
char *arg2cmd(int argc,char* argv[]){
    size_t size = 1;
    for(int i=0;i<argc-1;i++){
        size += strlen(argv[i+1])+1;
    }
    char *cmd=malloc(size*sizeof(char));
    strcpy(cmd,"");
    for(int i=0;i<argc-1;i++){
        strcat(cmd,argv[i+1]);
        strcat(cmd," ");
    }
    return cmd;
}
#ifdef ENABLE_PAM
static struct pam_conv conv = {
    misc_conv,
    NULL
};

int auth(char* pass){
    pam_handle_t *pamh=NULL;
    int retval;
    uid_t uid = getuid();
    if(uid != 0){
        retval = pam_start("su", "root", &conv, &pamh);
        if (retval == PAM_SUCCESS){
            retval = pam_authenticate(pamh, 0);
        }else{
            return 0;
        }
        if (retval == PAM_SUCCESS){
            retval = pam_acct_mgmt(pamh, 0);
        }else{
            return 0;
        }
    }
    return retval == PAM_SUCCESS;
}

#else
int auth(char* pass){
    wsl_block();
    uid_t uid = getuid();
    char *unencrypted="", *encrypted="", *correct="";
    if(uid != 0){
        setuid(0);
        if(getuid()!=0){
            fprintf(stderr,"Failed to set uid. (setuid error)\n");
            return 7;
        }
        struct spwd *sp = getspnam ("root");
        correct = sp->sp_pwdp;
        if(STREQ(pass,"")){
            pass = getpass ("Password:");
        }
        unencrypted = pass;
        encrypted = crypt (unencrypted, correct);
    }
    return uid == 0 || STREQ (encrypted, correct);
}
#endif
int auth_crypt(char* crypt){
    uid_t uid = getuid();
    char* correct="";
    struct spwd *sp = getspnam ("root");
    correct = sp->sp_pwdp;
    return uid == 0 || STREQ (crypt, correct);
}

char* which(char* cmd){
    char* fullPath = getenv("PATH");
    struct stat buffer;
    int exists;
    char* fileOrDirectory = cmd;
    char *fullfilename = malloc(1024*sizeof(char));

    char *token = strtok(fullPath, ":");

    /* walk through other tokens */
    while( token != NULL )
    {
        sprintf(fullfilename, "%s/%s", token, fileOrDirectory);
        exists = stat( fullfilename, &buffer );
        if ( exists == 0 && ( S_IFREG & buffer.st_mode ) ) {
            char ret[strlen(fullfilename)];
            strcpy(ret,fullfilename);
            return (char*)fullfilename;
        }

        token = strtok(NULL, ":"); /* next token */
    }
    return "";
}
