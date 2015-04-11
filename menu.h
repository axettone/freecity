#ifndef MENU_H
#define MENU_H
#include "structs.h"
#include "city.h"
#define MN_EXIT 0
#define MN_BUDGET 1
#define MN_ORDINANCES 2
#define MN_SCHOOL 3
#define MN_CRIME 4
#define MN_SAVE 5
int menu();
void menu_error();

//These functions are almost for debugging

void menu_print_budget_data();
void menu_print_ordinances_data();
void menu_print_school_data(struct school_l* schools);
void menu_print_crime_data();
void menu_save_city(struct city*);
#endif
