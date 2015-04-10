/**
 * map.h - map & object positioning on map structures and functions
 *
 * MAP_POS_OFL - Map position overflow
 * MAP_POS_OCC - Map position occupied
 * MAP_POS_OK  - Map position free
 */
#ifndef MAP_H
#define MAP_H

#define MAP_POS_OFL 2
#define MAP_POS_OCC 1
#define MAP_POS_OK 0
#include "structs.h"
#include "map.h"

struct map{
  short width;
  short height;
  void** items;
};

struct map* init_map(struct map *the_map,short width,short height);
int put_on_map(void* item,struct map* the_map,short x,short y,short side_size);
#endif
