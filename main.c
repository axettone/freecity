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
#include "structs.h"
#include "city.h"
#include "residentials.h"
#include "economy.h"
#include "school.h"
#include "matrixsys.h"
#include "ordinances.h"
#include "menu.h"
#include "map.h"
#include "xmalloc.h"
#include "power.h"

#define DEBUG 1

int main(int argc, char** argv){
	struct city the_city;
	printf("City name: ");
	fgets(the_city.name,80,stdin);
	printf("File name: ");
	fgets(the_city.filename,256,stdin);
	
	printf("Ok the city name is %s and it will be saved in %s\n",
			the_city.name,the_city.filename);
	int ii,jj;
  
	struct school_l *schools;
	struct map *the_map = init_map(100,100);  
	the_city.the_map = the_map;
	the_city.e_status = (struct economy_status*)xmalloc(sizeof(struct economy_status));
	the_city.e_status->available_cash = 1000000;
	the_city.e_status->happiness = 50;
	init_tax_sys(); //this is crap
	struct city_buildings *all_buildings; //wow 
	//POSITION demo;
	
	//Let's create a pair of residential building
	all_buildings = (struct city_buildings*)
		xmalloc(sizeof(struct city_buildings));

	all_buildings->building = init_residential(10,10,10,6,50);
	all_buildings->next = (struct city_buildings*)
		xmalloc(sizeof(struct city_buildings));
	all_buildings->next->building = init_residential(20,20,50,24,30);
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
  if(put_on_map(&sch1,the_city.the_map,50,50,3)==MAP_POS_OCC){
    printf("I can't put that school here, map is occupied\n");
  }
  if(put_on_map(&sch2,the_city.the_map,50,53,3) == MAP_POS_OCC){
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

  //Manual loop. This should be replaced one day
  //with a GUI and a thread

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
  return 0;
}
