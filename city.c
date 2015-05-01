/*
 * city.c - Functions working on the city as a whole
 * Copyright (C) 2015 Paolo Niccolò Giubelli <paoloniccolo.giubelli@gmail.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include <stdlib.h>
#include <time.h>
#include "city.h"
#include "structs.h"
#include "map.h"

struct city* init_city(const char* city_name, 
		unsigned short map_size, const char* filename)
{
	struct city* the_city = (struct city*)xmalloc(sizeof(struct city));
	strncpy(the_city->name, city_name, CITY_NAME_MAXLEN);
	strncpy(the_city->filename, filename, CITY_FILENAME_MAXLEN);
	the_city->the_map = init_map(map_size,map_size);
	the_city->now_time = 0;
	the_city->e_status = 
		(struct economy_status*) xmalloc(sizeof(struct economy_status));
	the_city->all_buildings = NULL; 
//		(struct city_buildings*)xmalloc(sizeof(struct city_buildings));
//	the_city->all_buildings->building = NULL;
//	the_city->all_buildings->next = NULL;
	
	return the_city;
}
void append_building(struct city* c, struct building* b)
{
	struct city_buildings* cb = c->all_buildings;
	struct city_buildings* bkp = cb;
	while(cb != NULL){
		bkp=cb;
		cb = cb->next;
	}
	if(cb == c->all_buildings){
		//This is the first building
		c->all_buildings = 
			(struct city_buildings*)xmalloc(
					sizeof(struct city_buildings));
		
		cb = c->all_buildings;
	} else { 
		//There's at least one building
		cb = (struct city_buildings*)xmalloc(sizeof(struct city_buildings));
		bkp->next = cb;
	}
	cb->building = b;
	cb->next = NULL;
}
void detach_building(struct city* c,struct building* b)
{
	struct city_buildings* cb = c->all_buildings;
	struct city_buildings* bkp=cb;
	while(cb != NULL){
		if(c->all_buildings == cb){
			//Want to remove the first element
			c->all_buildings = c->all_buildings->next;
			return;
		}
		if(cb->building==b){
			bkp->next = cb->next;
			xfree(b);
			return;
		}
		bkp=cb;
		cb=cb->next;
	}
}
struct city_buildings* get_cbuilding_at(struct city_buildings* buildings, 
		unsigned int index){
	unsigned int ii = 0;
	while(buildings != NULL)
	{
		if(ii==index)
			return buildings;
		buildings = buildings->next;
		ii++;
	}
	abort();
}
unsigned int count_buildings(struct city_buildings* buildings){
	unsigned int ret = 0;
	while(buildings != NULL){
		ret++;
		buildings = buildings->next;
	}
	return ret;
}
