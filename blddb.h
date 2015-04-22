#ifndef BLDDB_H
#include "structs.h"

struct residential_db
{
	struct res_model;
	struct residential_db* next;
}

struct commercial_db
{
	struct com_model;
	struct commercial_db* next;
}
struct industrial_db
{
	struct ind_model;
	struct industrial_db* next;
}

struct *residential_db get_residential_db();
struct *commercial_db get_commercial_db();
struct *industrial_db get_industrial_db();

void* find_model_by_id(unsigned int id, unsigned short model_type);
void* insert_model_db(void* model, unsigned short model_type);
void delete_model_db(unsigned int id);
#define BLDDB_H
#endif
