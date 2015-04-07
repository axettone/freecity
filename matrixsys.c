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
#include "matrixsys.h"

int check_coords(matrix_t* matr, short x,short y){
  if(x>MATRIX_W || x<0 || y<0 || y>MATRIX_H)
    return INVALID_COORDS;
  return 0;
}


matrix_t *init_matrix(const char* name){
  matrix_t *ret = (matrix_t*)malloc(sizeof(matrix_t));
  strncpy(ret->name,name,80);
  ret->m = (uint8_t*)malloc(sizeof(uint8_t)*MATRIX_W*MATRIX_H); 
  memset(ret->m,0,MATRIX_W*MATRIX_H);
  return ret;
}

uint8_t read_value_from_matrix(matrix_t* matr,short x,short y){
  if(check_coords(matr,x,y) == 0){
    return matr->m[MATRIX_W*y+x];
  }
}

uint8_t set_value_in_matrix(matrix_t* matr, uint8_t val, short x, short y){
  if(check_coords(matr,x,y)==0){
    matr->m[MATRIX_W*y+x] = val;
  }
}

int not_on_edge(short x, short y){
  if(x==0||x==MATRIX_W-1||y==0||y==MATRIX_H-1)
    return 0;
  return 1;
}

int matrix_sum_range(matrix_t* matr, short range, short x, short y){
  int ret = 0;
  int ii,jj;
  for(ii=x-range;ii<x+range+1;ii++){
    for(jj=y-range;jj<y+range+1;jj++){
      if(not_on_edge(ii,jj)){
        ret+=matr->m[MATRIX_W*jj+ii];
      }
    }
  }
  return ret;
}
int set_matrix_range_quadratic(matrix_t* matr, short range, int matr_op, uint8_t value, short x, short y){
  if(check_coords(matr,x,y) == 0){
    int ii,jj;
    uint8_t tmp;
    for(ii=x-range;ii<x+range+1;ii++){
      for(jj=y-range;jj<y+range+1;jj++){
        if(not_on_edge(ii,jj)){
          tmp = value-(sqrt(pow(x-ii,2)+pow(y-jj,2))); //works
          switch(matr_op){
            case MATR_SUB:
              tmp*=-1;
            case MATR_ADD:
              matr->m[MATRIX_W*jj+ii]+=tmp;
              break;
            case MATR_MUL:
              matr->m[MATRIX_W*jj+ii]*=tmp;
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
  for(ii=0;ii<MATRIX_W;ii++){
    for(jj=0;jj<MATRIX_H;jj++){
      printf("%d", read_value_from_matrix(matr,ii,jj));
    }
    printf("\n");
  }
}
