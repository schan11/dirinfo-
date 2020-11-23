#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    
    // scan current directory
    DIR *directory = opendir(".");
    // struct dirent: directory struct that contains information stored in a directory file
    struct dirent *entry = readdir(directory); // readdir: returns a pointer to the next entry in a directory stream
    struct stat file;
    int size = 0;
    
    // show total size of all regular files in directory
    printf("Statistics for directory: %s\n", entry -> d_name); // d_name: Name of a file
    while (entry){
       if (entry -> d_type == DT_REG){ // d_type: File type as an int
         stat(entry -> d_name, &file);
         size += file.st_size;
       }
       entry = readdir(directory);
     }
    
    printf("Total Directory Size: %d Bytes\n", size);
    
    rewinddir(directory); // rewinddir: resets the directory stream of d to the beginning
    entry = readdir(directory);
    
    // specify which files are directories
    printf("Directories:\n");
    while (entry != NULL){
        if (entry -> d_type == DT_DIR){
            printf("\t%s\n", entry -> d_name);
        }
        entry = readdir(directory);
    }
    
    rewinddir(directory);
    entry = readdir(directory);
    
    // list all files in directory
    printf("Regular files:\n");
    while (entry != NULL){
        if (entry -> d_type == DT_REG){
            printf("\t%s\n", entry -> d_name);
        }
        entry = readdir(directory);
        
    }
    
    closedir(directory);
    return 0;
}


