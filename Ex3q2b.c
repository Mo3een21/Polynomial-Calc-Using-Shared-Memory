#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_LENGTH (128*10)
#define BUFFER_SIZE 10

//typedef struct {
//    char strings[10][MAX_LENGTH];
//} SharedData;



enum Operation{
    ADD,
    MUL,
    SUB
};

int getNum(char *poly,int index) {
    char degree=poly[index];
    char degStr[2]={degree,'\0'};
    int deg=atoi(degStr);
    return deg;
}



void multiplication(char *leftSidePoly, char *rightSidePoly) {



    int degOne=getNum(leftSidePoly,0);
    int degTwo=getNum(rightSidePoly,0);
    int lenOne=0,lenTwo=0;
    int maxDeg=degOne+degTwo;
    for(int i=2;i< strlen(leftSidePoly);i++){
        if(leftSidePoly[i]!=','){
            lenOne++;}
    }
    for(int i=2;i< strlen(rightSidePoly);i++){
        if(rightSidePoly[i]!=','){
            lenTwo++;
        }
    }
    int result[lenOne+lenTwo+1];
    for(int i=0;i<=lenOne+lenTwo;i++){
        result[i]=0;
    }

    int temp1=0,temp2=0;
    for(int i=2;i< strlen(leftSidePoly);i++){
        int numOne=0;
        if(leftSidePoly[i]!=',') {

            if(leftSidePoly[i]=='-'){
                i++;
                numOne=-1* getNum(leftSidePoly,i);

            }
            else{
                numOne= getNum(leftSidePoly,i);
            }
            temp2=0;
            for (int j = 2; j < strlen(rightSidePoly); j++) {
                if (rightSidePoly[j] != ',') {
                    int numTwo=0;
                    if(rightSidePoly[j]=='-'){
                        j++;
                        numTwo=-1* getNum(rightSidePoly,j);

                    }
                    else{
                        numTwo= getNum(rightSidePoly,j);
                    }
                    result[temp1+ temp2] += (numOne * numTwo);
                    temp2++;
                }
            }
            temp1++;
        }
    }

    for(int i=0;i< lenOne+lenTwo;i++){

        if(result[i]!=0 &&maxDeg>0){
            if(result[i]<0){
                printf("- %dx^%d ",-1*result[i],maxDeg);
            }
            else{
                if(i>0){
                    printf(" + ");
                }
                printf("%dx^%d ",result[i],maxDeg);
            }
        }
        if(maxDeg==0){
            if(result[i]<0){
                printf("- %d",-1*result[i]);
            }
            else {
                printf("%d", result[i]);
            }
        }
        maxDeg--;

    }




    printf("\n");
}

void subtraction(char *leftSidePoly, char *rightSidePoly) {

    int degOne=getNum(leftSidePoly,0);
    int degTwo=getNum(rightSidePoly,0);
    if(degOne>degTwo) {
        int num1,num2;
        for (int i = 2, j=2; i < strlen(leftSidePoly)&& j< strlen(rightSidePoly); i++) {
            if (degOne == degTwo) {
                if (leftSidePoly[i] != ',' && rightSidePoly[j] != ',') {
                    num1 = getNum(leftSidePoly, i);
                    num2 = getNum(rightSidePoly, j);
                    if (leftSidePoly[i] == '-') {
                        i++;
                        num1 = -1 * (getNum(leftSidePoly, i));
                    }
                    if (rightSidePoly[j] == '-') {
                        j++;
                        num2 = -1 * getNum(rightSidePoly, j);
                    }

                    int result = num1 - num2;
                    if (i > 0 && result > 0) {
                        if (degOne == 0) {
                            printf("+ %d", result);
                        } else {
                            printf("+ %dx^%d ", result, degOne);
                        }

                        degTwo -= 1;
                        degOne -= 1;
                    }
                    if (i > 0 && result < 0) {
                        if (degOne == 0) {
                            printf("- %d", result * -1);
                        } else {
                            printf("- %dx^%d ", result * -1, degOne);
                        }
                        degTwo -= 1;
                        degOne -= 1;
                    }
                    if (result == 0) {
                        degTwo -= 1;
                        degOne -= 1;
                    }

                }

                j++;
            } else {
                int num = getNum(leftSidePoly, i);
                if (leftSidePoly[i] == '-') {
                    i++;
                    num = -1 * getNum(leftSidePoly, i);
                    printf("%dx^%d ", num, degOne);
                } else {


                    if (i > 3) {
                        printf("+ ");
                    }
                    printf("- %dx^%d ", num, degOne);

                    i++;
                    degOne--;
                }


            }

        }

    }




    else{
        int num1,num2;
        for (int i = 2, j=2; i < strlen(rightSidePoly)&& j< strlen(leftSidePoly); i++) {
            if (degOne == degTwo ) {
                if (leftSidePoly[j] != ',' && rightSidePoly[i] != ',') {
                    num1= getNum(leftSidePoly,j);
                    num2= getNum(rightSidePoly,i);
                    if(leftSidePoly[j]=='-'){
                        j++;
                        num1=-1*(getNum(leftSidePoly,j));
                    }
                    if(rightSidePoly[i]=='-'){
                        i++;
                        num2= -1*getNum(rightSidePoly,i);
                    }

                    int result = num1 -num2;
                    if (i > 0 && result > 0) {
                        if(degOne==0){
                            printf("+ %d",result);
                        }
                        else{
                            printf("+ %dx^%d ",result,degOne);
                        }

                        degTwo-=1;
                        degOne-=1;
                    }
                    if (i > 0 && result < 0) {
                        if(degOne==0){
                            printf("- %d",result*-1);
                        }
                        else {
                            printf("- %dx^%d ", result * -1, degOne);
                        }
                        degTwo-=1;
                        degOne-=1;
                    }
                    if(result==0){
                        degTwo-=1;
                        degOne-=1;
                    }

                }

                j++;
            }
            else {
                int num = getNum(rightSidePoly, i);
                if (rightSidePoly[i] == '-') {
                    i++;
                    num = -1 * getNum(rightSidePoly, i);
                    printf("%dx^%d ", num, degTwo);
                } else {
                    if (i > 3) {
                        printf("+ ");
                    }
                    printf("- %dx^%d ", num, degTwo);

                    i++;
                    degTwo--;
                }
            }

        }


    }

    printf("\n");
}



void addition(char *leftSidePoly, char *rightSidePoly) {
    int degOne=getNum(leftSidePoly,0);
    int degTwo=getNum(rightSidePoly,0);
    if(degOne>degTwo) {
        int num1,num2;
        for (int i = 2, j=2; i < strlen(leftSidePoly)&& j< strlen(rightSidePoly); i++) {
            if (degOne == degTwo ) {
                if (leftSidePoly[i] != ',' && rightSidePoly[j] != ',') {
                    num1= getNum(leftSidePoly,i);
                    num2= getNum(rightSidePoly,j);
                    if(leftSidePoly[i]=='-'){
                        i++;
                        num1=-1*(getNum(leftSidePoly,i));
                    }
                    if(rightSidePoly[j]=='-'){
                        j++;
                        num2= -1*getNum(rightSidePoly,j);
                    }

                    int result = num1 +num2;
                    if (i > 0 && result > 0) {
                        if(degOne==0){
                            printf("+ %d",result);
                        }
                        else{
                            printf("+ %dx^%d ",result,degOne);
                        }

                        degTwo-=1;
                        degOne-=1;
                    }
                    if (i > 0 && result < 0) {
                        if(degOne==0){
                            printf("- %d",result*-1);
                        }
                        else {
                            printf("- %dx^%d ", result * -1, degOne);
                        }
                        degTwo-=1;
                        degOne-=1;
                    }
                    if(result==0){
                        degTwo-=1;
                        degOne-=1;
                    }

                }

                j++;
            }
            else {
                int num = getNum(leftSidePoly, i);
                if(leftSidePoly[i]=='-'){
                    i++;
                    num=-1* getNum(leftSidePoly,i);
                }
                if (i >3) {
                    printf("+ ");
                }
                printf("%dx^%d ", num,degOne);

                i++;
                degOne--;
            }


        }



    }




    else{
        int num1,num2;
        for (int i = 2, j=2; i < strlen(rightSidePoly)&& j< strlen(leftSidePoly); i++) {
            if (degOne == degTwo ) {
                if (leftSidePoly[j] != ',' && rightSidePoly[i] != ',') {
                    num1= getNum(leftSidePoly,j);
                    num2= getNum(rightSidePoly,i);
                    if(leftSidePoly[j]=='-'){
                        j++;
                        num1=-1*(getNum(leftSidePoly,j));
                    }
                    if(rightSidePoly[i]=='-'){
                        i++;
                        num2= -1*getNum(rightSidePoly,i);
                    }

                    int result = num1 +num2;
                    if (i > 0 && result > 0) {
                        if(degOne==0){
                            printf("+ %d",result);
                        }
                        else{
                            printf("+ %dx^%d ",result,degOne);
                        }

                        degTwo-=1;
                        degOne-=1;
                    }
                    if (i > 0 && result < 0) {
                        if(degOne==0){
                            printf("- %d",result*-1);
                        }
                        else {
                            printf("- %dx^%d ", result * -1, degOne);
                        }
                        degTwo-=1;
                        degOne-=1;
                    }
                    if(result==0){
                        degTwo-=1;
                        degOne-=1;
                    }

                }

                j++;
            }
            else {
                int num = getNum(rightSidePoly, i);
                if(rightSidePoly[i]=='-'){
                    i++;
                    num=-1* getNum(rightSidePoly,i);
                }
                if (i >3) {
                    printf("+ ");
                }
                printf("%dx^%d ", num,degTwo);

                i++;
                degTwo--;
            }


        }


    }

    printf("\n");
}


void sendToOperation(enum Operation operation, char *firstPoly, char *secondPoly) {
    switch(operation){
        case ADD:

            addition(firstPoly,secondPoly);
            break;
        case SUB:

            subtraction(firstPoly,secondPoly);
            break;
        case MUL:

            multiplication(firstPoly,secondPoly);
            break;
        default:
            printf("INVALID OPERATION!!!\nTRY AGAIN:\n");
    }
}



enum Operation checkOperation(char *string) {
    char strOne[]={ "ADD"};
    char strTwo[]={"SUB"};
    char strThree[]={"MUL"};
    if(strstr(string,strOne)!=NULL){
        return ADD;
    }
    else if(strstr(string,strTwo)!=NULL){
        return SUB;
    }
    else if(strstr(string,strThree)!=NULL){
        return MUL;
    }

}

int main() {

    key_t externalKey,secondKey;
    char *bufferPtr;
    char *endFlag;
    int shmemo_id,shmemo_id_2;
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
       // secondKey=ftok("/tmp2",'y');
        if ((shmemo_id = shmget(externalKey, MAX_LENGTH* sizeof(char), 0600)) == -1) {
            perror("FAILED TO GET MEMORY!!!");
            exit(1);
        }

//    if ((shmemo_id_2 = shmget(secondKey, 10*sizeof(char) , 0600)) == -1) {
//        perror("FAILED TO GET MEMORY!!!");
//        exit(1);
//    }

        bufferPtr = (char*) shmat(shmemo_id, NULL, 0);
        if (bufferPtr < 0) {
            perror("FAILED TO ATTACH MEMO!!!");
            exit(1);
        }

//    endFlag = (char*) shmat(shmemo_id_2, NULL, 0);
//    if (endFlag < 0) {
//        perror("FAILED TO ATTACH MEMO!!!");
//        exit(1);
//    }

        int i = 0;


    while(i<10){
        sem_wait(full);
       sem_wait(mutex);

        //(2:3,2,1)ADD(3:2,4,0,-1)
       // printf("%s\n",bufferPtr);
        enum Operation op = checkOperation(bufferPtr);

        char *tokenizedInput = strtok(bufferPtr, "()");
        char *secondInput=strtok(NULL,"ADDMULSUB()");
        /**** saving the first number in the input polynmial of each polynomial to be the degree

         * for each polynomial respectively

         */
        sendToOperation(op,tokenizedInput,secondInput);

        i++;

        sem_post(mutex);
        sem_post(empty);

    }

    pthread_mutex_destroy(&lockMutex);
    sem_close(full);
    sem_close(empty);
    sem_unlink("/ex3_full");
    sem_unlink("/ex3_empty");
    sem_close(mutex);
    sem_unlink("/ex3_mutex");
    shmdt(bufferPtr);
    shmctl(shmemo_id, IPC_RMID, NULL);

    return 0;
}
