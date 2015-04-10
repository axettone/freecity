#include <stdlib.h>
#include "map.h"
#include "structs.h"
struct map* init_map(struct map *the_map,short width,short height){
  the_map->width = width;
  the_map->height = height;
  the_map->items = calloc(width*height,sizeof(void*)); 
  
}
int put_on_map(void* item,struct map* the_map,short x,short y,short side_size){
  int found=0,ii,jj;
  if(x+side_size >= the_map->width || y+side_size >= the_map->height){
    //map overflow
    return MAP_POS_OFL;
  }
  for(ii=y;ii<y+side_size;ii++){
    for(jj=x;jj<x+side_size;jj++){
      if(the_map->items[ii*the_map->width+jj]!=0)
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

