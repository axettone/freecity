#include <stdlib.h>
#include "structs.h"
#include "commercials.h"
struct building* init_commercial(struct coords_s origin,
		struct com_model* model)
{
	struct building* ret = (struct building*)xmalloc(sizeof(struct building));
	ret->origin = origin;
	ret->type = BLD_COMMERCIAL;
	ret->item = (struct commercial*)xmalloc(sizeof(struct commercial));
	struct commercial* c = (struct commercial*)ret->item;
	c->model = model;
	c->employees = 0;
	return ret;
}

