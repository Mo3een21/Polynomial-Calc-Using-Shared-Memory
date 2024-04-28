#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_LENGTH 128

enum Operation{
    ADD,
    MUL,
    SUB
};


enum Operation checkOperation(char *input);

void sendToOperation(enum Operation operation, char *input, char *input1);

void addition(char *leftSidePoly, char *rightSidePoly);

void subtraction(char *leftPoly, char *rightPoly);

void multiplication(char *leftPoly, char *rightPoly);

int getNum(char *poly,int index);

int main() {
int endCheck=0;
char *saveptr;
    int counter=0;
char *polyInput = (char *) malloc((MAX_LENGTH) * sizeof(char));
    while(polyInput!="END") {
        fgets(polyInput, MAX_LENGTH, stdin);
        if (strcmp(polyInput, "END\n") == 0) {
            free(polyInput);
            exit(0);
        }

            polyInput[strcspn(polyInput, "\n")] = '\0';
            enum Operation op = checkOperation(polyInput);

            char *tokenizedInput = strtok(polyInput, "()");
            char *secondInput=strtok(NULL,"ADDMULSUB()");

//            printf("%s\n",tokenizedInput);
//            printf("%s\n",secondInput);
            /**** saving the first number in the input polynmial of each polynomial to be the degree

             * for each polynomial respectively

             */

        //(2:3,-2,-1)ADD(3:2,4,0,-1)
            sendToOperation(op,tokenizedInput,secondInput);



    }
    free(polyInput);
    return 0;
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

int getNum(char *poly,int index) {
    char degree=poly[index];
   // char* token= strtok(NULL,",");
    char degStr[2]={degree,'\0'};
    int deg=atoi(degStr);
    return deg;
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
