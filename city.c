#include <stdlib.h>
#include "city.h"
#include "structs.h"

unsigned int count_buildings(struct city_buildings* buildings){
	unsigned int ret = 0;
	while(buildings != NULL){
		ret++;
		buildings = buildings->next;
	}
	return ret;
}
