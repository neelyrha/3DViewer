#ifndef _3D_VIEWER_H
#define _3D_VIEWER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct data {
  unsigned int qty_vertex;  // lines start with v * 3 + 3 for first vertex
  unsigned int qty_facet;   // lines start with f
  unsigned int qty_vertex_in_facet;  // lines * qty in line
  double max_vertex;
  double *matrix_vertex;
  unsigned int *matrix_facet;  // qty of matrix_facet == (qty_facet[i] *
                               // qty_edges_in_facet[i]) * 2;
} struct_data;

/**
 * @brief Opens a file to calculate the amount of memory to allocate
 *
 * @param file_name
 * @param data structure with object data
 * @return int
 */
// parcer
int first_file_open(const char *file_name, struct_data *data);

/**
 * @brief Fills the matrix with data about vertices and connections
 *
 * @param file_name
 * @param data structure with object data
 * @return int errors
 */
int second_file_open(const char *file_name, struct_data *data);

/**
 * @brief Returns the larger vertex value for scaling the entire object
 *
 * @param num1 verticle value
 * @param num2 verticle value
 * @return double verticle value
 */

double max(double num1, double num2);
/**
 * @brief  Scales the object so that the maximum value of the vertex does not
 * exceed 1 (required for correct work in QT)
 *
 * @param data structure with object data
 * @return int
 */
int vertex_normalize(struct_data *data);
/**
 * @brief Creating a duplicate of a matrix to change it when an object is moved
 *
 * @param input structure with object data
 * @param output structure with object data
 */
void copy_data_matrix(struct_data input, struct_data *output);

// dynamic memory allocation and free
/**
 * @brief Allocates memory for matrix
 *
 * @param data
 * @return int errors
 */
int create_matrix_data(struct_data *data);
/**
 * @brief Frees allocated memory
 *
 * @param data
 */
void remove_matrix_data(struct_data *data);

// move_data
void translating(struct_data *data, int x_move, int y_move, int z_move);
/**
 * @brief Calculates the new position of an object when its scale changes
 *
 * @param data verticles structure
 * @param scale difference in the object's previous scale position
 */
void scale_change(struct_data *data, int scale);
/**
 * @brief Calculates the new position of an object when it is rotated along the
 * x-coordinate
 *
 * @param data verticles structure
 * @param x_spin difference in the object's previous x position
 */
void x_rotation(struct_data *data, int x_spin);
/**
 * @brief CCalculates the new position of an object when it is rotated along the
 * y-coordinate
 *
 * @param data verticles structure
 * @param y_spin difference in the object's previous y position
 */
void y_rotation(struct_data *data, int y_spin);
/**
 * @brief Calculates the new position of an object when it is rotated along the
 * z-coordinate
 *
 * @param data verticles structure
 * @param z_spin difference in the object's previous z position
 */
void z_rotation(struct_data *data, int z_spin);

#endif /* _3D_VIEWER_H */
