#ifndef MODELDBF_H
#include "structs.h"
struct res_model_list
{
	struct res_model model;
	struct res_model_list* next;
};
void list_models();
void insert_res_model(struct res_model);
void insert_com_model(struct com_model);
void insert_ind_model(struct ind_model);
#define MODELDBF_H
#endif
