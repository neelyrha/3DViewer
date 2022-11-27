#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "gif.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  my_glview = new qlview;

  settings = new QSettings("21school", "3DViewer", NULL);

  loading_saved_setting();

  //  sliders setting
  ui->x_move_box->setText("0");
  ui->x_move_slider->setRange(-100, 100);
  ui->y_move_box->setText("0");
  ui->y_move_slider->setRange(-100, 100);
  ui->z_move_box->setText("0");
  ui->z_move_slider->setRange(-100, 100);
  ui->x_rotation_box->setText("0");
  ui->x_rotation_slider->setRange(0, 360);
  ui->y_rotation_box->setText("0");
  ui->y_rotation_slider->setRange(0, 360);
  ui->z_rotation_box->setText("0");
  ui->z_rotation_slider->setRange(0, 360);
  ui->scale_box->setText("0");
  ui->scale_slider->setRange(-100, 300);
  ui->thickness_edge_slider->setRange(1, 30);
  ui->size_vertices_slider->setRange(1, 30);
}

MainWindow::~MainWindow() {
  save_setting();
  delete ui;
}

//  Press on movement buttons and sliders (translating, rotation, scale)

void MainWindow::on_x_move_slider_sliderMoved(int position) {
  ui->x_move_box->setText(QString::number(position));
}
void MainWindow::on_x_move_box_textChanged(const QString &arg1) {
  int x_move = ui->x_move_box->text().toInt();
  ui->x_move_slider->setValue(x_move);
  ui->openGLWidget->x_move = x_move;
  ui->openGLWidget->update();
}

void MainWindow::on_y_move_slider_sliderMoved(int position) {
  ui->y_move_box->setText(QString::number(position));
}
void MainWindow::on_y_move_box_textChanged(const QString &arg1) {
  int y_move = ui->y_move_box->text().toInt();
  ui->y_move_slider->setValue(y_move);
  ui->openGLWidget->y_move = y_move;
  ui->openGLWidget->update();
}

void MainWindow::on_z_move_slider_sliderMoved(int position) {
  ui->z_move_box->setText(QString::number(position));
}
void MainWindow::on_z_move_box_textChanged(const QString &arg1) {
  int z_move = ui->z_move_box->text().toInt();
  ui->z_move_slider->setValue(z_move);
  ui->openGLWidget->z_move = z_move;
  ui->openGLWidget->update();
}

void MainWindow::on_x_rotation_slider_sliderMoved(int position) {
  ui->x_rotation_box->setText(QString::number(position));
}
void MainWindow::on_x_rotation_box_textChanged() {
  int x_spin = ui->x_rotation_box->text().toInt();
  ui->x_rotation_slider->setValue(x_spin);
  ui->openGLWidget->x_spin = x_spin;
  ui->openGLWidget->update();
}

void MainWindow::on_y_rotation_slider_sliderMoved(int position) {
  ui->y_rotation_box->setText(QString::number(position));
}
void MainWindow::on_y_rotation_box_textChanged(const QString &arg1) {
  int y_spin = ui->y_rotation_box->text().toInt();
  ui->y_rotation_slider->setValue(y_spin);
  ui->openGLWidget->y_spin = y_spin;
  ui->openGLWidget->update();
}

void MainWindow::on_z_rotation_slider_sliderMoved(int position) {
  ui->z_rotation_box->setText(QString::number(position));
}
void MainWindow::on_z_rotation_box_textChanged(const QString &arg1) {
  int z_spin = ui->z_rotation_box->text().toInt();
  ui->z_rotation_slider->setValue(z_spin);
  ui->openGLWidget->z_spin = z_spin;
  ui->openGLWidget->update();
}

void MainWindow::on_scale_slider_sliderMoved(int position) {
  ui->scale_box->setText(QString::number(position));
}
void MainWindow::on_scale_box_textChanged(const QString &arg1) {
  int scale = ui->scale_box->text().toInt();
  ui->scale_slider->setValue(scale);
  ui->openGLWidget->scale = scale;
  ui->openGLWidget->update();
}

//  Press on setting buttons (appearance of edges, vertixes, background and
//  projection)

void MainWindow::on_dashed_button_clicked() {
  ui->openGLWidget->if_dashed = 1;
  ui->openGLWidget->update();
}
void MainWindow::on_solid_button_clicked() {
  ui->openGLWidget->if_dashed = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_color_edge_combo_textActivated(const QString &arg1) {
  if (ui->color_edge_combo->currentText() == "black") {
    ui->openGLWidget->color_edge = 0;
  }
  if (ui->color_edge_combo->currentText() == "white") {
    ui->openGLWidget->color_edge = 1;
  }
  if (ui->color_edge_combo->currentText() == "purple") {
    ui->openGLWidget->color_edge = 2;
  }
  if (ui->color_edge_combo->currentText() == "pink") {
    ui->openGLWidget->color_edge = 3;
  }
  if (ui->color_edge_combo->currentText() == "blue") {
    ui->openGLWidget->color_edge = 4;
  }
  if (ui->color_edge_combo->currentText() == "green") {
    ui->openGLWidget->color_edge = 5;
  }
  ui->openGLWidget->update();
}

void MainWindow::on_thickness_edge_slider_sliderMoved(int position) {
  ui->openGLWidget->edge_thickness = position;
  ui->openGLWidget->update();
}

void MainWindow::on_non_button_clicked() {
  ui->openGLWidget->display_method = 0;
  ui->size_vertices_slider->setSliderPosition(1);
  emit ui->size_vertices_slider->sliderMoved(1);
  update();
}
void MainWindow::on_circle_button_clicked() {
  ui->openGLWidget->display_method = 1;
  emit ui->size_vertices_slider->sliderMoved(1);
  ui->size_vertices_slider->setSliderPosition(1);
  update();
}
void MainWindow::on_square_button_clicked() {
  ui->openGLWidget->display_method = 2;
  ui->size_vertices_slider->setSliderPosition(1);
  emit ui->size_vertices_slider->sliderMoved(1);
  update();
}

void MainWindow::on_color_vertices_combo_textActivated(const QString &arg1) {
  if (ui->color_vertices_combo->currentText() == "black") {
    ui->openGLWidget->color_vertex = 0;
  }
  if (ui->color_vertices_combo->currentText() == "white") {
    ui->openGLWidget->color_vertex = 1;
  }
  if (ui->color_vertices_combo->currentText() == "purple") {
    ui->openGLWidget->color_vertex = 2;
  }
  if (ui->color_vertices_combo->currentText() == "pink") {
    ui->openGLWidget->color_vertex = 3;
  }
  if (ui->color_vertices_combo->currentText() == "blue") {
    ui->openGLWidget->color_vertex = 4;
  }
  if (ui->color_vertices_combo->currentText() == "green") {
    ui->openGLWidget->color_vertex = 5;
  }
  ui->openGLWidget->update();
}

void MainWindow::on_size_vertices_slider_sliderMoved(int position) {
  ui->openGLWidget->vertex_size = position;
  ui->openGLWidget->update();
}

void MainWindow::on_background_combo_textActivated(const QString &arg1) {
  if (ui->background_combo->currentText() == "black") {
    ui->openGLWidget->color_bg = 0;
  }
  if (ui->background_combo->currentText() == "white") {
    ui->openGLWidget->color_bg = 1;
  }
  if (ui->background_combo->currentText() == "purple") {
    ui->openGLWidget->color_bg = 2;
  }
  if (ui->background_combo->currentText() == "pink") {
    ui->openGLWidget->color_bg = 3;
  }
  if (ui->background_combo->currentText() == "blue") {
    ui->openGLWidget->color_bg = 4;
  }
  if (ui->background_combo->currentText() == "green") {
    ui->openGLWidget->color_bg = 5;
  }
  ui->openGLWidget->update();
}

void MainWindow::on_parallel_button_clicked() {
  ui->openGLWidget->projection_type = 0;
  update();
}
void MainWindow::on_central_button_clicked() {
  ui->openGLWidget->projection_type = 1;
  update();
}

//  Press on Open file button

void MainWindow::on_open_file_clicked() {
  const QString current_dir = QDir::currentPath();
  QString full_file_name;
  full_file_name = QFileDialog::getOpenFileName(this, tr("Open OBJ file"),
                                                current_dir, tr("*.obj"));
  if (full_file_name.isNull()) {
    ui->file_name->setText("Please open another file");
  } else {
    ui->file_name->setText(full_file_name);

    ui->openGLWidget->file_name = nullptr;
    QByteArray ba = full_file_name.toLocal8Bit();
    ui->openGLWidget->file_name = ba.data();

    ui->openGLWidget->open_new_file();
    ui->openGLWidget->update();

    int qty_vertexes = ui->openGLWidget->data.qty_vertex;
    qty_vertexes = qty_vertexes / 3 - 1;
    ui->qty_vertice->setText(QString::number(qty_vertexes, 'f', 0));

    int qty_facets = ui->openGLWidget->data.qty_vertex_in_facet;
    qty_facets = qty_facets / 2;
    ui->qty_facet->setText(QString::number(qty_facets, 'f', 0));
  }
}

void MainWindow::save_setting() {
  settings->setValue("edges_type", ui->openGLWidget->if_dashed);
  settings->setValue("edges_color", ui->openGLWidget->color_edge);
  settings->setValue("edges_thickness", ui->openGLWidget->edge_thickness);
  settings->setValue("vertix_display_method", ui->openGLWidget->display_method);
  settings->setValue("vertex_color", ui->openGLWidget->color_vertex);
  settings->setValue("vertex_size", ui->openGLWidget->vertex_size);
  settings->setValue("background_color", ui->openGLWidget->color_bg);
  settings->setValue("type_projection", ui->openGLWidget->projection_type);
}

void MainWindow::loading_saved_setting() {
  if (settings != nullptr) {
    ui->openGLWidget->if_dashed = settings->value("edges_type").toInt();
    ui->openGLWidget->color_edge = settings->value("edges_color").toInt();
    ui->openGLWidget->edge_thickness =
        settings->value("edges_thickness").toDouble();
    ui->openGLWidget->display_method =
        settings->value("vertix_display_method").toInt();
    ui->openGLWidget->color_vertex = settings->value("vertex_color").toInt();
    ui->openGLWidget->vertex_size = settings->value("vertex_size").toInt();
    ui->openGLWidget->color_bg = settings->value("background_color").toInt();
    ui->openGLWidget->projection_type =
        settings->value("type_projection").toInt();
  } else {
    ui->parallel_button->click();
    ui->solid_button->click();
    ui->non_button->click();
  }
}

void MainWindow::on_push_default_setting_clicked() {
  ui->x_move_box->setText("0");
  ui->x_move_slider->setValue(0);
  ui->openGLWidget->x_move = 0;
  ui->y_move_box->setText("0");
  ui->y_move_slider->setValue(0);
  ui->openGLWidget->y_move = 0;
  ui->z_move_box->setText("0");
  ui->z_move_slider->setValue(0);
  ui->openGLWidget->z_move = 0;
  ui->x_rotation_box->setText("0");
  ui->x_rotation_slider->setValue(0);
  ui->openGLWidget->x_spin = 0;
  ui->y_rotation_box->setText("0");
  ui->y_rotation_slider->setValue(0);
  ui->openGLWidget->y_spin = 0;
  ui->z_rotation_box->setText("0");
  ui->z_rotation_slider->setValue(0);
  ui->openGLWidget->z_spin = 0;
  ui->scale_box->setText("0");
  ui->scale_slider->setValue(0);
  ui->openGLWidget->scale = 0;
  ui->solid_button->click();
  ui->non_button->click();
  ui->parallel_button->click();
  ui->thickness_edge_slider->setValue(0);
  ui->openGLWidget->edge_thickness = 1;
  ui->size_vertices_slider->setValue(0);
  ui->openGLWidget->vertex_size = 1;
  ui->openGLWidget->color_edge = 1;
  ui->color_edge_combo->setCurrentIndex(0);
  ui->openGLWidget->color_vertex = 1;
  ui->color_vertices_combo->setCurrentIndex(0);
  ui->openGLWidget->color_bg = 0;
  ui->background_combo->setCurrentIndex(0);
  ui->openGLWidget->update();
}

void MainWindow::on_save_jpeg_clicked() {
  QString screenshot_dir;
  screenshot_dir = QFileDialog::getSaveFileName(this, tr("Save screenshot"), "",
                                                tr("jpg (*.jpg);;bmp (*.bmp)"));
  ui->openGLWidget->grab().save(screenshot_dir);
}

void MainWindow::save_one_pic() {
  if (start_time == current_time && pic_qty < 51) {
    ui->openGLWidget->grab()
        .scaled(640, 480, Qt::IgnoreAspectRatio)
        .save(gif_dir + "/" + QString::number(pic_qty) + ".bmp");
    pic_qty++;
    current_time += 100;
  }
  if (pic_qty > 50) {
    timer->stop();
    save_gif();
    pic_qty = 1;
  }
  start_time += 100;
}

void MainWindow::on_save_gif_clicked() {
  // создать папку, в которую будут складываться картинки
  gif_dir = QFileDialog::getExistingDirectory(
      this, tr("Please create new folder"), QDir::currentPath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (gif_dir != "") {
    //  запустить таймер
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(save_one_pic()));
    timer->start(100);
  }
}

void MainWindow::save_gif() {
  // выбрать папку и имя для сохранения гифки:
  QString gif_name =
      QFileDialog::getSaveFileName(this, tr("Save gif"), "", tr("gif (*.gif)"));
  QByteArray ga = gif_name.toLocal8Bit();

  GifWriter writer = {};
  int err = 0;

  if (GifBegin(&writer, ga.data(), 640, 480, 10, 8, false)) {
    for (int i = 1; i <= 50; i++) {
      if (err == 1) {
        break;
      }
      QImage img(gif_dir + "/" + QString::number(i) + ".bmp");
      if (!img.isNull()) {
        if (GifWriteFrame(&writer,
                          img.convertToFormat(QImage::Format_Indexed8)
                              .convertToFormat(QImage::Format_RGBA8888)
                              .constBits(),
                          640, 480, 10, 8, false)) {
        } else {
          QMessageBox::critical(0, "Error", "Gif file can not be create!d");
          err = 1;
        }
      } else {
        QMessageBox::critical(0, "Error", "Gif file can not be created!");
        err = 1;
      }
    }
    if (err == 0) {
      GifEnd(&writer);
    }
  } else {
    err = 1;
    qDebug() << 'c';
    QMessageBox::critical(0, "Error", "Gif file can not be created!");
  }
  if (err == 1) {
    if (QFile::exists(gif_name)) {
      QFile::remove(gif_name);
    }
  }
}
