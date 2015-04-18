//
// Created by lenovo on 2015/4/18.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "simple.h"

sem_t bin_sem;

int main(void){
    int res;
    pthread_t a_thread;
    void *thread_result;

    bin_sem = sem_init(&bin_sem, 0, 0);
    if(res != 0){
        perror("semaphore init failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if(res != 0){
        perror("thread create failed");
        exit(EXIT_FAILURE);
    }

    while (strncmp("end", work_area, 3) != 0){
        fgets(work_area, WORK_SIZE, stdin);
        sem_post(&bin_sem);
    }
    printf("thread joining\n");
    res = pthread_join(a_thread, &thread_result);
    printf("thread join done\n");
    sem_destory(&bin_sem);
    exit(EXIT_SUCCESS);

    return 0;
}

void *thread_function(void *arg){
    printf("waiting\n");
    pthread_exit(NULL);
}

