#include "3d_viewer.h"

void translating(struct_data *data, int x_move, int y_move, int z_move) {
  double x_move_in_fn = x_move / 50.;
  double y_move_in_fn = y_move / 50.;
  double z_move_in_fn = z_move / 50.;
  if (x_move != 0) {
    for (unsigned int i = 0; i < data->qty_vertex; i += 3) {
      data->matrix_vertex[i] = data->matrix_vertex[i] + x_move_in_fn;
    }
  }
  if (y_move != 0) {
    for (unsigned int i = 1; i < data->qty_vertex; i += 3) {
      data->matrix_vertex[i] = data->matrix_vertex[i] + y_move_in_fn;
    }
  }
  if (z_move != 0) {
    for (unsigned int i = 2; i < data->qty_vertex; i += 3) {
      data->matrix_vertex[i] = data->matrix_vertex[i] + z_move_in_fn;
    }
  }
}

void scale_change(struct_data *data, int scale) {
  if (scale != 0) {
    if (scale < -100) {
      scale = -100;
    }
    double scale_in_fn = 1 + scale / 100.;
    for (unsigned int i = 0; i < data->qty_vertex; i++) {
      data->matrix_vertex[i] = data->matrix_vertex[i] * scale_in_fn;
    }
  }
}

void x_rotation(struct_data *data, int x_spin) {
  if (x_spin != 0) {
    double angle = x_spin * (M_PI / 180);
    for (unsigned int i = 0; i < data->qty_vertex; i += 3) {
      double y = data->matrix_vertex[i + 1];
      double z = data->matrix_vertex[i + 2];
      data->matrix_vertex[i + 1] = cos(angle) * y - sin(angle) * z;
      data->matrix_vertex[i + 2] = sin(angle) * y + cos(angle) * z;
    }
  }
}

void y_rotation(struct_data *data, int y_spin) {
  if (y_spin != 0) {
    double angle = y_spin * (M_PI / 180);
    for (unsigned int i = 0; i < data->qty_vertex; i += 3) {
      double x = data->matrix_vertex[i];
      double z = data->matrix_vertex[i + 2];
      data->matrix_vertex[i] = cos(angle) * x - sin(angle) * z;
      data->matrix_vertex[i + 2] = sin(angle) * x + cos(angle) * z;
    }
  }
}

void z_rotation(struct_data *data, int z_spin) {
  if (z_spin != 0) {
    double angle = z_spin * (M_PI / 180);
    for (unsigned int i = 0; i < data->qty_vertex; i += 3) {
      double x = data->matrix_vertex[i];
      double y = data->matrix_vertex[i + 1];
      data->matrix_vertex[i] = cos(angle) * x - sin(angle) * y;
      data->matrix_vertex[i + 1] = sin(angle) * x + cos(angle) * y;
    }
  }
}
