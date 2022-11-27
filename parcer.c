#include "3d_viewer.h"

int first_file_open(const char *file_name, struct_data *data) {
  int ex_code = 0;
  data->qty_facet = 0;
  data->qty_vertex = 3;
  data->qty_vertex_in_facet = 0;
  data->max_vertex = 0;
  FILE *file_obj;
  file_obj = fopen(file_name, "r");
  if (file_obj != NULL) {
    ssize_t ex_getline = 0;
    size_t n = 0;
    char *str = NULL;
    while ((ex_getline = getline(&str, &n, file_obj)) != -1) {
      if (str[0] == 'v' && str[1] == ' ') {
        data->qty_vertex += 3;
      }
      if (str[0] == 'f') {
        data->qty_facet++;
        data->qty_vertex_in_facet++;
        for (int i = 2; str[i]; i++) {
          if (str[i] == ' ') {
            data->qty_vertex_in_facet++;
          }
        }
      }
    }
    data->qty_vertex_in_facet *= 2;
    free(str);
    fclose(file_obj);
  } else {
    ex_code = 1;
  }
  return ex_code;
}

int second_file_open(const char *file_name, struct_data *data) {
  int ex_code = 0;
  FILE *file_obj;
  file_obj = fopen(file_name, "r");
  if (file_obj != NULL) {
    ssize_t ex_getline = 0;
    size_t n = 0;
    char *str = NULL;
    unsigned int qty_v = 3;
    unsigned int qty_f = 0;
    while ((ex_getline = getline(&str, &n, file_obj)) != -1) {
      if (str[0] == 'v' && str[1] == ' ') {
        char *startstr = &str[2];
        char *endstr;
        for (int i = 0; i < 3; i++) {
          data->matrix_vertex[qty_v] = strtod(startstr, &endstr);
          data->max_vertex =
              max(fabs(data->matrix_vertex[qty_v]), data->max_vertex);
          ++qty_v;
          startstr = endstr;
        }
      }
      if (str[0] == 'f') {
        unsigned int fist_vertex = 0;
        for (int i = 0; str[i]; i++) {
          if (str[i] == ' ') {
            char *startstr = &str[i];
            data->matrix_facet[qty_f] = (unsigned int)strtod(startstr, NULL);
            if (fist_vertex == 0) {
              fist_vertex = data->matrix_facet[qty_f];
            } else {
              qty_f++;
              data->matrix_facet[qty_f] = data->matrix_facet[qty_f - 1];
            }
            qty_f++;
          }
        }
        data->matrix_facet[qty_f] = fist_vertex;
        qty_f++;
      }
    }
    ex_code = vertex_normalize(data);
    free(str);
    fclose(file_obj);
  } else {
    ex_code = 1;
  }
  return ex_code;
}

int vertex_normalize(struct_data *data) {
  int ex_code = 0;
  if (data->max_vertex == 0) {
    ex_code = 1;
  } else {
    for (unsigned int i = 0; i < data->qty_vertex; i++) {
      data->matrix_vertex[i] = data->matrix_vertex[i] / data->max_vertex;
    }
  }
  return ex_code;
}

double max(double num1, double num2) { return (num1 > num2) ? num1 : num2; }

int create_matrix_data(struct_data *data) {
  int ex_code = 0;
  data->matrix_vertex = calloc(data->qty_vertex, sizeof(double));
  data->matrix_facet = calloc(data->qty_vertex_in_facet, sizeof(unsigned int));
  if (data->matrix_vertex == NULL || data->matrix_facet == NULL) {
    ex_code = 1;
  }
  return ex_code;
}

void remove_matrix_data(struct_data *data) {
  free(data->matrix_vertex);
  if (data->matrix_facet != NULL) {
    free(data->matrix_facet);
  }
}

void copy_data_matrix(struct_data input, struct_data *output) {
  output->qty_vertex = input.qty_vertex;
  output->qty_facet = input.qty_facet;
  output->qty_vertex_in_facet = input.qty_vertex_in_facet;
  output->max_vertex = input.max_vertex;
  create_matrix_data(output);
  for (unsigned int i = 0; i < input.qty_vertex; i++) {
    output->matrix_vertex[i] = input.matrix_vertex[i];
  }
}
