#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "modeldbf.h"
#include "structs.h"
#include "xmalloc.h"
#include <string.h>
#include <errno.h>

//#define RES_MODELS_FILE "/home/axettone/Desktop/freecity/models/resid.bin"
#define RES_MODELS_FILE "resid.bin"
int open_model_file(const char* file)
{
	int fd = open(file,O_RDWR);
	if(fd<0)
		abort();
	return fd;
}

void close_model_file(int fd)
{
	//Probably the most unuseful function in the world
	close(fd);
}
void list_models()
{
	int fd = open_model_file(RES_MODELS_FILE);
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
	close_model_file(fd);

	//debug
	cur = root;
	while(cur!=NULL){
		printf("Found %s\n",cur->model.name);
		cur = cur->next;
	}
}

void insert_res_model(struct res_model model)
{
	int fd = open(RES_MODELS_FILE,O_APPEND|O_CREAT|O_WRONLY,0777);
	if(fd<0){
		printf("Error opening file\n");
		abort();
	}
	ssize_t written = write(fd,&model,sizeof(struct res_model));
	if(written<=0){
		printf("Error %d writing on file\n", errno);
		abort();
	}
	close_model_file(fd);
}
