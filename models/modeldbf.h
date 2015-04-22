#ifndef MODELDBF_H
#include "structs.h"
struct res_model_list
{
	struct res_model model;
	struct res_model_list* next;
};
int open_model_file(const char* file);
void list_models();
void insert_res_model(struct res_model);
#define MODELDBF_H
#endif
