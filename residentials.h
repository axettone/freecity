#ifndef RESIDENTIALS_H
#define RESIDENTIALS_H
#include "structs.h"
struct building* init_residential(unsigned short x,unsigned short y, unsigned short size, unsigned short capacity,
	       	unsigned short occupied, unsigned short wealth);

long count_population(struct city_buildings* buildings);

void people_migration();
#endif
