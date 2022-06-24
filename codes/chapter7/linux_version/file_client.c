#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    char buf[BUF_SIZE];
    
    if(argc != 3){
        printf("Usage: %s <Ip><Port> \n", argv[0]);
        exit(1);
    }
    
    FILE* fp = fopen("receive.dat", "wb");
    int sd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_adr;
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2])); // char* to int, and convert to net

    connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    
    int read_cnt;
    while((read_cnt = read(sd, buf, BUF_SIZE)) != 0){
        fwrite((void*)buf, 1, read_cnt, fp);
    }
    
    puts("Receive file data");
    write(sd, "Thank you", 10);
    fclose(fp);
    close(sd);
    return 0;
}
