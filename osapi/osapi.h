#define _GNU_SOURCE
#include <stdio.h>
#include "os.h"
#include <sys/stat.h>
#include<fcntl.h>
#include <unistd.h>

#define getposixfd(x) fds[(x)]
#define assert_initialized() if (!inintialized)reterr(ErrInit) //cannot use OS services before the OS is ready


private bool isopen(fd);
private void setupfds(void);
private void zero(int8*, int16);