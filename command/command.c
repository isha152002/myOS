/*command.c*/
#include"command.h"

int main(int argc, char*argv[]){
    int8 c;
    init();

    c=store((int8)0);
    printf("ASCII VALUE =%d\n", $i c);
    printf("HEX VALUE =0x%.02hhx\n", $i c);
    printf("errornumber=0x%.02hhx\n", $i errnumber);


    return 0;
}
