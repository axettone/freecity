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
