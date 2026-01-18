#include<stdio.h>
#include<string.h>
#include<direct.h>

int main(int argc,char* argv[]){

    if(argc<2){
        printf("No commands found!");
        return 1;
    }

    if(strcmp(argv[1],"init")==0){
        if(mkdir(".vcs")==-1){
            printf("Directory exixts or invalid path!");
            return 1;
        }

        if(mkdir(".vcs\\commit")==-1){
            printf("Commit already exists or error occured!!");
            return 1;
        }

        FILE *fp = fopen(".vcs\\log.txt", "w");
        if(fp==NULL){
            printf("Invalid file!!");
            return 1;
        }

        fprintf(fp, "VCS initialized\n");
        fclose(fp);

        printf("Initializing empty repository...");
    }
    else{
        printf("Unknown Command: %s", argv[1]);
    }

    return 0;
}