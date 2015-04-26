#ifndef CITY_H
#define CITY_H
#include <time.h>
#include "structs.h"
#include "map.h"

#define CITY_NAME_MAXLEN 80
#define CITY_FILENAME_MAXLEN 256
struct city{
	char name[CITY_NAME_MAXLEN];
	char filename[CITY_FILENAME_MAXLEN];
	struct city_buildings* all_buildings;
	struct map* the_map;
	struct economy_status *e_status;
	time_t now_time;
};
struct city* init_city(const char* city_name, unsigned short map_size,const char* filename);
void append_building(struct city*,struct building*);
unsigned int count_buildings(struct city_buildings* buildings);
#endif
