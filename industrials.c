/*
 * industrials.c - Function that handle industrial buildings
 * Copyright (C) 2015 Paolo Niccolò Giubelli <paoloniccolo.giubelli@gmail.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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
