#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PTHREAD 100
long long num = 0;

void *thread_inc(void* args){
    for(int i = 0; i < 50000000; ++i){
        num++;
    }
    return NULL;
}
void *thread_des(void* args){
    for(int i = 0; i < 50000000; ++i){
        num--;
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t thread_id[NUM_PTHREAD];
    printf("sizeof long long: %d \n", sizeof(long long));
    for(int i = 0; i < NUM_PTHREAD; ++i){
        if(i%2){
            pthread_create(&(thread_id[i]),NULL, thread_inc, NULL);
        }
        else{
            pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
        }
    }
    for(int i = 0; i < NUM_PTHREAD; ++i){
        pthread_join(thread_id[i], NULL);
    }
    printf("result: %lld \n", num);
    return 0;
}
