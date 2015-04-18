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
	if(r->wealth < 35){
		g->low_res+=r->occupied*r->wealth;
	} else if(r->wealth < 75) {
		g->mid_res+=r->occupied*r->wealth;
	} else {
		g->high_res+=r->occupied*r->wealth;
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

//Init tax system
void init_tax_sys(){
  tax_sys.low_res = 0.10;
  tax_sys.mid_res = 0.25;
  tax_sys.high_res = 0.40;

  tax_sys.low_com = 0.10;
  tax_sys.mid_com = 0.20;
  tax_sys.high_com = 0.30;

  tax_sys.low_ind = 0.05;
  tax_sys.mid_ind = 0.10;
  tax_sys.high_ind = 0.12;
}

void attractiveness_compute(struct attractiveness* attr){
	printf("Evaluating attractiveness\n");	
}
