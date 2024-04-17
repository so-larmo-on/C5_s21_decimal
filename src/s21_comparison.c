#include "s21_decimal.h"

int s21_is_less(s21_decimal decimal1, s21_decimal decimal2) {
  int res = 0;
  s21_big_decimal value_big_1 = bigConvert(decimal1);
  s21_big_decimal value_big_2 = bigConvert(decimal2);
  int scale_1 = getScale(decimal1);
  int scale_2 = getScale(decimal2);
  if ((scale_1 - scale_2) <= 0) {
    normalization(&value_big_1, -1 * (scale_1 - scale_2));
  } else {
    normalization(&value_big_2, (scale_1 - scale_2));
  }
  int sign1 = getSign(decimal1);
  int sign2 = getSign(decimal2);
  if ((sign1 && sign2) || (!sign1 && !sign2)) {
    res = is_mantis_less(value_big_1, value_big_2);
  } else {
    res = (sign1) ? 1 : 0;
  }
  return res;
}

int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2) {
  int res = 1;
  for (int i = 0; i < 3; i++) {
    if (decimal1.bits[i] != decimal2.bits[i]) res = 0;
  }
  return res;
}

int s21_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2) {
  return (s21_is_less(decimal1, decimal2) || s21_is_equal(decimal1, decimal2));
}

int s21_is_greater(s21_decimal decimal1, s21_decimal decimal2) {
  int res = 0;
  s21_big_decimal value_big_1 = bigConvert(decimal1);
  s21_big_decimal value_big_2 = bigConvert(decimal2);
  int scale_1 = getScale(decimal1);
  int scale_2 = getScale(decimal2);
  if ((scale_1 - scale_2) <= 0) {
    normalization(&value_big_1, -1 * (scale_1 - scale_2));
  } else {
    normalization(&value_big_2, (scale_1 - scale_2));
  }
  int sign1 = getSign(decimal1);
  int sign2 = getSign(decimal2);
  if ((sign1 && sign2) || (!sign1 && !sign2)) {
    res = is_mantis_less(value_big_2, value_big_1);
  } else {
    res = (sign1) ? 0 : 1;
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2) {
  return (s21_is_greater(decimal1, decimal2) ||
          s21_is_equal(decimal1, decimal2));
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  bool status = false;
  if (s21_is_equal(value_1, value_2) != true) {
    status = true;
  }
  return status;
}