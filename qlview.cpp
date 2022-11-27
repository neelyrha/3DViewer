#include "qlview.h"

#include <QDebug>

qlview::qlview(QWidget *parent) : QOpenGLWidget(parent) { open_new_file(); }

qlview::~qlview() {
  remove_matrix_data(&data);
  remove_matrix_data(&copy_data);
}

void qlview::open_new_file() {
  int ex_code = first_file_open(file_name, &data);
  create_matrix_data(&data);
  if (ex_code == 0) {
    ex_code = second_file_open(file_name, &data);
  }
}

void qlview::initializeGL() { glEnable(GL_DEPTH_TEST); }

void qlview::resizeGL(int w, int h) {}

void qlview::paintGL() {
  copy_data_matrix(data, &copy_data);

  glViewport(0, 0, 1800, 1800);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type == 1) {
    glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5,
              10.0);  //(левая, правая, верхняя, нижняя, ближняя, дальняя)
    translating(&copy_data, 0, 0, -100);
  } else if (projection_type == 0) {
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0,
            1.0);  //(левая, правая, верхняя, нижняя, передняя, задняя)
  }

  translating(&copy_data, x_move, y_move, z_move);
  scale_change(&copy_data, scale);
  x_rotation(&copy_data, x_spin);
  y_rotation(&copy_data, y_spin);
  z_rotation(&copy_data, z_spin);

  switch (color_bg) {
    case 0:  // black bg
      glClearColor(0.0, 0.0, 0.0, 1.0);
      break;
    case 1:  // white bg
      glClearColor(1.0, 1.0, 1.0, 1.0);
      break;
    case 2:  // purple bg
      glClearColor(0.153, 0.051, 0.255, 1.0);
      break;
    case 3:  // pink bg
      glClearColor(1.0, 0.86, 0.898, 1.0);
      break;
    case 4:  // blue bg
      glClearColor(0.0, 0.298, 0.6, 1.0);
      break;
    case 5:  // green bg
      glClearColor(0.0, 0.4, 0.4, 1.0);
      break;
  }

  switch (color_vertex) {
    case 0:  // black
      glColor3f(0.0, 0.0, 0.0);
      break;
    case 1:  // white
      glColor3f(1.0, 1.0, 1.0);
      break;
    case 2:  // purple
      glColor3f(0.8, 0.6, 1.0);
      break;
    case 3:  // pink
      glColor3f(1.0, 0.86, 0.898);
      break;
    case 4:  // blue
      glColor3f(0.0, 0.298, 0.6);
      break;
    case 5:  // green
      glColor3f(0.0, 0.4, 0.4);
      break;
  }

  if (display_method != 0) {
    glPointSize(vertex_size);
  } else {
    glPointSize(1);
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (display_method == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, copy_data.matrix_vertex);
  glDrawArrays(GL_POINTS, 0, data.qty_vertex / 3);

  // способ отображения грани (if_dashed) - 0 непрерывная, 1 - пунктир
  if (if_dashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(edge_thickness);

  switch (color_edge) {
    case 0:  // black
      glColor3f(0.0, 0.0, 0.0);
      break;
    case 1:  // white
      glColor3f(1.0, 1.0, 1.0);
      break;
    case 2:  // purple
      glColor3f(0.8, 0.6, 1.0);
      break;
    case 3:  // pink
      glColor3f(1.0, 0.86, 0.898);
      break;
    case 4:  // blue
      glColor3f(0.0, 0.298, 0.6);
      break;
    case 5:  // green
      glColor3f(0.0, 0.4, 0.4);
      break;
  }

  glDrawElements(GL_LINES, data.qty_vertex_in_facet, GL_UNSIGNED_INT,
                 data.matrix_facet);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void qlview::mousePressEvent(QMouseEvent *press_event) {
  firstPos = press_event->pos();
}

void qlview::mouseMoveEvent(QMouseEvent *move_event) {
  if (move_event->buttons() & Qt::LeftButton) {
    int xMoveMouse = (firstPos.x() - move_event->pos().x());
    int yMoveMouse = (firstPos.y() - move_event->pos().y());
    x_move = -xMoveMouse / 4.5;
    y_move = yMoveMouse / 4.5;
    update();
  }
  if (move_event->buttons() & Qt::RightButton) {
    int yRotationMouse = (firstPos.x() - move_event->pos().x());
    int xRotationMouse = (firstPos.y() - move_event->pos().y());
    x_spin = xRotationMouse / 2.5;
    y_spin = -yRotationMouse / 2.5;
    update();
  }
}

void qlview::wheelEvent(QWheelEvent *wheel) {
  if (wheel->angleDelta().y() > 0) {
    scale = (scale + 10);
  } else {
    scale = (scale - 10);
  }
  update();
}
