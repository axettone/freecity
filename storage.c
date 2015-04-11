#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "city.h"
#include "structs.h"

void write_buildings(struct city_buildings* all_buildings,int fd,size_t *written){
	size_t tmp_size=0;
	while(all_buildings!=NULL){
		//Let's skip the void* ptr and replace it with the
		//actual object
		*written += write(fd, all_buildings->building, 
				sizeof(struct building)-sizeof(void*));
		switch(all_buildings->building->type){
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

void load_city(struct city* the_city){

}
