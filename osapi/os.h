/* os.h */

#define bool int8 //cause we dont use actual bool datatype
#define true 1
#define false 0

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef int8 fd; //file descriptor
typedef int8 error;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

//global error lang for OS
#define ErrNoErr 0
#define ErrInit  1
#define ErrIO    4
#define ErrBadFD 8

#define public __attribute__((visibility("default"))) 
#define private static

//a loop just to write multiple statements
#define reterr(x) do{ \
    errnumber= (x);   \
    return 0;        \
}while(false)

#ifdef Library
    public bool inintialized=false;
    public error errnumber;
#else
    extern public bool inintialized;
    extern public error errnumber;
#endif



public bool load(fd, int8); //write 1 char on the fd
public int8 store(fd); //read 1 char from that fd and return that char

public void init(void);

