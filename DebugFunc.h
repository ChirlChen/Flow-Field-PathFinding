#ifndef _DEBUGFUNC_H_
#define _DEBUGFUNC_H_

#define MYDEBUG 1
#if MYDEBUG
	#include <stdio.h>
	#define PRINT(str, ...) fprintf(stdout, (str), ##__VA_ARGS__)
#else
	#define PRINT(str, ...) ((void)0)

#endif


#endif
