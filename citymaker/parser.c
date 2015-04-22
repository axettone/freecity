#include "citymaker/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "city.h"
#include "map.h"
#include "structs.h"
#include "residentials.h"
#include "fb.h"

#define INSTR_SIZE 5

/**
 * Format: resid(X,Y,S)
 * X,Y = coordinates on the map
 * S   = square side side (e.g.: 3 is 3x3)
 */
void i_residential(struct city* the_city,char *l){
	printf("Analyzing %s\n",l);
	unsigned short x,y;
	unsigned int model_id;
	sscanf((&l[INSTR_SIZE+1]),"%hu,%hu,%d",&x,&y,&model_id);
	struct city_buildings* a_b = the_city->all_buildings;
	struct city_buildings* old = the_city->all_buildings;
	struct res_model* a_model = NULL; //Load with model_id from db
	struct building *b = init_residential(x,y,a_model);
	append_building(the_city, b);
	put_on_map(b, the_city->the_map,x,y,a_model->side_size);
}
void i_commercial(struct city* the_city, char *l){
}
void i_industrial(struct city* the_city, char *l){
}

int decode_line(struct city* the_city,char* line)
{
	if(strstr(line,"#")==line){
		printf("Found a comment\n");
		return 1;
	}
	if(strstr(line,"resid")==line){
		i_residential(the_city, line);
		return 0;
	}
	if(strstr(line, "comme")==line){
		i_commercial(the_city, line);
		return 0;
	}
	if(strstr(line, "indus")==line){
		i_industrial(the_city, line);
		return 0;
	}
	return -1;
}
void parse_cm_file(char* filename)
{
	struct city* the_city;
	printf("Initializing the city...\n");
	the_city = init_city("Ferrara", 1000, filename);
	printf("Parsing the file\n");
	char buff[81];

	FILE *fd = fopen(filename,"r");
	if(fd==NULL){
		printf("Cannot open file %s\n", filename);
		abort();
	}
	while(fgets(buff,80,fd)!=NULL){
		decode_line(the_city,buff);		
	}
	//Render on framebuffer (must be on console mode)
	struct fbdev* fb = init_fb();
	draw_city(fb,the_city);
	
	close(fd);
}
