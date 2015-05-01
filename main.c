/*
 * main.c - Freecity main file. Now it's just a workbench, for testing
 * purposes.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "structs.h"
#include "city.h"
#include "residentials.h"
#include "commercials.h"
#include "industrials.h"
#include "economy.h"
#include "school.h"
#include "matrixsys.h"
#include "ordinances.h"
#include "menu.h"
#include "map.h"
#include "xmalloc.h"
#include "power.h"
#include "modeldbf.h"
#include "utils.h"

#define DEBUG 1


struct attractiveness attractiveness;

void sim_loop_a(struct city* the_city){
	unsigned int loop = 0;
	struct timespec loop_w,unuseful_w;
	loop_w.tv_sec = 0;
	loop_w.tv_nsec = 500000000;
	struct city_buildings* all_buildings;
	struct economy_status* e = the_city->e_status;
	init_tax_rates_default(&(e->tax_rates));
	while(1){
		printf("Loop %u\n", loop);
		//Resetting stats
		e->available_jobs=0;
		e->active_jobs=0;
		//TODO: Evaluating power and other services
		//...

		//Evaluating business buildings
		all_buildings=the_city->all_buildings;
		int ii=0;
		while(all_buildings != NULL){
			if(all_buildings->building->type == BLD_COMMERCIAL)
				eval_com_building(the_city,
						all_buildings->building);
			else if(all_buildings->building->type == BLD_INDUSTRIAL)
				eval_ind_building(the_city,
						all_buildings->building);
			all_buildings=all_buildings->next;
			ii++;
		}

		//Evaluating residential buildings
		all_buildings = the_city->all_buildings;
		while(all_buildings != NULL){
			//For each building
			if(all_buildings->building->type == BLD_RESIDENTIAL){
				eval_res_building(the_city,
					all_buildings->building);
			}
			
			all_buildings = all_buildings->next;
		}
		nanosleep(&loop_w,&unuseful_w);
		printf("Available jobs: %d\n", the_city->e_status->available_jobs);
		printf("Active jobs: %d\n", the_city->e_status->active_jobs);
		loop++;
	}
}
/**
 * At this time, main() is actually a workbench, where I test functions and
 * features.
 **/
int main(int argc, char** argv){
	int ii,jj,ran;
	struct city the_city;
	struct city *ferrara =
		init_city("Ferrara",500,"ferrara.fc");

	ferrara->e_status->available_cash = 100000;
	ferrara->e_status->available_jobs = 0;
	ferrara->e_status->active_jobs = 0;
	struct res_model_list* r_models=NULL;
	struct com_model_list* c_models=NULL;
	struct ind_model_list* i_models=NULL;

	init_models_lists(&r_models,&c_models,&i_models);

	//Adding some buildings
	struct building* b1,*b2,*b3;

	struct res_model* a_model = get_resmodel_by_id(r_models,1);
	struct com_model* c_model = get_commodel_by_id(c_models,1);
	struct ind_model* i_model = get_indmodel_by_id(i_models,1);

	if(a_model == NULL || c_model == NULL || i_model == NULL){
		abort();
	}

	//Generate 10,000 buildings
	for(ii=0;ii<10000;){
		ran = rand();
		b1=NULL;
		if(ran%2 == 0){
			b1 = init_residential(C_XY(0,0), a_model);

		} else if (ran %3==0) {
			b1 = init_commercial(C_XY(0,0), c_model);

		} else if (ran %5==0) {
			b1 = init_industrial(C_XY(0,0), i_model);
		}
		if(b1!=NULL){
			append_building(ferrara,b1);
			ii++;
		}
	}

	//Remove 100 random buildings
	//(just debuggin deatch_building)
	for(;ii>9900;ii--){
		unsigned int r_el = pos_rand(0,ii-1);
		detach_building(ferrara, 
				get_cbuilding_at(ferrara->all_buildings,r_el));	
	}
	printf("Appended %d new buildings in the city\n",
			count_buildings(ferrara->all_buildings));
	/*
	if(a_model == NULL){
		printf("Model not found\n");
		abort();
	}
	b1 = init_residential(C_XY(0,0),a_model);
	b2 = init_residential(C_XY(10,10),a_model);
	b3 = init_commercial(C_XY(20,20),c_model);

	//try to set wealth here
	append_building(ferrara,b1);
	append_building(ferrara,b2);
	append_building(ferrara,b3);
	*/
	sim_loop_a(ferrara);

	return 0;
	//CODE CEMETERY
	printf("City name: ");
	fgets(the_city.name,CITY_NAME_MAXLEN,stdin);
	printf("File name: ");
	fgets(the_city.filename,CITY_FILENAME_MAXLEN,stdin);
	
	printf("Ok the city name is %s and it will be saved in %s\n",
			the_city.name,the_city.filename);
  
	struct school_l *schools;
	struct map *the_map = init_map(100,100);  
	the_city.the_map = the_map;
	the_city.e_status = (struct economy_status*)
		xmalloc(sizeof(struct economy_status));
	the_city.e_status->available_cash = 1000000;
	the_city.e_status->happiness = 50;
	init_tax_sys(); //this is crap
	struct city_buildings *all_buildings; //wow 
	//POSITION demo;
	//struct mod_res* a_model = NULL;
	//Let's create a pair of residential building
	all_buildings = (struct city_buildings*)
		xmalloc(sizeof(struct city_buildings));

	all_buildings->building = init_residential(C_XY(10,10),a_model);
	all_buildings->next = (struct city_buildings*)
		xmalloc(sizeof(struct city_buildings));
	all_buildings->next->building = init_residential(C_XY(20,20),a_model);
	//List termination
	all_buildings->next->next = NULL;

	the_city.all_buildings = all_buildings;

  schools = (struct school_l*)malloc(sizeof(struct school_l)*2);
  schools[0].school.funding = 1.0;
  schools[0].school.occupied = 90;
  schools[0].school.capacity = 150;
  schools[0].school.grade = ELEMENTARY;

  schools[1].school.funding = 0.9;
  schools[1].school.occupied = 80;
  schools[1].school.capacity = 100;
  schools[1].school.grade = ELEMENTARY;

  struct map_item sch1,sch2;
  sch1.item_type = I_SCHOOL;
  sch2.item_type = I_SCHOOL;

  sch1.item = &schools[0];
  sch2.item = &schools[1];
  if(put_on_map(&sch1,the_city.the_map,m_coords(50,50),3)==MAP_POS_OCC){
    printf("I can't put that school here, map is occupied\n");
  }
  if(put_on_map(&sch2,the_city.the_map,m_coords(60,60),3) == MAP_POS_OCC){
    printf("I can't put that school here, map is occupied\n");
  }
  strncpy(schools[0].school.name,"Enrico Fermi",80);
  strncpy(schools[1].school.name,"Albert Einstein",80);
  schools[0].next = &schools[1];
  schools[1].next = NULL;

  /*
  for(ii=0;ii<the_map.width;ii++){
    for(jj=0;jj<the_map.height;jj++){
      if(the_map.items[jj*the_map.width+ii]!=0){
        school_t* tosa = (school_t*)the_map.items[jj*the_map.width+ii];
        printf("School name: %s\n",tosa->name);
        break;
      }
    }
  }*/

  struct matrix_t *pollution = init_matrix("Pollution matrix",the_city.the_map->width,the_map->height);
  printf("Our first matrix is: %s\n", pollution->name);
  //print_matrix(pollution);
  set_matrix_range_quadratic(pollution,5,MATR_ADD,10,25,0);
  print_matrix(pollution);
  printf("Pollution value in [10,15]: %d\n", read_value_from_matrix(pollution,10,15));
  printf("Population: %ld\n", count_population(all_buildings));
  //printf("Got taxes: %d\n", get_taxes(l_res));

  ordinances.PERMIT_GAMBLING = true;
  int balance = 0;
  apply_ordinances(&balance,ordinances);
  printf("Balance: %d\n",balance);

  school_overall_cost(schools);

  unsigned int loop = 0;

  while(1){
	  printf("Loop %u\n", loop);

	  sleep(1);
  }


  ////// CODE CEMETERY //////

  //Manual loop. This should be replaced one day
  //with a GUI and a thread
/*
  while(1){
    int ch = menu();
    if(ch==MN_EXIT)
      break;
    switch(ch){
      case MN_BUDGET:
        menu_print_budget_data();
        break;
      case MN_ORDINANCES:
        menu_print_ordinances_data();
        break;
      case MN_SCHOOL:
        menu_print_school_data(schools);
        break;
      case MN_CRIME:
        menu_print_crime_data();
        break;
      case MN_SAVE:
	menu_save_city(&the_city);
	break;
      default:
        menu_error();
        break;
    }
  }

*/	
/*
  return 0;
  while(1){
	attractiveness_compute(&attractiveness);

	people_migration();
	check_power_grid();
	evaluate_economy();
	//gather_taxes();
	//apply_ordinances();
	evaluate_government();
	autosave();
	advance_date();
  }
  return 0;
  */
}
