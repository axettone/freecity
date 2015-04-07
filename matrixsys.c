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
#include "matrixsys.h"

matrix_t *init_matrix(const char* name){
  matrix_t *ret = (matrix_t*)malloc(sizeof(matrix_t));
  strncpy(ret->name,name,80);
  ret->m = (uint8_t*)malloc(sizeof(uint8_t)*MATRIX_W*MATRIX_H); 
  memset(ret->m,10,MATRIX_W*MATRIX_H);
  return ret;
}

uint8_t read_value_from_matrix(matrix_t* matr,short x,short y){
  if(x>MATRIX_W || y>MATRIX_H || x<0 || y<0){
    return -1;
  }
  return matr->m[MATRIX_W*x+y];
}
