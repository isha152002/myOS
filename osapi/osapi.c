#define Library
#include "osapi.h"


private fd fds[256]; //file descriptors can be 2^8 as fd is int8 type 




private bool isopen(fd file){ //check if valid AND open
    signed int posixfd;
    struct stat _;//just need a dummy container

    if(file<3) //not managed by our OS , 0,1,2 are open in the host OS, but they are NOT considered “open” by our OS API so our fds start with 3
        return false;

    posixfd = getposixfd(file);

    if(posixfd==0) 
        return false;
    
    if ((fstat(posixfd, &_))==-1) return false;//fill this structure with info about this fd

    return true;
    
}

public bool load(fd file, int8 c){
    int8 buf[2];
    signed int n;
    signed int posixfd;

    assert_initialized();

    if(file>1)  // as if fd==2 then error
        if(!isopen(file))
            reterr(ErrBadFD); //function must STOP immediately when an error happens hence using a fun to also return in place of writing 2 lines repeatedly
    
    posixfd = getposixfd(file);
    if(posixfd==0){
        reterr(ErrBadFD);
    }

    posixfd = (posixfd == 1)? 0
        : (posixfd ==2)? 1
        : (posixfd);
    

    *buf = *(buf+1) = (int8)0;
    *buf= c;
    n= write(posixfd, $c buf, 1);
    if (n!=1){
        reterr(ErrIO);
    }
      
    return true;
}

public int8 store(fd file){
    int8 buf[2];
    signed int n;
    signed int posixfd;

    assert_initialized();

    if(file>2)  
        if(!isopen(file))
            reterr(ErrBadFD); 
    
    posixfd = getposixfd(file);
    if(posixfd==0){
        reterr(ErrBadFD);
    }

    posixfd = (posixfd == 1)? 0
        : (posixfd ==2)? 1
        : (posixfd);
    

    *buf = *(buf+1) = (int8)0;
    
    n= read(posixfd, $c buf, 1);
    if (n!=1){
        reterr(ErrIO);
    }
      
    return (int8)*buf;
}

private void setupfds(){
    zero($1 fds, sizeof(fds));

    fds[0]=1;
    fds[1]=2;

    return;

}

private void zero(int8* str, int16 size){
    int8 *p;
    int16 n;

    for(n=size, p=str; n>0; n--,p++){
        *p=(int8)0;
    }
    return;
}

public void init(){
    errnumber= (int8)0;
    setupfds();
    inintialized=true;
    return;
}