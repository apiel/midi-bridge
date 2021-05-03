#ifndef IO_UTIL_H_
#define IO_UTIL_H_

#include <Arduino.h>

int mod(int n, int m) { return ((n % m) + m) % m; }

#endif