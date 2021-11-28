#include <stdint.h>

#include <stdio.h>

#include <limits.h>

#include <stdlib.h>

#define CHAR_FIRST_POS 0

#define TRUE 1
#define FALSE 0

#define NEGATIVE 1
#define POSITIVE 0

#define EXP_0 1
#define EXP_1 10

//The function get digit from number from end position of the exponent.
uint8_t GetDigit(int64_t x, uint64_t exp);

//The functon inverts numbers in DEC value inside the exponent.
int64_t Invert(int64_t x, uint64_t exp);

int main() {
  //output before point value  before point
  int64_t before_point_value = 0;
  //output after point value  after point
  int64_t after_point_value = 0;

  //current character
  char buffer;

  //curren exponent
  uint64_t point = EXP_0;

  //sign of the input value
  uint8_t sign = POSITIVE;
  uint8_t point_found = FALSE;
  uint8_t first_zero = TRUE;
  uint8_t zero_count = 0;

  while ((buffer = getchar()) != EOF && buffer != '\n' && buffer != '\0') {
    switch (buffer) {
    case '-':
      if (point == EXP_0) {
        sign = NEGATIVE;
      } else {
        printf("Input error. Sign found in the value.\n");
        exit(-1);
      }
      break;
    case '.':
      if (!point_found) {
        point_found = TRUE;
        before_point_value = Invert(before_point_value, point / EXP_1);
        point = 1;
      } else {
        printf("Input error. Found second point.\n");
        exit(-1);
      }
      break;
    case '0':
      if (point_found && first_zero) {
        zero_count++;
      }
      point *= EXP_1;
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      if (point_found && first_zero) {
        first_zero = FALSE;
      }
      if (point_found) {
        after_point_value += (buffer - '0') * point;
        point *= EXP_1;
      } else {
        before_point_value += (buffer - '0') * point;
        point *= EXP_1;
      }
      break;
    case ' ':
      break;
    default:
      printf("Input error. Incorrect input.\n");
      exit(-1);
      break;
    }
    if (point % EXP_1 && point != 1) {
      printf("Input error: Input value is hight.\n");
      exit(-1);
    }
  }

  if (!point_found) {

    printf("Input error: Point not found.\n");
    exit(-1);
  }

  after_point_value = Invert(after_point_value, point / EXP_1);

  if (sign == NEGATIVE) {
    before_point_value *= -1;
  }

  printf("%li | ", before_point_value);

  if (after_point_value) {
    for (uint8_t z = 0; z < zero_count; z++) {
      printf("0");
    }
  }
  printf("%li\n", after_point_value);

  exit(0);
}

int64_t Invert(int64_t x, uint64_t exp) {
  //return value
  int64_t r_x = 0;
  uint64_t p = EXP_0;

  for (uint64_t e = exp; e > 0; e /= EXP_1) {
    r_x += GetDigit(x, e) * p;
    p *= EXP_1;
  }

  return r_x;
}

uint8_t GetDigit(int64_t x, uint64_t exp) {
  if (x < 0) {
    x *= -1;
  }
  if (exp == 0) {
    return 0;
  }
  return (x / exp) % EXP_1;
}
