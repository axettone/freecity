#include <stdlib.h>
#include "utils.h"

float zero_to_one(float n)
{
	if(n<0.0)
		return 0.0;
	if(n>1.0)
		return 1.0;
	return n;
}

unsigned int pos_rand(unsigned int min, unsigned int max)
{
	return ((float)rand()/RAND_MAX) *(max-min) + min;
}
