/*
 * matrixsys.c - Let's use matrixes to handle pollution, wealth, crime...
 * 
 * All those things are mappend onto a separate matrix with numeric values.
 * For example, to compute crime level on (X,Y) we look into the "crime" matrix
 * at thoose coords.
 *
 * Copyright (C) 2015 Paolo Niccolò Giubelli
 *
 */
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "map.h"
#include "matrixsys.h"

int check_coords(matrix_t* matr, short x,short y){
  if(x>matr->width || x<0 || y<0 || y>matr->height)
    return INVALID_COORDS;
  return 0;
}


matrix_t *init_matrix(const char* name,short width,short height){
  matrix_t *ret = (matrix_t*)malloc(sizeof(matrix_t));
  strncpy(ret->name,name,80);
  ret->m = (uint8_t*)malloc(sizeof(uint8_t)*width*height);
  ret->width=width;
  ret->height=height; 
  memset(ret->m,0,width*height);
  return ret;
}

uint8_t read_value_from_matrix(matrix_t* matr,short x,short y){
  if(check_coords(matr,x,y) == 0){
    return matr->m[matr->width*y+x];
  }
}

uint8_t set_value_in_matrix(matrix_t* matr, uint8_t val, short x, short y){
  if(check_coords(matr,x,y)==0){
    matr->m[matr->width*y+x] = val;
  }
}

int not_on_edge(matrix_t* matr,short x, short y){
  if(x==0||x==matr->width-1||y==0||y==matr->height-1)
    return 0;
  return 1;
}

int matrix_sum_range(matrix_t* matr, short range, short x, short y){
  int ret = 0;
  int ii,jj;
  for(ii=y-range;ii<y+range+1;ii++){
    for(jj=x-range;jj<x+range+1;jj++){
      if(not_on_edge(matr,jj,ii)){
        ret+=matr->m[matr->width*ii+jj];
      }
    }
  }
  return ret;
}
int set_matrix_range_quadratic(matrix_t* matr, short range, int matr_op, uint8_t value, short x, short y){
  if(check_coords(matr,x,y) == 0){
    int ii,jj;
    uint8_t tmp;
    for(ii=y-range;ii<y+range+1;ii++){
      for(jj=x-range;jj<x+range+1;jj++){
        if(not_on_edge(matr,jj,ii)){
          tmp = value-(sqrt(pow(x-jj,2)+pow(y-ii,2))); //works
          switch(matr_op){
            case MATR_SUB:
              tmp*=-1;
            case MATR_ADD:
              matr->m[matr->width*ii+jj]+=tmp;
              break;
            case MATR_MUL:
              matr->m[matr->width*ii+jj]*=tmp;
              break;
          }     
        } else {
          continue;
        }
      }
    }
  } 
  return 0; //WTF?
}

void print_matrix(matrix_t* matr){
  int ii,jj;
  for(ii=0;ii<matr->width;ii++){
    for(jj=0;jj<matr->height;jj++){
      printf("%d", read_value_from_matrix(matr,ii,jj));
    }
    printf("\n");
  }
}
