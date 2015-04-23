#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "modeldbf.h"
#include "structs.h"
#include "xmalloc.h"
#include <string.h>
#include <errno.h>

#define RES_MODELS_FILE "resid.bin"
#define COM_MODELS_FILE "comm.bin"
#define IND_MODELS_FILE "indus.bin"
#define GOV_MODELS_FILE "govern.bin"

void list_models()
{
	int fd = open(RES_MODELS_FILE,O_RDONLY);
	struct res_model_list* root=NULL;
	struct res_model_list* cur=NULL;
	struct res_model_list* last=NULL;
	struct res_model tmp;
	ssize_t nread = 0;
	while(1){
		cur = (struct res_model_list*)
			xmalloc(sizeof(struct res_model_list));
		nread = read(fd,&tmp,sizeof(struct res_model));
		if(nread==0)
			break;
		memcpy(&(cur->model),&tmp,sizeof(struct res_model));
		if(last == NULL){
			root = cur;
			root->next = NULL;
			last = cur;
		} else {
			last->next = cur;
			last = cur;
			cur->next = NULL;
		}

	}
	close(fd);

	//debug
	cur = root;
	while(cur!=NULL){
		printf("Found %s\n",cur->model.name);
		cur = cur->next;
	}
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

