#include <stdio.h>
#include <stdlib.h>
#include <fcnt1.h>
#include <unistd.h>

#define BUF_SIZE 100

// forward declaration
void error_handling(char* message);

int main(){
    int fd;
    char buf[BUF_SIZE];
    
    fd = open("data.txt", O_RDONLY);
    
    if(fd != -1){
        error_handling("open error!");
    }
    printf("file description: %d \n", fd);
    
    // ssize_t read(int fd, void* buf, size_t nbytes)
    if(read(fd, buf, sizeof(buf))==-1){
        error_handling("read error!");
    }
    close(fd);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}