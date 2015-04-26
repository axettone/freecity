#ifndef MODELDBF_H
#include "structs.h"
#define RES_MODELS_FILE "models/resid.bin"
#define COM_MODELS_FILE "models/comm.bin"
#define IND_MODELS_FILE "models/indus.bin"
#define GOV_MODELS_FILE "models/govern.bin"
struct res_model_list
{
	struct res_model model;
	struct res_model_list* next;
};
struct com_model_list
{
	struct com_model model;
	struct com_model_list* next;
};

struct ind_model_list
{
	struct ind_model model;
	struct ind_model_list* next;
};

void init_models_lists();

void list_models(unsigned short type);
void insert_res_model(struct res_model);
void insert_com_model(struct com_model);
void insert_ind_model(struct ind_model);
void delete_res_model(struct res_model *model);
void delete_com_model(struct com_model *model);
void delete_ind_model(struct ind_model *model);

void describe_res_model(struct res_model *m);
void describe_com_model(struct com_model *m);
void describe_ind_model(struct ind_model *m);

//macro functions, look at modeldbf.c
void write_list_to_file_resmodel(int fd,struct res_model_list *list);
void write_list_to_file_commodel(int fd,struct com_model_list *list);
void write_list_to_file_indmodel(int fd,struct ind_model_list *list);

struct res_model_list* read_resmodel_list(int fd);
struct com_model_list* read_commodel_list(int fd);
struct ind_model_list* read_indmodel_list(int fd);

void list_items_resmodel (struct res_model_list* list);
void list_items_commodel (struct com_model_list* list);
void list_items_indmodel (struct ind_model_list* list);

unsigned int lastid_resmodel (struct res_model_list* list);
unsigned int lastid_commodel (struct com_model_list* list);
unsigned int lastid_indmodel (struct ind_model_list* list);

struct res_model* get_resmodel_by_id(struct res_model_list*,unsigned int);
struct com_model* get_commodel_by_id(struct com_model_list*,unsigned int);
struct ind_model* get_indmodel_by_id(struct ind_model_list*,unsigned int);

#define MODELDBF_H
#endif
