#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "residentials.h"
#include "economy.h"


#define DEBUG 1

int main(int argc, char** argv){
  int ii;
  residentials *l_res;

  economy_status.available_cash = 1000000;
  economy_status.happiness = 50;
  init_tax_sys();

  POSITION demo;
  l_res = init_residential(demo,100,0,50);
  l_res->next = NULL;
  for(ii=1;ii<100;ii++){
   l_res->next = init_residential(demo,100,ii,50);
   l_res = l_res->next;
  }

  printf("Population: %ld\n", count_population(l_res));
  printf("Got taxes: %ld\n", get_taxes(l_res));
  return 0;
}
