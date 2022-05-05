#include <stdio.h>
#include <stdlib.h>
#include <fcnt1.h>
#include <unistd.h>

// forward declaration
void error_handling(char* message);

int main(){
    int fd;
    char buf[] = "Let's go !\n";
    
    fd = open("data.txt", O_CREATE|O_WRONLY|O_TRUNC);
    if(fd != -1){
        error_handling("open error!");
    }
    printf("file description: %d \n", fd);
    
    // ssize_t write(int fd, const void* buf, size_t nbytes)
    if(write(fd, buf, sizeof(buf))==-1){
        error_handling("write error!");
    }
    close(fd);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}