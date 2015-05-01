#ifndef RESIDENTIALS_H
#define RESIDENTIALS_H
#include "structs.h"
#include "city.h"
struct building* init_residential(struct coords_s coords,
		struct res_model* model);

long count_population(struct city_buildings* buildings);
void eval_res_building(struct city* the_city,struct building *bld);
struct building* find_closest_job_and_assign(struct city*,struct building*);
void people_migration();
#endif
