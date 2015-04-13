#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "city.h"
#include "structs.h"
#include "xmalloc.h"
size_t building_byte_size(struct building* b){
	size_t tmp_size = 0;
	switch(b->type){
			case BLD_RESIDENTIAL:
				tmp_size = sizeof(struct residential);
				break;
			case BLD_COMMERCIAL:
				tmp_size = sizeof(struct commercial);
				break;
			case BLD_INDUSTRIAL:
				tmp_size = sizeof(struct industrial);
				break;
		}
	return tmp_size;

}
void read_buildings(struct city *the_city,int fd, unsigned int bc, size_t* br){
	size_t tmp_size=0;
	unsigned int ii,jj;
	the_city->all_buildings = 
		(struct city_buildings*)xmalloc(sizeof(struct city_buildings));
	struct city_buildings* ptr = the_city->all_buildings;
	struct city_buildings* prev = ptr;

	for(ii=0;ii<bc;ii++){
		tmp_size = building_byte_size(ptr->building);
		*br+=read(fd,ptr->building,sizeof(struct building)-sizeof(void*));
		*br+=read(fd,ptr->building->item,tmp_size);
		prev=ptr;
		ptr++;
		prev->next = ptr;
	}
}
void write_buildings(struct city_buildings* all_buildings,int fd,size_t *written){
	size_t tmp_size=0;
	while(all_buildings!=NULL){
		//Let's skip the void* ptr and replace it with the
		//actual object
		*written += write(fd, all_buildings->building, 
				sizeof(struct building)-sizeof(void*));
		tmp_size = building_byte_size(all_buildings->building);
		*written += write(fd, all_buildings->building->item,tmp_size);
		all_buildings = all_buildings->next;
	}
}

/*
 * save the city into a binary file
 * File structure
 *
 * 80	bytes: city name
 * 256	bytes: city file
 * 4	bytes: number of buildings
 * 2	bytes: map width
 * 2	bytes: map height
 * 16	bytes: economy status
 * n*16	bytes: buildings (b=sizeof(struct building))
 *
 */
void save_city(struct city *the_city){
	printf("Saving the city...\n");
	unsigned int buildings = count_buildings(the_city->all_buildings);
	size_t written = 0;
	int fd = open(the_city->filename,O_WRONLY|O_CREAT|O_APPEND);
	written+=write(fd, the_city->name, 80*sizeof(char));
	written+=write(fd, the_city->filename, 256*sizeof(char));
	written+=write(fd, &buildings, sizeof(unsigned int));
	written+=write(fd, &(the_city->the_map->width),sizeof(unsigned short));
	written+=write(fd, &(the_city->the_map->height),sizeof(unsigned short));
	written+=write(fd, the_city->e_status,sizeof(struct economy_status));
	write_buildings(the_city->all_buildings,fd,&written);
	//fixed-length data end, begin variable data length
	close(fd);
	printf("Written %d bytes of data\n",written);
}

void load_city(char* filename, struct city* the_city){
	unsigned int bc=0;
	size_t br=0;
	int fd = open(filename, O_RDONLY);
	if(fd<0){
		printf("Can't open file %s, aborting.\n", filename);
		abort();
	}
	br+=read(fd,the_city->name,80*sizeof(char));
	strncpy(the_city->filename, 256, filename);
	br+=read(fd,&bc,sizeof(unsigned int));
       	br+=read(fd,&(the_city->the_map->width),sizeof(unsigned short));
	br+=read(fd,&(the_city->the_map->height),sizeof(unsigned short));
	br+=read(fd,the_city->e_status,sizeof(struct economy_status));
	read_buildings(the_city,fd,bc,&br);
	close(fd);

	//debug only
	printf("Read %d bytes\n", br);
	printf("Ok, I've loaded a city called %s from file %s\n");
	printf("It has %d buildings and map %dx%d\n",bc,the_city->the_map->width,
			the_city->the_map->height);
	
}
