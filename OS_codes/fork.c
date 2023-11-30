#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc , char* argv[]){
    int id = fork();
    printf("hello bhai!\n form id: %d",id);
    return 0;
}