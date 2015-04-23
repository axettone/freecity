#include "struts.h"
#include "industrials.h"

struct building* init_industrial(struct coords_s coords,
		struct ind_model* model)
{
	struct building* ret (struct building*)xmalloc(sizeof(struct building));
	ret->coords.x = x;ret->coords.y=y;
	ret->type=BLD_INDUSTRIAL;
	ret->side_size = model->size_size;
	ret->item = (struct industrial*)xmalloc(sizeof(struct industrial));
	struct industrial* i = (struct industrial*)ret->item;
	i->employees = 0;
	return ret;
}
