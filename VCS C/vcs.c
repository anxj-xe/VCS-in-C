#include<stdio.h>
#include<string.h>
#include<direct.h>

int repo_initialized(){
    FILE *fp = fopen(".vcs/log.txt", "r");

    if(fp==NULL){
        return 0;
    }

    fclose(fp);
    return 1;
}

int main(int argc,char* argv[]){

    if(argc<2){
        printf("No commands found!\n");
        return 1;
    }

    if(strcmp(argv[1],"init")==0){
        if(mkdir(".vcs")==-1){
            printf("Directory exists or invalid path\n");
            return 1;
        }

        mkdir(".vcs/commit");

        FILE *fp = fopen(".vcs/log.txt", "w");
        if(fp==NULL){
            printf("Invalid file!!\n");
            return 1;
        }

        fprintf(fp, "0");
        fclose(fp);

        printf("Initialized a VCS Repository in .vcs\n");
    }
    else{
        if(!repo_initialized()){
            printf("Not a ./vcs repository!\n");
            return 1;
        }
        if(strcmp(argv[1],"commit")==0){

            FILE *fp = fopen(".vcs/log.txt", "r");
            if(fp == NULL){
                printf("Error in log.txt\n");
                return 1;
            }

            int lastCommit = 0;
            fscanf(fp, "%d", &lastCommit);
            fclose(fp);

            int newCommit = lastCommit + 1;

            char path[100];
            sprintf(path, ".vcs/commit/%d", newCommit);

            if(mkdir(path)==-1){
                printf("Failed to creat Commit directory!\n");
                return 1;
            }else{
                FILE *fp = fopen(".vcs/log.txt", "w");
                fprintf(fp,"%d",newCommit);
                fclose(fp);
            }
            printf("Commited as %d\n",newCommit);

        }else{
            printf("Unknown Command: %s", argv[1]);
        }
    }

    return 0;
}