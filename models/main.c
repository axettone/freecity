/*
 * main.c - Models DB utility.
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
#include "structs.h"
#include "modeldbf.h"

int main(int argc, char** argv)
{
	struct res_model r_model;
	struct com_model c_model;
	struct ind_model i_model;

	struct res_model_list* res_l;
	struct com_model_list* com_l;
	struct ind_model_list* ind_l;

	printf("Freecity model creator\n");
	printf("1) Create a residential model\n");
	printf("2) Create a commercial model\n");
	printf("3) Create an industrial model\n");
	printf("4) List residential models\n");
	printf("5) List commercial models\n");
	printf("6) List industrial models\n");
	printf("7) Delete a residencial model\n");
	//printf("7) Search for a model\n");
	printf("Make your choice >> ");
	int choice;
	scanf("%d", &choice);
	//while(1){
		switch(choice){
			case 1:
				
				printf("Name (79 chars max): ");
				scanf("%s",r_model.name);
				printf("How many people can live there: ");
				scanf("%hu",&(r_model.capacity));
				printf("Wealth level [0-100]: ");
				scanf("%hu",&(r_model.wealth));
				printf("Side size on map: ");
				scanf("%hu",&(r_model.side_size));
				insert_res_model(r_model);
				break;
			case 2:
				printf("Name (79 chars max): ");
				scanf("%s", c_model.name);
				printf("How man many people can work here: ");
				scanf("%hu", &(c_model.capacity));
				printf("Wealth level [0-100]: ");
				scanf("%hu", &(c_model.wealth_grade));
				printf("Power required [0-100]: ");
				scanf("%hu",&(c_model.power_req));
				printf("Side size on map: ");
				scanf("%hu",&(c_model.side_size));
				insert_com_model(c_model);
				break;	
			case 3:
				//Do something
				printf("Name (79 chars max): ");
				scanf("%s", i_model.name);
				printf("How man many people can work here: ");
				scanf("%hu", &(i_model.capacity));
				printf("Wealth level [0-100]: ");
				scanf("%hu", &(i_model.wealth_grade));
				printf("Power required [0-100]: ");
				scanf("%hu",&(i_model.power_req));
				printf("Side size on map: ");
				scanf("%hu",&(i_model.side_size));
				insert_ind_model(i_model);

				break;
			
			case 4:
				list_models(I_RESIDENTIAL);
				break;
			case 5:
				list_models(I_COMMERCIAL);
				break;
			case 6:
				list_models(I_INDUSTRIAL);
				break;
			case 7:
				//Do something
				break;
			default:
				//Do something
				break;
		}
	//}
	return 0;
}
