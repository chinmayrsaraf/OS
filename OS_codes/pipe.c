#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
int main(){
    int fd[2] ;
    // fd[0] = read;
    // fd[1] = write
    
    if (pipe(fd) == -1){
        printf("error occured!");
        return -1;
    }

    int id = fork();
    if (id == 0){//child process
        close(fd[0]);
        int x;
        printf("input a number : ");
        scanf("%d", &x);
        write(fd[1] , &x , sizeof(int));
        close(fd[1]);
    }
    else{//parent process
        close(fd[1]);
        int y;
        read(fd[0] , &y , sizeof(int));
        close(fd[0]);
        printf("got from child process %d",y);
        
    }


    return 0;
    
    

}