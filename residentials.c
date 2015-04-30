/*
 * residentials.c - Residentials stuff
 *
 * Copyright (c) 2015 Paolo Niccolò Giubelli
 *
 */
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "residentials.h"
#include "utils.h"
#include "economy.h"

struct building* init_residential(struct coords_s coords,struct res_model* model){
  struct building* ret = (struct building*)xmalloc(sizeof(struct building));
  ret->origin = coords;
  ret->type = BLD_RESIDENTIAL;
  ret->item = (struct residential*)xmalloc(sizeof(struct residential));
  struct residential* r = (struct residential*)ret->item;
  r->model = model;
  r->occupied = 0;
  return ret;
}

long count_population(struct city_buildings* buildings){
  long ret = 0;
  while(1){
	  if(buildings->building->type == BLD_RESIDENTIAL){
		  ret+= ((struct residential*)buildings->building->item)
			  ->occupied;
	  }
    buildings = buildings->next;
    if(buildings == NULL){
      break;
    }
  }
  return ret;
}
void people_migration(){
	printf("Computing people migrations\n");
}

void eval_res_building(struct city* the_city,struct building *bld)
{
	struct economy_status* e = the_city->e_status;
	unsigned int MAX_TAX_RATE = 60;
	//unsigned int TAX_RATE = 30;
	unsigned int TOTAL_JOBS = e->available_jobs - e->active_jobs;
	float CHOOSINESS = 0.30;
	unsigned int DISTANCE = 50;
	unsigned int MAX_DISTANCE = 100;
	unsigned short LAND_VALUE = 50;
	unsigned short MAX_LAND_VALUE = 100;
	float tax_rate = get_tax_rate_for_bld(e,bld);
	//printf("Evaluating building\n");
	struct residential* r = (struct residential*)bld->item;
	float attract = 0.30*((MAX_TAX_RATE-tax_rate)/MAX_TAX_RATE)
		+ 0.50*CHOOSINESS*(e->available_jobs/TOTAL_JOBS)
		+ 0.10*DISTANCE/MAX_DISTANCE
		+ 0.10*(50-abs(50-LAND_VALUE))/MAX_LAND_VALUE;
	attract=zero_to_one(attract*(RAND_MAX/2-rand())/RAND_MAX);
#if 0
	printf("Model capacity: %d, occupied: %d\n", r->model->capacity,
						r->occupied);
#endif
	short diff = attract*(r->model->capacity - r->occupied);
	r->occupied += diff;
	e->active_jobs += diff;
	e->available_jobs -= diff;
#if 0
	printf("VAL: %g\n", attract);
	printf("Occupied: %d\n", r->occupied);
#endif
}

