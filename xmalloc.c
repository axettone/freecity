#include <stdlib.h>
#include "xmalloc.h"

void* xmalloc(size_t size){
	void* ret = malloc(size);
	if(ret == NULL)
		abort();
	return ret;
}
