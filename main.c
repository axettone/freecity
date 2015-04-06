#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "residentials.h"
#include "economy.h"
#include "school.h"

#define DEBUG 1

int main(int argc, char** argv){
  int ii;
  residentials *l_res;
  school_l *schools;

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
  schools = (school_l*)malloc(sizeof(school_l));
  schools->school.funding = 1.0;
  schools->school.occupied = 90;
  schools->school.capacity = 150;
  schools->school.grade = ELEMENTARY;
  strncpy(schools->school.name,"Enrico Fermi",80);
  schools->next = NULL;
  printf("Population: %ld\n", count_population(l_res));
  printf("Got taxes: %d\n", get_taxes(l_res));
  school_overall_cost(schools);
  return 0;
}
