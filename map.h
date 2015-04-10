/**
 * map.h - map & object positioning on map structures and functions
 */
#ifndef MAP_H
#define MAP_H
#include "structs.h"
struct map{
  short width;
  short height;
  void** items;
};

struct map* init_map(struct map *the_map,short width,short height);

#endif
