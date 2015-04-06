/*
 * economy.c - handling economy stuff: taxes, wealth, money...
 *
 * Copyright (c) 2015 Paolo Niccolò Giubelli
 *
 */

#include <stdlib.h>
#include "economy.h"
#include "structs.h"

int get_taxes(residentials* buildings){
#if 1
  printf("Getting taxes with rate %f\n",tax_sys.mid_res);
#endif
  int ret = 0;
  while(1){
    if(buildings->bldng.wealth <= 25){
      ret += buildings->bldng.occupied*tax_sys.low_res*buildings->bldng.wealth;
    } else if(buildings->bldng.wealth <= 50) {
      ret += buildings->bldng.occupied*tax_sys.mid_res*buildings->bldng.wealth;
    } else {
      ret += buildings->bldng.occupied*tax_sys.high_res*buildings->bldng.wealth;
    }
    buildings = buildings->next;
    if(buildings == NULL){
      break;
    }
  }
  return ret;
}

//Init tax system
void init_tax_sys(){
  tax_sys.low_red = 0.10;
  tax_sys.mid_red = 0.25;
  tax_sys.high_res = 0.40;

  tax_sys.low_com = 0.10;
  tax_sys.mid_com = 0.20;
  tax_sys.high_com = 0.30;

  tax_sys.low_ind = 0.05;
  tax_sys.mid_ind = 0.10;
  tax_sys.high_ind = 0.12;
}
