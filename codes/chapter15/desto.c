#include <stdio.h>
#include <fcntl.h>

int main(void){
    FILE *fp;
    int fd = open("data.dat", O_WRONLY | O_CREAT| O_TRUNC);
    if(fd==-1){
        fputs("file open error", stdout);
        return -1;
    }
    // FILE * fdopen(int filedes, const char* mode)
    fp = fdopen(fd, "w");
    fputs("Network C programming \n", fp);
    fclose(fp);
    return 0;
}