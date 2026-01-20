#include<stdio.h>
#include<string.h>
#include<direct.h>
#include<dirent.h>
#include<sys/stat.h>

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
                printf("Failed to create Commit directory!\n");
                return 1;
            }
            else{
                DIR *dir = opendir(".");
                if(dir == 0){
                    printf("Failed to open directory!\n");
                    return 1;
                }
            
                struct dirent *entry;
                // printf("First entry: %s\n", entry->d_name);
                while((entry = readdir(dir))!=NULL){
                    if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0 || strcmp(".vcs", entry->d_name)==0) continue;
                    if(strstr(entry->d_name, ".exe")!=0) continue;
                    struct stat st;
                    stat(entry->d_name,&st);
                    if(stat(entry->d_name,&st)==-1) continue;
                    if(!S_ISREG(st.st_mode)){
                    continue;
                    }
            
                    char src[200],dest[200];
                    sprintf(src,"%s",entry->d_name);
                    sprintf(dest,"%s/%s",path,entry->d_name);
            
                    FILE *fs = fopen(src,"rb");
                    FILE *fd = fopen(dest, "wb");
            
                    if(fs == NULL || fd==NULL){
                        if(fs) fclose(fs);
                        if(fd) fclose(fd);
                        continue;
                    }
            
                    char buffer[1024];
                    size_t byte;
            
                    while((byte = fread(buffer,1,sizeof(buffer),fs))>0){
                        fwrite(buffer,1,byte,fd);
                    }
                    fclose(fs);
                    fclose(fd);
                }
                closedir(dir);
                FILE *fp = fopen(".vcs/log.txt", "w");
                fprintf(fp,"%d",newCommit);
                fclose(fp);

                printf("Commited as %d\n",newCommit);
            }
            
        }else{
            printf("Unknown Command: %s", argv[1]);
        }
    }


    return 0;
}