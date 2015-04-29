/*
 * economy.c - handling economy stuff: taxes, wealth, money...
 *
 * Copyright (c) 2015 Paolo Niccolò Giubelli
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "economy.h"
#include "structs.h"

//Please, make some benchmarks using inline function
void gather_residential_taxes(struct residential* r,struct tax_gather* g){
	if(r->model->wealth < TAX_LOW_TRESHOLD){
		g->low_res+=r->occupied*r->model->wealth;
	} else if(r->model->wealth < TAX_MID_TRESHOLD) {
		g->mid_res+=r->occupied*r->model->wealth;
	} else {
		g->high_res+=r->occupied*r->model->wealth;
	}
}
void gather_commercial_taxes(struct commercial* c, struct tax_gather*g){
}
void gather_industrial_taxes(struct industrial* i, struct tax_gather*g){
}
//Sheriff of Nottingham
void gather_taxes(struct tax_gather* gathering,struct city_buildings* buildings){
  if(gathering==NULL)
	  abort();
  if(buildings==NULL)
	  abort();
  while(1){
	  void (*f_ptr)(struct tax_gather*,struct city_buildings*);
	  if(buildings->building->type == BLD_RESIDENTIAL){
		  f_ptr = &gather_residential_taxes;
	  } else if(buildings->building->type == BLD_COMMERCIAL){
		  f_ptr = &gather_commercial_taxes;
	  } else if(buildings->building->type == BLD_INDUSTRIAL){
		  f_ptr = &gather_industrial_taxes;
	  }
	  f_ptr(buildings->building->item,gathering);
    buildings = buildings->next;
    if(buildings == NULL){
      break;
    }
  }
}

//Init tax system with default values
void init_tax_rates_default(struct tax_rates* tax_rates)
{
  tax_rates->low_res = 0.10;
  tax_rates->mid_res = 0.25;
  tax_rates->high_res = 0.40;

  tax_rates->low_com = 0.10;
  tax_rates->mid_com = 0.20;
  tax_rates->high_com = 0.30;

  tax_rates->low_ind = 0.05;
  tax_rates->mid_ind = 0.10;
  tax_rates->high_ind = 0.12;
}
void init_tax_rates(){
}

void attractiveness_compute(struct attractiveness* attr){
	printf("Evaluating attractiveness\n");	
}
float get_tax_rate_for_res(struct economy_status *e,struct residential*r)
{
	if(r->wealth<TAX_LOW_TRESHOLD)
		return e->tax_rates.low_res;
	if(r->wealth<TAX_MID_TRESHOLD)
		return e->tax_rates.mid_res;
	return e->tax_rates.high_res;
}
float get_tax_rate_for_com(struct economy_status *e,struct commercial *r)
{
	if(r->wealth<TAX_LOW_TRESHOLD)
		return e->tax_rates.low_com;
	if(r->wealth<TAX_MID_TRESHOLD)
		return e->tax_rates.mid_com;
	return e->tax_rates.high_com;
}
float get_tax_rate_for_ind(struct economy_status *e,struct industrial *r)
{
	if(r->wealth<TAX_LOW_TRESHOLD)
		return e->tax_rates.low_ind;
	if(r->wealth<TAX_MID_TRESHOLD)
		return e->tax_rates.mid_ind;
	return e->tax_rates.high_ind;
}


float get_tax_rate_for_bld(struct economy_status *e,struct building* bld)
{
	switch(bld->type){
		case BLD_RESIDENTIAL:
			return get_tax_rate_for_res(e,bld->item);
			break;
		case BLD_COMMERCIAL:
			return get_tax_rate_for_com(e,bld->item);
			break;
		case BLD_INDUSTRIAL:
			return get_tax_rate_for_ind(e,bld->item);
			break;
	}
}
