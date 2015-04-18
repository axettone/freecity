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
struct building* init_residential(unsigned short x,unsigned short y, unsigned short size, unsigned short capacity,
	       	unsigned short occupied, unsigned short wealth){
  struct building* ret = (struct building*)xmalloc(sizeof(struct building));
  ret->x=x;
  ret->y=y;
  ret->type = BLD_RESIDENTIAL;
  ret->side_size = size;
  ret->item = (struct residential*)xmalloc(sizeof(struct residential));
  struct residential* r = (struct residential*)ret->item;
  r->capacity = capacity;
  r->occupied = occupied;
  r->wealth = wealth;
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
