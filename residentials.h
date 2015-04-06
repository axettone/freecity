#ifndef RESIDENTIALS_H
#define RESIDENTIALS_H
#include "structs.h"
residentials* init_residential(POSITION pos, unsigned short c, unsigned short o, unsigned short w);

long count_population(residentials* buildings);
#endif
