#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void new_proc(int fd[2])
{
    int prime;
    int num;

    close(fd[1]);

    if(read(fd[0],&prime,4)!=4){
        fprintf(2, "Error in read.\n");
        exit(1);
    }

    fprintf(0, "prime %d\n",prime);

    if(read(fd[0],&num,4)==4){
        int newfd[2];   
        pipe(newfd);
        if(num % prime != 0)
            write(newfd[1],&num,4);
        if(fork()!=0){
            close(newfd[0]);
            while(read(fd[0],&num,4)==4){
                if(num % prime != 0)
                    write(newfd[1],&num,4);
            }
            close(fd[0]);
            close(newfd[1]);
            wait(0);
            exit(0);
            }else{
                new_proc(newfd);
            }   
    }else{
        exit(0);
    }
}


//第一个进程不断向管道写入2-35的数字
//其他进程分别对管道数字进行分析
int main(int argc, char* argv[])
{
    // parent to child
    int fd[2];

    if (pipe(fd) == -1) {
        fprintf(2, "Error: pipe(fd) error.\n");
    }
    // child process
    if (fork() == 0){
        new_proc(fd);
    }
    // parent process
    else {   
        close(fd[0]);
        fprintf(0, "prime 2\n");
        for(int i=3;i<=35;i++)
        {
            if( i%2 != 0)
             write(fd[1],&i,4);
        }
        close(fd[1]);
        wait(0);
    }
    exit(0);
}


