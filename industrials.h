#ifndef INDUSTRIALS_H
#define INDUSTRIALS_H
#include "structs.h"
#include "city.h"

struct building* init_industrial(struct coords_s coords,
		struct ind_model* model);
void eval_ind_building(struct city* the_city,struct building *bld);
#endif
