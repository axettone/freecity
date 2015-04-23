#ifndef RESIDENTIALS_H
#define RESIDENTIALS_H
#include "structs.h"
struct building* init_residential(struct coords_s coords,
		struct res_model* model);

long count_population(struct city_buildings* buildings);

void people_migration();
#endif
