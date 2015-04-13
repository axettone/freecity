#ifndef CITY_H
#define CITY_H
#include <time.h>
#include "structs.h"
#include "map.h"

struct city{
	char name[80];
	char filename[256];
	struct city_buildings* all_buildings;
	struct map* the_map;
	struct economy_status *e_status;
	time_t now_time;
};

unsigned int count_buildings(struct city_buildings* buildings);
#endif
