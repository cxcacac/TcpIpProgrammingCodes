#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char* argv[]){
    char message[30];
    if(argc!=3){
        printf("Usage: %s <IP> <port> \n", argv[0]);
    }
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        error_handling("socket() error");
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        error_handling("connect() error");
    } 
    int idx = 0;
    int str_len=0;
    int read_len;
    while((read_len = read(sock, &message[idx++], 1))){
        if(read_len == -1){
            error_handling("read() error");
        }
        str_len += read_len;
    }

    printf("Message from server: %s \n", message);
    close(sock);
    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
