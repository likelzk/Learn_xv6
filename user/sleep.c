#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc != 2){
        write(1,"para fail\n",10);
        exit(1);
    }

    int time = atoi(&argv[1]);

    sleep(time);

    write(1,"Nothing happen\n",15);
    
    exit(0);
}
