#ifndef QLVIEW_H
#define QLVIEW_H

#ifdef __cplusplus
extern "C" {
#endif
#include "3d_viewer.h"
#ifdef __cplusplus
}
#endif

#define GL_SILENCE_DEPRECATION
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QWheelEvent>

class qlview : public QOpenGLWidget {
 public:
  ~qlview();

  const char *file_name;

  struct_data data;
  struct_data copy_data;
  int x_move = 0;
  int y_move = 0;
  int z_move = 0;
  int x_spin = 0;
  int y_spin = 0;
  int z_spin = 0;
  int scale = 0;
  int if_dashed = 0;  // 0 - solid, 1 - dashed
  int color_edge =
      1;  // 0 - black, 1 - white, 2 - purple, 3 - pink, 4 - blue, 5 - green
  double edge_thickness = 1;

  int display_method = 0;  // 0 - none, 1 - circle, 2 - square
  int vertex_size = 0;
  int color_vertex =
      1;  // 0 - black, 1 - white, 2 - purple, 3 - pink, 4 - blue, 5 - green
  int color_bg =
      0;  // 0 - black, 1 - white, 2 - purple, 3 - pink, 4 - blue, 5 - green
  int projection_type =
      0;  // 0 - parallel (orthographic), 1 - central (perspective)
  qlview(QWidget *parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void open_new_file();
  void mousePressEvent(QMouseEvent *press_event) override;
  QPoint firstPos;
  void mouseMoveEvent(QMouseEvent *move_event) override;
  void wheelEvent(QWheelEvent *wheel) override;
};

#endif  // QLVIEW_H
