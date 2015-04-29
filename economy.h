#ifndef ECONOMY_H
#define ECONOMY_H
#include "structs.h"

#define TAX_LOW_TRESHOLD 35
#define TAX_MID_TRESHOLD 75

void gather_taxes(struct tax_gather* gathering,
		struct city_buildings* buildings);

void gather_residential_taxes(struct residential* r, struct tax_gather* g);
void gather_commercial_taxes(struct commercial* c, struct tax_gather* g);
void gather_industrial_taxes(struct industrial* i, struct tax_gather* g);

void init_tax_rates_default(struct tax_rates* tax_rates);
float get_tax_rate_for_bld(struct economy_status *e,struct building* bld);
void attractiveness_compute(struct attractiveness* attr);
#endif
