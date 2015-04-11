#include <stdlib.h>
#include "map.h"
#include "structs.h"
#include "xmalloc.h"

struct map* init_map(short width,short height){
	struct map* the_map = (struct map*)xmalloc(sizeof(struct map));
	the_map->width = width;
	the_map->height = height;
	the_map->items = (struct map_item*)calloc(width*height,
			sizeof(struct map_item));
	return the_map;	
  
}

/**
 * Put an item (e.g. a building like a school) on the map. The target position
 * on map is described by (x,y) coordinates. The size of the building is
 * side_size^2 blocks on the map. The building is encapsulated into a map_item
 * structure, and it will be pointed from each block on the map.
 * If any target block of the map is already occupied by something else,
 * a MAP_POS_OCC is returned. If you're trying to put the item on the border
 * of the map and there's no enough space, MAP_POS_OCC is returned. If 
 * everything was ok, MAP_POS_OK is returned.
 */
int put_on_map(struct map_item* item,struct map* the_map,short x,short y,
		short side_size){
  int found=0,ii,jj;
  if(x+side_size >= the_map->width || y+side_size >= the_map->height){
    //map overflow
    return MAP_POS_OFL;
  }
  
  for(ii=y;ii<y+side_size;ii++){
    for(jj=x;jj<x+side_size;jj++){
      if(the_map->items[ii*the_map->width+jj]!=NULL)
        return MAP_POS_OCC;
    }
  }
  for(ii=y;ii<y+side_size;ii++){
    for(jj=x;jj<x+side_size;jj++){
      the_map->items[ii*the_map->width+jj] = item;
    }
  }
  
  return MAP_POS_OK; 
}

