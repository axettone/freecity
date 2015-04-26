/*
 * modeldbf.c - Functions working on model databases
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include "modeldbf.h"
#include "structs.h"
#include "xmalloc.h"
#include <string.h>
#include <errno.h>

#define IMPLEMENT_WRITE_LIST_TO_FILE(type,ltype,tname)\
	void write_list_to_file_##tname (int fd,ltype *list){\
		while(list!=NULL){\
			write(fd,&(list->model),sizeof(type));\
			list = list->next;\
		}\
	}

#define IMPLEMENT_READ_LIST(type,ltype,tname)\
	ltype *read_##tname##_list(int fd){\
		ltype *root = NULL;\
		ltype *old = NULL;\
		ltype *cur = NULL;\
		type item;\
		int nread;\
		while((nread=read(fd,&item,sizeof(type)))>0){\
			cur=(ltype*)xmalloc(sizeof(ltype));\
			memcpy(&(cur->model),&item,sizeof(type));\
			if(root==NULL){\
				root=cur;\
			} else {\
				old->next=cur;\
			}\
			cur->next=NULL;\
			old=cur;\
		}\
		return root;\
	}

#define IMPLEMENT_LIST_LIST(ltype,tname,describe_f_ptr)\
	void list_items_##tname (ltype* list){\
		while(list!=NULL){\
			describe_f_ptr(&(list->model));\
			list=list->next;\
		}\
	}
#define IMPLEMENT_LIST_LASTID(ltype,tname)\
	unsigned int lastid_##tname (ltype* list){\
		unsigned int r=0;\
		while(list!=NULL){\
			r=max(r,list->model.id);\
			list=list->next;\
		}\
		return r;\
	}
#define IMPLEMENT_LIST_GET_BY_ID(ltype,type,tname)\
	type* get_##tname##_by_id(ltype* list, unsigned int id){\
		while(list!=NULL){\
			if(list->model.id == id)\
				return &(list->model);\
			list=list->next;\
		}\
		return NULL;\
	}

IMPLEMENT_WRITE_LIST_TO_FILE(struct res_model,struct res_model_list,resmodel);
IMPLEMENT_WRITE_LIST_TO_FILE(struct com_model,struct com_model_list,commodel);
IMPLEMENT_WRITE_LIST_TO_FILE(struct ind_model,struct ind_model_list,indmodel);

IMPLEMENT_READ_LIST(struct res_model,struct res_model_list,resmodel);
IMPLEMENT_READ_LIST(struct com_model,struct com_model_list,commodel);
IMPLEMENT_READ_LIST(struct ind_model,struct ind_model_list,indmodel);

IMPLEMENT_LIST_LIST(struct res_model_list,resmodel,describe_res_model);
IMPLEMENT_LIST_LIST(struct com_model_list,commodel,describe_com_model);
IMPLEMENT_LIST_LIST(struct ind_model_list,indmodel,describe_ind_model);

IMPLEMENT_LIST_GET_BY_ID(struct res_model_list,struct res_model,resmodel);
IMPLEMENT_LIST_GET_BY_ID(struct com_model_list,struct com_model,commodel);
IMPLEMENT_LIST_GET_BY_ID(struct ind_model_list,struct ind_model,indmodel);

void init_models_lists(struct res_model_list** r_models,
		struct com_model_list** c_models,
		struct ind_model_list** i_models)
{
	if(*r_models == NULL){
		int fd = open(RES_MODELS_FILE, O_RDONLY);
		if(fd<0){
			printf("Error %d opening file\n", errno, RES_MODELS_FILE);
			abort();
		}
	       	*r_models = read_resmodel_list(fd);
		close(fd);
	}
	if(*c_models == NULL){
		int fd = open(COM_MODELS_FILE, O_RDONLY);
		if(fd<0){
			printf("Error %d opening file\n", errno, COM_MODELS_FILE);
			abort();
		}
		*c_models = read_commodel_list(fd);
		close(fd);
	}
	if(*i_models == NULL){
		int fd = open(IND_MODELS_FILE, O_RDONLY);
		if(fd<0){
			printf("Error %d opening file\n", errno, IND_MODELS_FILE);
			abort();
		}
		*i_models = read_indmodel_list(fd);
		close(fd);
	}	
}
void describe_res_model(struct res_model *m){
	printf("%u\n",m->id);
	printf("Model name: %s\n", m->name);
	printf("Size on map: %hux%hu\n",m->side_size,m->side_size);
	printf("How many people can live here: %d\n", m->capacity);
}
void describe_com_model(struct com_model *m){

}
void describe_ind_model(struct ind_model *m){
}
void list_models(unsigned short type)
{
	int fd;
	switch(type){
		case I_RESIDENTIAL:
			fd=open(RES_MODELS_FILE,O_RDONLY);
			if(fd<0){
				printf("Error %d opening %s!",errno,RES_MODELS_FILE);
				abort();
			}
			struct res_model_list *list_a = read_resmodel_list(fd);
			list_items_resmodel(list_a);
			break;
		case I_COMMERCIAL:
			fd=open(COM_MODELS_FILE,O_RDONLY);
			struct com_model_list *list_b = read_commodel_list(fd);
			list_items_commodel(list_b);
			break;
		case I_INDUSTRIAL:
			fd=open(IND_MODELS_FILE,O_RDONLY);
			struct ind_model_list *list_c = read_indmodel_list(fd);
			list_items_indmodel(list_c);
	};
}

void insert_raw_model(int fd,void* data,size_t len)
{
	if(fd<0){
		printf("Error opening file: %d\n",errno);
		abort();
	}
	if(write(fd,data,len)<=0){
		printf("Error %d writing on file\n", errno);
		abort();
	}
}
void insert_res_model(struct res_model model)
{
	int fd = open(RES_MODELS_FILE,O_APPEND|O_CREAT|O_WRONLY,0777);
	insert_raw_model(fd,&model,sizeof(struct res_model));
	close(fd);
}
void insert_com_model(struct com_model model)
{
	int fd = open(COM_MODELS_FILE,O_APPEND|O_CREAT|O_WRONLY,0777);
	insert_raw_model(fd,&model,sizeof(struct com_model));
	close(fd);
}
void insert_ind_model(struct ind_model model)
{
	int fd = open(IND_MODELS_FILE,O_APPEND|O_CREAT|O_WRONLY,0777);
	insert_raw_model(fd,&model,sizeof(struct ind_model));
	close(fd);
}

void delete_res_model(struct res_model*	model)
{
	struct res_model_list *the_list; //Feed this
	struct res_model_list *start;
	struct res_model_list *prev;

	prev=the_list;
	start=the_list;

	while(the_list != NULL)
	{
		if(the_list->model.id == model->id){
			prev->next = the_list->next;	
			break;
		}
		prev=the_list;
		the_list=the_list->next;
	}

	int fd = open("res_tmp_file.bin",O_WRONLY|O_CREAT,0777);
	write_list_to_file_resmodel(fd,start);
	close(fd);
	remove(RES_MODELS_FILE);
	rename("res_tmp_file.bin",RES_MODELS_FILE);
}
void delete_com_model(struct com_model *model)
{
	
}
void delete_ind_model(struct ind_model *model)
{

}
