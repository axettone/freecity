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
/**
 * Find the closest buisiness building matching worker prerequisites, and
 * adjust employees counter for that building
 **/
struct building* find_closest_job_and_assign(struct city* the_city,
		struct building* res_building)
{
	struct building* found;
	struct residential* r = (struct residential*)res_building->item;
	struct commercial* c;
	struct industrial* i;
	if(res_building->type != BLD_RESIDENTIAL)
		abort();

	struct city_buildings* all_buildings = the_city->all_buildings;

	while(all_buildings != NULL)
	{
		//If it's a com/ind building
		if(all_buildings->building->type % 7 == 0){
			found = all_buildings->building;
			switch(found->type){
				case BLD_COMMERCIAL:
					c = (struct commercial*)found->item;
					if(c->employees < c->model->capacity){
						r->occupied++;
						c->employees++;
						return found;
					} else {
						found = NULL;
					}
					break;
				case BLD_INDUSTRIAL:
					i = (struct industrial*)found->item;
					if(i->employees < i->model->capacity){
						i->employees++;
						r->occupied++;
						return found;
					} else {
						found = NULL;
					}
					break;

			}
		}
		all_buildings = all_buildings->next;
	}
	return NULL;
}
void eval_res_building(struct city* the_city,struct building *bld)
{
	short ii;
	struct economy_status* e = the_city->e_status;
	unsigned int MAX_TAX_RATE = 60;
	//unsigned int TAX_RATE = 30;
	unsigned int TOTAL_JOBS = e->available_jobs + e->active_jobs;
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
	//attract=0.5;
#if 0
	printf("Model capacity: %d, occupied: %d\n", r->model->capacity,
						r->occupied);
#endif
	short diff = attract*(r->model->capacity - r->occupied);
	for(ii=0;ii<diff;ii++){
		if(find_closest_job_and_assign(the_city, bld) != NULL){
			e->active_jobs++;
			e->available_jobs--;
		}
	}
	//r->occupied += diff; already done in find_closest_job_and_assign
	//e->active_jobs += diff;
	//e->available_jobs -= diff;
#if 0
	printf("VAL: %g\n", attract);
	printf("Occupied: %d\n", r->occupied);
#endif
}

