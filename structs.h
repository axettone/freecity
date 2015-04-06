#ifndef STRUCTS_H
#define STRUCTS_H
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