#include "ordinances.h"

void apply_ordinances(int *balance, struct ordinances_t ordinances){
  *balance = 0;
  if(ordinances.PERMIT_GAMBLING){
    *balance+=100;
  }
}
