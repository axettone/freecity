#include <stdio.h>
#include <stdlib.h>
#include "citymaker/credits.h"
#include "structs.h"
#include "city.h"
#include "citymaker/parser.h"
int main(int argc, char** argv){
	print_credits();
	if(argc != 2) {
		printf("Error: you have to provide an input file\n");
		return 1;
	}
	parse_cm_file(argv[1]);
	return 0;
}
