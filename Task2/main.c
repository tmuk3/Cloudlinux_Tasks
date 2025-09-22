#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <linux/limits.h>

//char *PATH = "/mnt/c/Users/tmuke/Desktop/GitHub/Cloudlinux_Tasks/Task1";

void cls(char * cur_path, int depth){
    DIR *dir = opendir(cur_path);

    if (dir ==NULL){
        return;
    }
    struct dirent *entry;

    while((entry = readdir(dir)) != NULL){

        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..")==0){
            continue;
        }
            

        
        printf("%*s%s\n",depth*4,"",entry->d_name);
        char next[PATH_MAX]; 
        snprintf(next,sizeof(next),"%s/%s",cur_path,entry->d_name);
        cls(next,depth+1);
    }
    closedir(dir);

}

int main(int argc, char *argv[]){
    
    char *start = (argc > 1) ? argv[1] : ".";
    printf("%s\n",start);
    cls(start,1);



    return 0;
}