#include <stdlib.h>
#include <cstdio>
#include <cstring>

extern "C"{

int testfunc(const char* iStr)  {
	printf("input string: %s\n", iStr);
	int len = strlen(iStr);
	printf("string len: %d\n", len);
	return(len);
}

}
