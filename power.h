#ifndef POWER_H
#define POWER_H

//power plants
#define PP_COAL 1
#define PP_GAS 2
#define PP_OIL 3
#define PP_NUCLEAR 4
#define PP_SOLAR 5
#define PP_FUSION 6 //ITER
#define PP_MAMR 7 //USS ENTERPRISE
#define PP_PLANCK 8 //String theory

struct power_grid{
	struct powerplant* power_plants;
};
struct powerplant {
	unsigned short jobs;
	unsigned short power;
	unsigned short status;
	unsigned short type;
};
void attach_power_plant(struct building* bldng,struct powerplant* pplant);
void merge_power_grids(struct power_grid* g1, struct power_grid* g2);
#endif
