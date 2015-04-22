#include "struts.h"
#include "industrials.h"

struct building* init_industrial(unsigned short x,unsigned short y,
		unsigned short size, unsigned short capacity,
		unsigned short employees, unsigned short tech_grade,
		unsigned short pollution, unsigned short power_req)
{
	struct building* ret (struct building*)xmalloc(sizeof(struct building));
	ret->x = x;ret->y=y;
	ret->type=BLD_INDUSTRIAL;
	ret->side_size = size;
	ret->item = (struct industrial*)xmalloc(sizeof(struct industrial));
	struct industrial* i = (struct industrial*)ret->item;
	i->capacity = capacity;
	i->employees = employees;
	i->tech_grade = tech_grade;
	i->pollution = pollution;
	i->power_req = power_req;
	return ret;
}
