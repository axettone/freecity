#include <stdio.h>
#include <stdlib.h>
#include "school.h"
#include "structs.h"

int school_overall_cost(school_l* schools){
  int ret = 0;

  while(1){
    ret += schools->school.funding*schools->school.occupied;
    if(schools->next == NULL){
      break;
    }
    schools = schools->next;
  }

  return ret;
}
