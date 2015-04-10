#ifndef MATRIXSYS_H
#define MATRIXSYS_H
#include "structs.h"
#include <inttypes.h>

//Horrible, horrible, horrible
//#define MATRIX_W 100 //Maybe matrix size should be dynamic
//#define MATRIX_H 100

#define INVALID_COORDS 1

#define MATR_ADD 1
#define MATR_SUB 2
#define MATR_MUL 3

int check_coords(struct matrix_t* matr, short x,short y);
struct matrix_t *init_matrix(const char* matr_name,short w,short h);
uint8_t read_value_from_matrix(struct matrix_t* matr,short x,short y);
int set_matrix_range_quadratic(struct matrix_t* matr, short range, int matr_op, uint8_t value, short x, short y);
void print_matrix(struct matrix_t* matr); //for debug purposes only
int not_on_edge(struct matrix_t* matr,short x, short y);
int matrix_sum_range(struct matrix_t* matr, short range, short x, short y);
#endif
