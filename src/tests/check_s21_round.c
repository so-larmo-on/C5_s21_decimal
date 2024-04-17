#include "check_s21_round.h"

typedef struct testcase {
  s21_decimal a;
  s21_decimal floor;
  s21_decimal round;
  s21_decimal truncate;
  s21_decimal negate;
} testcase;

START_TEST(test) {
  testcase tests[] = {
      {
          // 0
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
      },
      {
          // 1.5
          {{0x0000000f, 0x00000000, 0x00000000, 0x00010000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
          {{0x0000000f, 0x00000000, 0x00000000, 0x80010000}},
      },
      {
          // -1.5
          {{0x0000000f, 0x00000000, 0x00000000, 0x80010000}},
          {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x0000000f, 0x00000000, 0x00000000, 0x00010000}},
      },
      {
          // 0.3
          {{0x00000003, 0x00000000, 0x00000000, 0x00010000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000003, 0x00000000, 0x00000000, 0x80010000}},
      },
      {
          // -0.3
          {{0x00000003, 0x00000000, 0x00000000, 0x80010000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000003, 0x00000000, 0x00000000, 0x00010000}},
      },
      {
          // 0.7
          {{0x00000007, 0x00000000, 0x00000000, 0x00010000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000007, 0x00000000, 0x00000000, 0x80010000}},
      },
      {
          // -0.7
          {{0x00000007, 0x00000000, 0x00000000, 0x80010000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000007, 0x00000000, 0x00000000, 0x00010000}},
      },
      {
          // 1
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
      },
      {
          // -1
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
          {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
      },

  };
  int size = sizeof(tests) / sizeof(testcase);
  for (int i = 0; i < size; i++) {
    testcase test = tests[i];
    s21_decimal floor;
    s21_decimal round;
    s21_decimal truncate;
    s21_decimal negate;
    int floor_res = s21_floor(test.a, &floor);
    int round_res = s21_round(test.a, &round);
    int truncate_res = s21_truncate(test.a, &truncate);
    int negate_res = s21_negate(test.a, &negate);
    ck_assert_int_eq(floor_res, 0);
    ck_assert_int_eq(round_res, 0);
    ck_assert_int_eq(truncate_res, 0);
    ck_assert_int_eq(negate_res, 0);
  }
}
END_TEST

START_TEST(test2) {
  s21_decimal value1;
  s21_decimal value2;
  s21_decimal negate;
  // s21_decimal round_p;
  // s21_decimal round_m;

  s21_decimal_init(&value1);
  s21_decimal_init(&value2);
  s21_decimal_init(&negate);
  // s21_decimal_init(&round_p);
  // s21_decimal_init(&round_m);

  s21_from_float_to_decimal(1.5, &value1);
  s21_from_float_to_decimal(-1.5, &value2);

  s21_negate(value1, &negate);

  ck_assert_int_eq(negate.bits[3], -2147418112);

  // s21_round(value1, &round_p);
  // s21_round(value2, &round_m);

  int status = s21_floor(value1, NULL);
  ck_assert_int_eq(status, 1);

  status = s21_truncate(value1, NULL);
  ck_assert_int_eq(status, 1);

  status = s21_round(value1, NULL);
  ck_assert_int_eq(status, 1);

  status = s21_negate(value1, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

Suite *

test_round_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Round");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test);
  tcase_add_test(tc_core, test2);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_round() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = test_round_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}
