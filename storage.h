#ifndef STORAGE_H
#define STORAGE_H
#include "city.h"
void save_city(struct city *the_city);
void load_city(char* filename, struct city *the_city);
#endif
