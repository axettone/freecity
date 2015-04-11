#ifndef RESIDENTIALS_H
#define RESIDENTIALS_H
#include "structs.h"
struct building* init_residential(uint8_t x,uint8_t y, unsigned short capacity,
	       	unsigned short occupied, unsigned short wealth);

long count_population(struct city_buildings* buildings);
#endif
