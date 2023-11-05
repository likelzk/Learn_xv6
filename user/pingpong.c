#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"


int main(int argc,char* argv[])
{
    int p[2];
    int Ownpid;

    char buff;

    pipe(p);

    if(fork() != 0){
        //父进程
        Ownpid = getpid();
        write(p[1],"a",1);
        read(p[0],&buff,1);
        printf("<%d>:received pong",Ownpid);
    }else{
        //子进程
        Ownpid = getpid();
        read(p[0],&buff,1);
        printf("<%d>:received ping",Ownpid);
        write(p[1],"a",1);
    }

    exit(0);
}