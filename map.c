#include "map.h"
#include "structs.h"
struct map* init_map(struct map *the_map,short width,short height){
  the_map->width = width;
  the_map->height = height;
  the_map->items = malloc(sizeof(void*)*width*height);
  
}

