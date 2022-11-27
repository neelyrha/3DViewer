#include <check.h>

#include "3d_viewer.h"

#define EPS 1e-7

START_TEST(test_case_1) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;

  int ex_code = first_file_open(file_name, &data);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_int_eq(data.qty_vertex, 9);
  ck_assert_int_eq(data.qty_facet, 2);
  ck_assert_int_eq(data.qty_vertex_in_facet, 8);
}
END_TEST

START_TEST(test_case_2) {
  char *file_name = "../obj_files/tet.obj";
  struct_data data;
  int ex_code = first_file_open(file_name, &data);
  ck_assert_int_eq(ex_code, 1);
}
END_TEST

START_TEST(test_case_3) {
  char *file_name = "../obj_files/tet.obj";
  struct_data data;
  int ex_code = second_file_open(file_name, &data);
  ck_assert_int_eq(ex_code, 1);
}
END_TEST

START_TEST(test_case_4) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  int ex_code = second_file_open(file_name, &data);
  ck_assert_int_eq(ex_code, 0);
  ck_assert_double_eq_tol(data.matrix_vertex[0], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], 1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], 0.25, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], 0.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], 0.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], 1, EPS);
  ck_assert_int_eq(data.matrix_facet[0], 1);
  ck_assert_int_eq(data.matrix_facet[1], 2);
  ck_assert_int_eq(data.matrix_facet[2], 2);
  ck_assert_int_eq(data.matrix_facet[3], 1);
  ck_assert_int_eq(data.matrix_facet[4], 2);
  ck_assert_int_eq(data.matrix_facet[5], 1);
  ck_assert_int_eq(data.matrix_facet[6], 1);
  ck_assert_int_eq(data.matrix_facet[7], 2);
  remove_matrix_data(&data);
}
END_TEST

START_TEST(test_case_5) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  struct_data copy_data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  second_file_open(file_name, &data);

  copy_data_matrix(data, &copy_data);

  ck_assert_int_eq(data.qty_vertex, copy_data.qty_vertex);
  ck_assert_int_eq(data.qty_facet, copy_data.qty_facet);
  ck_assert_int_eq(data.qty_vertex_in_facet, copy_data.qty_vertex_in_facet);
  ck_assert_double_eq_tol(data.max_vertex, copy_data.max_vertex, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[0], copy_data.matrix_vertex[0],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], copy_data.matrix_vertex[1],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], copy_data.matrix_vertex[2],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], copy_data.matrix_vertex[3],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], copy_data.matrix_vertex[4],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], copy_data.matrix_vertex[5],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], copy_data.matrix_vertex[6],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], copy_data.matrix_vertex[7],
                          EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], copy_data.matrix_vertex[8],
                          EPS);

  remove_matrix_data(&data);
  remove_matrix_data(&copy_data);
}
END_TEST

START_TEST(test_case_6) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  second_file_open(file_name, &data);

  scale_change(&data, 100);
  ck_assert_double_eq_tol(data.matrix_vertex[0], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], 2, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], 0.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], 1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], 1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], 2, EPS);

  remove_matrix_data(&data);
}
END_TEST

START_TEST(test_case_7) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  second_file_open(file_name, &data);

  translating(&data, 50, 100, 150);
  ck_assert_double_eq_tol(data.matrix_vertex[0], 1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], 2, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], 3, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], 2, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], 2, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], 3.25, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], 1.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], 2.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], 4, EPS);

  remove_matrix_data(&data);
}
END_TEST

START_TEST(test_case_8) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  second_file_open(file_name, &data);

  x_rotation(&data, 90);
  ck_assert_double_eq_tol(data.matrix_vertex[0], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], 1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], -0.25, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], 0.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], -1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], 0.5, EPS);

  remove_matrix_data(&data);
}
END_TEST

START_TEST(test_case_9) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  second_file_open(file_name, &data);

  y_rotation(&data, 90);

  ck_assert_double_eq_tol(data.matrix_vertex[0], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], -0.25, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], 1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], -1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], 0.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], 0.5, EPS);

  remove_matrix_data(&data);
}
END_TEST

START_TEST(test_case_10) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  second_file_open(file_name, &data);

  z_rotation(&data, 90);
  ck_assert_double_eq_tol(data.matrix_vertex[0], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], 1, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], 0.25, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], -0.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], 0.5, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], 1, EPS);

  remove_matrix_data(&data);
}
END_TEST

START_TEST(test_case_11) {
  char *file_name = "../obj_files/test.obj";
  struct_data data;
  first_file_open(file_name, &data);
  create_matrix_data(&data);
  second_file_open(file_name, &data);

  scale_change(&data, -500);
  ck_assert_double_eq_tol(data.matrix_vertex[0], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[1], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[2], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[3], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[4], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[5], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[6], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[7], 0, EPS);
  ck_assert_double_eq_tol(data.matrix_vertex[8], 0, EPS);

  remove_matrix_data(&data);
}

int main(void) {
  Suite *s1 = suite_create("viewer");
  TCase *viewer = tcase_create("viewer");
  suite_add_tcase(s1, viewer);
  tcase_add_test(viewer, test_case_1);
  tcase_add_test(viewer, test_case_2);
  tcase_add_test(viewer, test_case_3);
  tcase_add_test(viewer, test_case_4);
  tcase_add_test(viewer, test_case_5);
  tcase_add_test(viewer, test_case_6);
  tcase_add_test(viewer, test_case_7);
  tcase_add_test(viewer, test_case_8);
  tcase_add_test(viewer, test_case_9);
  tcase_add_test(viewer, test_case_10);
  tcase_add_test(viewer, test_case_11);

  SRunner *sr = srunner_create(s1);
  int nf;
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
