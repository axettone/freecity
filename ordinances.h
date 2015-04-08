#ifndef ORDINANCES_H
#define ORDINANCES_H
#include <stdbool.h>
struct ordinances_t{
   bool PERMIT_GAMBLING;
   bool PERMIT_DRUGS;
   bool PERMIT_PROSTITUTION;

   bool FINING_MOTORISTS;
   bool FORBID_SMOKE;
   bool FREE_SCHOOLS;

} ordinances;

void apply_ordinances(int *balance,struct ordinances_t ordinances);
#endif
