#ifndef STRUCTS_H
#define STRUCTS_H
#include <inttypes.h>

#define I_SCHOOL 1
#define I_POLICE 2
#define I_RESIDENTIAL 3
#define I_INDUSTRIAL 4
#define I_FIRE 5
#define I_STREET 6

typedef struct geo_pos{
  int x,y,z;
} POSITION;

typedef struct res_building{
  POSITION position;
  unsigned short capacity;
  unsigned short occupied;
  unsigned short wealth;
  unsigned short happiness;
} RES_BUILDING;

typedef struct res_llist{
  RES_BUILDING bldng;
  struct residentials *next;
} residentials;

typedef enum schoolgrade { KINDER, ELEMENTARY, HIGH, COLLEGE, UNIVERSITY } schoolgrade_t;

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

struct {
  long available_cash;
  int happiness;

} economy_status;

struct {
  float low_res,mid_res,high_res;
  float low_com,mid_com,high_com;
  float low_ind,mid_ind,high_ind;
} tax_sys;
#endif
