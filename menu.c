#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int menu(){
  int choice;
  printf("1) Print budget data\n");
  printf("2) Print ordinances data\n");
  printf("3) Print schools data\n");
  printf("4) Print crime data\n");
  printf("0) Exit\n");
  printf("Freecity>> ");
  scanf("%d",&choice);
  return choice;
}
void menu_print_budget_data(){

}
void menu_print_ordinances_data(){
}
void menu_print_school_data(school_l* s){
  while(1){
    printf("School %s: %d students on %d (%.2f)\n",s->school.name,s->school.occupied,s->school.capacity,s->school.occupied/(float)s->school.capacity);
    if(s->next == NULL)
      break;
    s = s->next;
  }
}
void menu_print_crime_data(){
}

void menu_error(){
  printf("Wrong choice!\n");
}
