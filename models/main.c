#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "modeldbf.h"

int main(int argc, char** argv)
{
	printf("Freecity model creator\n");
	printf("1) Create a residential model\n");
	printf("2) Create a commercial model\n");
	printf("3) Create an industrial model\n");
	printf("4) List residential models\n");
	printf("5) List commercial models\n");
	printf("6) List industrial models\n");
	//printf("7) Search for a model\n");
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
				struct com_model a_model;
				printf("Name (79 chars max): ");
				scanf("%s", a_model.name);
				printf("How man many people can work here: ");
				scanf("%hu", &(a_model.capacity));
				printf("Wealth level [0-100]: ");
				scanf("%hu", &(a_model.wealth_grade));
				printf("Power required [0-100]: ");
				scanf("%hu",&(a_model.power_req));
				printf("Side size on map: ");
				scanf("%hu",&(a_model.side_size));
				insert_com_model(a_model);
				break;	
			} else if(choice == 3){
			
			} else if(choice == 4){
				list_models();
				break;
			} else if(choice == 5){
			} else if(choice == 6){

			} else {
				printf("Not implemented\n");
			}
		}	
	return 0;
}
