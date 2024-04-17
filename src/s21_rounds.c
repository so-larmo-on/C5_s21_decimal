#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  bool status = OK;
  if (result == NULL) {
    status = ERR_OVERFLOW;
  } else {
    float tmp = 0;
    s21_from_decimal_to_float(value, &tmp);
    tmp = floorf(tmp);
    s21_from_float_to_decimal(tmp, result);
  }

  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_big_decimal val1 = bigConvert(value);
  s21_big_decimal val2 = bigInit();
  s21_big_decimal res_big = bigInit();
  val2.bits[0] = 10u;
  int res = 0;
  if (result) {
    int scale_init = getScale(value);
    int scale = scale_init;
    int sign = getSign(value);
    for (int i = 0; i < scale; i++) {
      if (val1.bits[0] < 10) {
        val1.bits[0] = 0;
      } else {
        div_without_left(val1, val2, &res_big);
        val1 = res_big;
      }
    }
    for (int i = 0; i < 3; i++) {
      result->bits[i] = val1.bits[i];
    }
    setSign(result, sign);
  } else {
    res = 1;
  }

  return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  bool status = OK;
  if (result == NULL) {
    status = ERR_OVERFLOW;
  } else {
    float tmp = 0;
    s21_from_decimal_to_float(value, &tmp);
    tmp = roundf(tmp);
    s21_from_float_to_decimal(tmp, result);
  }

  return status;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  bool status = OK;
  if (result == NULL) {
    status = ERR_OVERFLOW;
  } else {
    *result = value;
    setSign(result, 1);
  }

  return status;
}