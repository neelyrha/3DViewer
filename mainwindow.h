#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef __cplusplus
extern "C" {
#endif
#include "3d_viewer.h"
#ifdef __cplusplus
}
#endif

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QSettings>
#include <QTimer>

#include "qlview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  qlview *my_glview;
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QSettings *settings;
  void save_setting();
  void loading_saved_setting();

 private slots:

 private:
  Ui::MainWindow *ui;

  // For GIF save: 10fps - 10 frame for sec or 1 frame in 100 msec
  int start_time = 0;
  int current_time = 100;
  int pic_qty = 1;
  QString gif_dir;
  QTimer *timer;
  void save_gif();

 private slots:

  void on_x_move_slider_sliderMoved(int position);
  void on_x_move_box_textChanged(const QString &arg1);
  void on_y_move_slider_sliderMoved(int position);
  void on_y_move_box_textChanged(const QString &arg1);
  void on_z_move_slider_sliderMoved(int position);
  void on_z_move_box_textChanged(const QString &arg1);
  void on_x_rotation_slider_sliderMoved(int position);
  void on_x_rotation_box_textChanged();
  void on_y_rotation_slider_sliderMoved(int position);
  void on_y_rotation_box_textChanged(const QString &arg1);
  void on_z_rotation_slider_sliderMoved(int position);
  void on_z_rotation_box_textChanged(const QString &arg1);
  void on_scale_box_textChanged(const QString &arg1);
  void on_scale_slider_sliderMoved(int position);
  void on_dashed_button_clicked();
  void on_solid_button_clicked();
  void on_thickness_edge_slider_sliderMoved(int position);
  void on_background_combo_textActivated(const QString &arg1);
  void on_color_edge_combo_textActivated(const QString &arg1);
  void on_size_vertices_slider_sliderMoved(int position);
  void on_color_vertices_combo_textActivated(const QString &arg1);
  void on_circle_button_clicked();
  void on_square_button_clicked();
  void on_non_button_clicked();
  void on_parallel_button_clicked();
  void on_central_button_clicked();
  void on_open_file_clicked();
  void on_push_default_setting_clicked();
  void on_save_jpeg_clicked();
  void on_save_gif_clicked();
  void save_one_pic();
};
#endif  // MAINWINDOW_H
