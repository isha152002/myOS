#define Library
#include "osapi.h"


private fd fds[256]; //file descriptors can be 2^8 as fd is int8 type 




private bool isopen(fd file){ //check if valid AND open
    signed int posixfd;
    struct stat _;//just need a dummy container

    if(file<3) //check#1: fd is not a reserved one
        return false;

    posixfd = getposixfd(file);

    if(posixfd==0) //check#2: mapped to a real fd
        return false;
    
    if ((fstat(posixfd, &_))==-1) return false;//check3: real OS confirms it’s open

    return true;//all checks passed
    
}

public bool load(fd file, int8 c){//write
    int8 buf[2];
    signed int n;
    signed int posixfd;

    assert_initialized();

    if(file>1)  
        if(!isopen(file))
            reterr(ErrBadFD); //function must STOP immediately when an error happens hence using a fun to also return in place of writing 2 lines repeatedly
    
    posixfd = getposixfd(file);
    if(posixfd==0){
        reterr(ErrBadFD);
    }

    posixfd = (posixfd == 1)? 0//remapping
        : (posixfd ==2)? 1
        : (posixfd);
    

    *buf = *(buf+1) = (int8)0; //clear buffer
    *buf= c;
    n= write(posixfd, $c buf, 1);
    if (n!=1){
        reterr(ErrIO);
    }
      
    return true;
}

public int8 store(fd file){ //read
    int8 buf[2];
    signed int n;
    signed int posixfd;

    assert_initialized();

    if(file>2){// for user-managed files check if valid n open
        if(!isopen(file)){
            reterr(ErrBadFD); 
        }
    }

    posixfd = getposixfd(file);
    if(posixfd==0){//open but not mapped 0/1/2
        reterr(ErrBadFD);
    }
    
    posixfd = (posixfd == 1)? 0//remap to correct posix
        : (posixfd ==2)? 1
        : (posixfd);
    

    *buf = *(buf+1) = (int8)0; //clear buffer
    
    n= read(posixfd, $c buf, 1);

    if (n!=1){ //if read fails
        reterr(ErrIO);
    }
      
    return (int8)*buf; //return 1byte
}

private void setupfds(){
    zero($1 fds, sizeof(fds));

    fds[0]=1;
    fds[1]=2;

    return;

}

private void zero(int8* str, int16 size){//custom memset
    int8 *p;
    int16 n;

    for(n=size, p=str; n>0; n--,p++){
        *p=(int8)0; //avoid compiler ambiguity by typecasting
    }
    return;
}

public void init(){
    errnumber= (int8)0;
    setupfds();
    inintialized=true;
    return;
}