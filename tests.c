/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

int test_minusOne(void) {
  return -1;
}
int test_isTmax(int x) {
    return x == 0x7FFFFFFF;
}
int test_distinctNegation(int x) {
    return x != -x;
}
int test_isGreater(int x, int y)
{
  return x > y;
}
int test_bitOr(int x, int y)
{
  return x|y;
}
int test_bitMatch(int x, int y)
{
    int i;
    int result = 0;
    for (i = 0; i < 32; i++) {
 int mask = 1 << i;
 int bit = (x & mask) == (y & mask);
 result |= bit << i;
    }
    return result;
}



int test_anyOddBit(int x) {
    int i;
    for (i = 1; i < 32; i+=2)
        if (x & (1<<i))
      return 1;
    return 0;
}
int test_getByte(int x, int n)
{
    unsigned char byte;
    switch(n) {
    case 0:
      byte = x;
      break;
    case 1:
      byte = x >> 8;
      break;
    case 2:
      byte = x >> 16;
      break;
    default:
      byte = x >> 24;
      break;
    }
    return (int) (unsigned) byte;
}
int test_conditional(int x, int y, int z)
{
  return x?y:z;
}
int test_isPallindrome(int x) {
    int result = 1;
    int i;
    int mask = 0xFFFF;
    int xlo = x & mask;
    int xhi = (x >> 16) & mask;
    for (i = 0; i < 16; i++) {
 int flipi = 15-i;
 int bhigh = (xhi >> i) & 0x1;
 int blow = (xlo>> flipi) & 0x1;
 result = result && (bhigh == blow);
    }
    return result;
}
int test_floatIsEqual(unsigned uf, unsigned ug) {
    float f = u2f(uf);
    float g = u2f(ug);
    return f == g;
}
unsigned test_floatScale1d2(unsigned uf) {
  float f = u2f(uf);
  float hf = 0.5*f;
  if (isnan(f))
    return uf;
  else
    return f2u(hf);
}
unsigned test_floatPower2(int x) {
  float result = 1.0;
  float p2 = 2.0;
  int recip = (x < 0);
  /* treat tmin specially */
  if ((unsigned)x == 0x80000000) {
      return 0;
  }
  if (recip) {
    x = -x;
    p2 = 0.5;
  }
  while (x > 0) {
    if (x & 0x1)
      result = result * p2;
    p2 = p2 * p2;
    x >>= 1;
  }
  return f2u(result);
}
