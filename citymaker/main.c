/*
 * main.c - Citymaker util. It creates debug cities and draws them on the
 * framebuffer.
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
