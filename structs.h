/*
 * structs.h - This file contains almost all the structures and constants
 * used by freecity.
 *
 * Some notes:
 *
 * BLD_COMMERCIAL and BLD_INDUSTRIAL should be multiples of BLD_BUSINESS
 *
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
#ifndef STRUCTS_H
#define STRUCTS_H
#include <inttypes.h>
#include <time.h>
#define I_SCHOOL 5
#define I_POLICE 4i
#define I_RESIDENTIAL 1
#define I_INDUSTRIAL 14
#define I_COMMERCIAL 21

//building types
#define BLD_RESIDENTIAL 1
#define BLD_COMMERCIAL 21
#define BLD_INDUSTRIAL 14
#define BLD_GOVERNATIVE 4
#define BLD_BUSINESS 7

#define I_FIRE 5
#define I_STREET 6
//deprecated
typedef struct geo_pos{
  int x,y,z;
} POSITION __attribute__ ((deprecated));

struct coords_s{
	unsigned short x;
	unsigned short y;
};
struct building {
	struct coords_s origin;
	unsigned short side_size;
	unsigned short type;
	struct power_grid* p_grid;
	void* item; //Points to a residential,commercial or industrial struct
};

struct prod_requisites{
	unsigned short education;
	unsigned short pollution;
};
//Models
struct res_model
{
	unsigned int id;
	char name[81];
	unsigned short capacity;
	unsigned short wealth;
	void *graphics; //unused
	unsigned short side_size;
};
struct com_model
{
	unsigned int id;
	char name[80];
	unsigned short capacity;
	unsigned short wealth_grade;
	unsigned short power_req;
	void *graphics; //unused
	unsigned short side_size;
};
struct ind_model
{
	unsigned int id;
	char name[80];
	unsigned short capacity;
	unsigned short tech_grade;
	unsigned short wealth_grade;
	unsigned short power_req;
	unsigned short pollution;
	void *graphics;//unused
	unsigned short side_size;
};
struct residential{
	//struct building bldng;
	struct res_model* model;
	unsigned short occupied;
	unsigned short wealth;
};

struct commercial{	//struct building bldng;
	struct com_model* model;
	unsigned short employees;
	unsigned short wealth;
};

struct industrial{
	//struct building bldng;
	struct ind_model* model;
	unsigned short employees;
	unsigned short wealth;
};

struct city_buildings {
	struct city_buildings *next;
	struct building *building;

};
/*
typedef struct res_llist{
  RES_BUILDING bldng;
  struct residentials *next;
} residentials __attribute__ ((deprecated));
*/
typedef enum schoolgrade { 
	KINDER, ELEMENTARY, HIGH, COLLEGE, UNIVERSITY 
} schoolgrade_t;

struct school_t{
  char name[80];
  float funding;
  schoolgrade_t grade;
  unsigned short capacity;
  unsigned short occupied;

};

struct hospital_t{
  char name[80];
  float funding;
  unsigned short capacity;
  unsigned short occupied;
};

struct police_station{
  float funding;
  unsigned short agents;
  unsigned short inmates;
};

struct school_l{
  struct school_t school;
  struct school_l *next;
};

struct matrix_t{
  char name[80]; //Not sure is useful
  short width;
  short height;
  uint8_t *m; //The real matrix
};

struct map_item{
  int item_type;
  void *item;
};

struct tax_rates{
  float low_res,mid_res,high_res;
  float low_com,mid_com,high_com;
  float low_ind,mid_ind,high_ind;
};

struct economy_status {
  long available_cash;
  int happiness;
  unsigned int available_jobs;
  unsigned int active_jobs;
  struct tax_rates tax_rates;

};

struct attractiveness{
  uint8_t low_res,mid_res,high_res;
  uint8_t low_com,mid_com,high_com;
  uint8_t low_ind,mid_ind,high_ind;
};

struct tax_gather{
	unsigned int low_res,mid_res,high_res;
	unsigned int low_com,mid_com,hight_com;
	unsigned int low_ind,mid_ind,high_ind;
};
#endif
