#ifndef STRUCTS_H
#define STRUCTS_H
#include <inttypes.h>
typedef struct geo_pos{
  int x,y,z;
} POSITION;

typedef struct res_building{
  POSITION position;
  unsigned short capacity;
  unsigned short occupied;
  unsigned short wealth;
} RES_BUILDING;

typedef struct res_llist{
  RES_BUILDING bldng;
  struct residentials *next;
} residentials;
typedef enum schoolgrade { KINDER, ELEMENTARY, HIGH, COLLEGE, UNIVERSITY } schoolgrade_t;
typedef struct school_t{
  char name[80];
  float funding;
  schoolgrade_t grade;
  unsigned short capacity;
  unsigned short occupied;

}school_t;
typedef struct school_l{
  school_t school;
  struct school_l *next;
} school_l;

typedef struct matrix_t{
  char name[80]; //Not sure is useful
  uint8_t *m; //The real matrix
} matrix_t;
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
