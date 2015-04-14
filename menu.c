/*
 * menu.c - Freecity main menu functions
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
#include "storage.h"
#include "menu.h"

int menu(){
  int choice;
  printf("1) Print budget data\n");
  printf("2) Print ordinances data\n");
  printf("3) Print schools data\n");
  printf("4) Print crime data\n");
  printf("5) Save city\n");
  printf("0) Exit\n");
  printf("Freecity>> ");
  scanf("%d",&choice);
  return choice;
}
void menu_print_budget_data(){

}
void menu_print_ordinances_data(){
}
void menu_print_school_data(struct school_l* s){
  while(1){
    printf("School %s: %d students on %d (%.2f)\n",s->school.name,
		    s->school.occupied,s->school.capacity,
		    s->school.occupied/(float)s->school.capacity);
    if(s->next == NULL)
      break;
    s = s->next;
  }
}
void menu_print_crime_data(){
}
void menu_save_city(struct city *the_city){
	save_city(the_city);
}
void menu_error(){
  printf("Wrong choice!\n");
}
