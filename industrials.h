#ifndef INDUSTRIALS_H
#define INDUSTRIALS_H
#include "structs.h"

struct building* init_industrial(unsigned short x,unsigned short y,
		unsigned short size, unsigned short capacity,
		unsigned short employees, unsigned short tech_grade,
		unsigned short pollution, unsigned short power_req);


#endif
