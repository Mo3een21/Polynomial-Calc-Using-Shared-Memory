#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_LENGTH 128
#define SHARED_MEMO_SIZE (128*10)
#define BUFFER_SIZE 10


int main() {
    key_t externalKey;
    char *bufferPtr;
    int shmemo_id;
    sem_t *mutex, *full, *empty;
    pthread_mutex_t lockMutex;


    mutex = sem_open("/ex3_mutex", O_CREAT, 0644, 1);
    if (mutex == SEM_FAILED) {
        perror("sem open failed");
        return EXIT_FAILURE;
    }

    full = sem_open("/ex3_full", O_CREAT, 0644, 0); // Updated semaphore names
    if (full == SEM_FAILED) {
        perror("sem open failed");
        return EXIT_FAILURE;
    }

    empty = sem_open("/ex3_empty", O_CREAT, 0644, BUFFER_SIZE); // Updated semaphore names
    if (empty == SEM_FAILED) {
        perror("sem open failed");
        return EXIT_FAILURE;
    }

    pthread_mutex_init(&lockMutex, NULL);

    externalKey = ftok("/tmp", 'y');

    shmemo_id = shmget(externalKey, SHARED_MEMO_SIZE * sizeof(char), IPC_CREAT | 0600);
    if (shmemo_id == -1) {

            perror("FAILED SHARED MEMORY!!!");
            exit(1);

    }


    bufferPtr=(char*)shmat(shmemo_id,NULL,0);
    if((bufferPtr)<0){
    perror("FAILED TO ATTACH MEMORY!!!");
    exit(1);

}



    int i=0;
    while(i<10){
        sem_wait(empty);
        sem_wait(mutex);

    fgets( bufferPtr, MAX_LENGTH, stdin);


        if(strcmp( bufferPtr, "END\n") == 0){

           break;
        }
        bufferPtr[strcspn(bufferPtr,"\n")]='\0';

        sem_post(mutex);
        sem_post(full);
        i++;
    }
    pthread_mutex_destroy(&lockMutex);
    sem_close(full);
    sem_close(empty);
    sem_unlink("/ex3_full");
    sem_unlink("/ex3_empty");
    sem_close(mutex);
    sem_unlink("/ex3_mutex");
    shmdt(bufferPtr);
    return 0;
}
