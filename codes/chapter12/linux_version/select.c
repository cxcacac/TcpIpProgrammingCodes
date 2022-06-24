#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 30

int main(int argc, char* argv[]){
    fd_set reads, tmps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    
    // FDZERO(fd_set *fdset);
    // FD_SET(int fd, fd_set* fdset);
    // FD_CLR(int fd, fd_set* fdset);
    // FD_ISSET(int fd, fd_set* fdset);

    FD_ZERO(&reads);
    // 0 is standard input(console)
    FD_SET(0, &reads);

    // timeout.tv_sec = 5;
    // timeout.tv_usec = 5000;

    while(1){
        tmps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &tmps, 0, 0, &timeout);
        if(result==-1){
            puts("select() error!");
        }
        else if(result==0){
            puts("Time-out!");
        }
        else{
            if(FD_ISSET(0, &tmps)){
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console: %s \n", buf);
            }
        }
    }
    return 0;
}
