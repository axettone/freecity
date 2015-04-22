#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "modeldbf.h"

int main(int argc, char** argv)
{
	printf("Freecity model creator\n");
	printf("1) Create a residential model\n");
	printf("2) List residential models\n");
	printf("3) Search for a model\n");
	printf("Make your choice >> ");
	int choice;
	scanf("%d", &choice);
	while(1){
		if(choice==1){
			
				struct res_model a_model;
				printf("Name (79 chars max): ");
				scanf("%s",a_model.name);
				printf("How many people can live there: ");
				scanf("%hu",&(a_model.capacity));
				printf("Wealth level [0-100]: ");
				scanf("%hu",&(a_model.wealth));
				printf("Side size on map: ");
				scanf("%hu",&(a_model.side_size));
				insert_res_model(a_model);
				break;
			} else if(choice == 2){
				list_models();
				break;
			}
		}	
	return 0;
}
