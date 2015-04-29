#ifndef COMMERCIALS_H
#include "structs.h"
#include "city.h"

struct building* init_commercial(struct coords_s origin,
		struct com_model* model);

void eval_com_building(struct city* the_city,struct building *bld);
#define COMMERCIALS_H
#endif
