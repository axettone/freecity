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
