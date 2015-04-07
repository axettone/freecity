#ifndef MATRIXSYS_H
#define MATRIXSYS_H
#include "structs.h"
#include <inttypes.h>
#define MATRIX_W 100 //Maybe matrix size should be dynamic
#define MATRIX_H 100
matrix_t *init_matrix(const char* matr_name);
uint8_t read_value_from_matrix(matrix_t* matr,short x,short y);
#endif
