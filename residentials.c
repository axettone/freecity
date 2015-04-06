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
residentials* init_residential(POSITION pos, unsigned short c, unsigned short o, unsigned short w)
{
  residentials* ret = malloc(sizeof(residentials));
  memcpy(&(ret->bldng.position),&pos,sizeof(POSITION));
  ret->bldng.capacity = c;
  ret->bldng.occupied = o;
  ret->bldng.wealth = w;
  return ret;
}

long count_population(residentials* buildings){
  long ret = 0;
  while(1){
    ret += buildings->bldng.occupied;
    buildings = buildings->next;
    if(buildings == NULL){
      break;
    }
  }
  return ret;
}
