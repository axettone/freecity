#ifndef ECONOMY_H
#define ECONOMY_H
#include "structs.h"
void gather_taxes(struct tax_gather* gathering,
		struct city_buildings* buildings);

void gather_residential_taxes(struct residential* r, struct tax_gather* g);
void gather_commercial_taxes(struct commercial* c, struct tax_gather* g);
void gather_industrial_taxes(struct industrial* i, struct tax_gather* g);

void init_tax_sys();
void attractiveness_compute(struct attractiveness* attr);
#endif
