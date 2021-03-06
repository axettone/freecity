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

#define C_XY(X,Y) m_coords(X,Y)

struct map{
  unsigned short width;
  unsigned short height;
  struct map_item** items;
};

struct map* init_map(unsigned short width, unsigned short height);
int put_on_map(struct map_item* item,struct map* the_map,struct coords_s coords,
		unsigned short side_size);

inline struct coords_s m_coords(unsigned short x, unsigned short y);
#endif
