#include<stdio.h>
#include<string.h>
#include<direct.h>

int repoexist(){
    FILE *fp = fopen(".vcs/log.txt", "r");

    if(fp==NULL){
        return 0;
    }

    fclose(fp);
    return 1;
}

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

        mkdir(".vcs/commit");

        FILE *fp = fopen(".vcs/log.txt", "w");
        if(fp==NULL){
            printf("Invalid file!!");
            return 1;
        }

        fprintf(fp, "0");
        fclose(fp);

        printf("Initialized a VCS Repository in .vcs\n");
    }
    else{
        if(!repoexist()){
            printf("Not a ./vcs repository!");
            return 1;
        }
        if(strcmp(argv[1],"commit")==0){

            //Commit logic pending brahh

        }else{
            printf("Unknown Command: %s", argv[1]);
        }
    }

    return 0;
}