#include "utils.h"

float zero_to_one(float n)
{
	if(n<0.0)
		return 0.0;
	if(n>1.0)
		return 1.0;
	return n;
}
