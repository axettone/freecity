#ifndef STRUCTS_H
#define STRUCTS_H
#include <inttypes.h>
#include <time.h>
#define I_SCHOOL 1
#define I_POLICE 2
#define I_RESIDENTIAL 3
#define I_INDUSTRIAL 4

//building types
#define BLD_RESIDENTIAL 1
#define BLD_COMMERCIAL 2
#define BLD_INDUSTRIAL 3
#define BLD_GOVERNATIVE 4

#define I_FIRE 5
#define I_STREET 6
//deprecated
typedef struct geo_pos{
  int x,y,z;
} POSITION __attribute__ ((deprecated));


struct building {
	unsigned short x,y;
	unsigned short side_size;
	unsigned short type;
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
	char name[80];
	unsigned short capacity;
	unsigned short wealth;
	void *graphics; //unused
}
struct com_model
{
	unsigned int id;
	char name[80];
	unsigned short capacity;
	unsigned short wealth_grade;
	unsigned short power_req;
	void *graphics; //unused
}
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
}
struct residential{
	//struct building bldng;
	struct res_model* model;
	unsigned short occupied;
	unsigned short happiness;
};

struct commercial{	//struct building bldng;
	struct com_model* model;
	unsigned short employees;
};

struct industrial{
	//struct building bldng;
	struct ind_model* model;
	unsigned short employees;
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

struct economy_status {
  long available_cash;
  int happiness;

};

struct {
  float low_res,mid_res,high_res;
  float low_com,mid_com,high_com;
  float low_ind,mid_ind,high_ind;
} tax_sys;

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
