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
