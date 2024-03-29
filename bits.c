/* 
 * CS:APP Data Lab 
 * 
 * Dominic Hatch dmh7817, Ian Armstrong ima5655
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
/*flips 0000... to 1111..., or -1 in 2s complement*/
   return ~0;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
/* arithmetically shifts number to 0 giving false positive for -1
 * so variable m is used to check that it is not -1*/
	int i = x + 1;
	int r = i + i;
	int m = !i;
	r = r ^ m;
	r = !r;

  return r;
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x) {
/*calculates the negative of x, then compares it to x*/ 
  x = x ^ (~x + 0x01);
  return !!x;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int e =!! (x ^ y); //checks if x=y, 0 if identical

        int xsign = (x >>31); //if x is negative this will be 1
        int ysign = (y >>31); //likewise for y 

        int xpyn = (!xsign) & ysign; //useful because if x is positive and y is negative, x>y
        int xnyp = xsign & (!ysign); 
        int samesign = !xpyn & !xnyp;

        int n = ~y + 1;
        int z = (x + n) >> 31; //if x-y is negative, z=1

        int r = (!z) & samesign;      

        r = r | xpyn;
        r = r & e; //if r, and not identical

        return r;  
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
/*flips both inputs, compares using &. This returns bits that are not in
 * either x or y. Flipping this gives bits not not in either which is 
 * in one or the other*/
  return ~(~x & ~y);
}
/* 
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and & 
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y) {
/*use & to check for same 1s, flip both and us & again to check for same 0s. 
 * Use | to combine these two sequences*/
  int ones = x & y;
  int bx = ~x;
  int by = ~y;
  int zeros = bx & by;
  int r = ones | zeros;
	return r;
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
/*constructs thebit pattern where every odd position is filled, the checks it accross*/
    int check = 1 << 1;
	int r = 0;

	check = check + (check << 2);
	check = check + (check << 4);
	check = check + (check << 8);
	check = check + (check << 16);
	
	r = x & check;
	r = !!r;	

    	return r;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/*move the desired byte to rightmost position, then check whatever is in that position with block of 1s*/
  int i = x;
	int move = n << 3;

	int block = ~0;
	block = block << 8;
	block = ~block;

	i = i >> move;
	i = i & block;
	return i;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
/*if the condition is true, do nothing to y. If false, add the difference between x and y*/
  int diff = z + (~y + 0x1);
  int cond =!x;
  int r = 0;

  cond = cond << 31;
  cond = cond >>31;

  diff = diff & cond;

  r =  y + diff;
  return r;
}
/*
 * isPallindrome - Return 1 if bit pattern in x is equal to its mirror image
 *   Example: isPallindrome(0x01234567E6AC2480) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 */
int isPallindrome(int x) {
/*splits 32 bit sequence into upper and lower 16bit halves. Use mask to extract upper and lower
 *  8 bit sequence  and | to lower 16 bit sequence. Continue process of cutting sequence in half
 *  (&ing with respective mask) and |ing with lower16. By end, lower16 contains reversed order of
 *  upper16 bit sequence. Use !^ to see if they are the same. If yes it will return 1 otherwise 0. */
   int upper16, lower16, upper8, lower8, upper4, lower4, upper2, lower2, upper1, lower1;
   int mask16, mask8, mask4, mask2, mask1;
   int result;
  
   mask16 = 0xff | (0xff << 8);
   upper16 = (x >> 16) & mask16;
   lower16 = x & mask16;

   mask8 = 0xff;
   upper8 = (lower16 >> 8) & mask8;
   lower8 = (lower16 & mask8) << 8;
   lower16 = lower8 | upper8;

   mask4 = 0xf | (0xf << 8);
   upper4 = (lower16 >> 4) & mask4;
   lower4 = (lower16 & mask4) << 4;
   lower16 = lower4 | upper4;

   mask2 = 0x33 | (0x33 << 8);
   upper2 = (lower16 >> 2) & mask2;
   lower2 = (lower16 & mask2) << 2;
   lower16 = lower2 | upper2;

   mask1 = 0x55 | (0x55 << 8);
   upper1 = (lower16 >> 1) & mask1;
   lower1 = (lower16 & mask1) << 1;
   lower16 = lower1 | upper1;

   result = lower16 ^ upper16;
   result = !result;
 return result;
}
/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
/*uses a block to extract exponent terms of the float. Checks whether the bits are the same.
 * if both are0, make it equal. If either is NaN, return 0*/
    unsigned block = ~0;
    int expf = 0;
    int expg = 0;
    
    int same = !(uf ^ ug);

    int zerof = uf << 1;
    int zerog = ug << 1;

    int nanf = 0;
    int nang = 0;

    int zeros = 0;
    int r = 0;

    block = block << 24;
    block = block  >> 1;
    expf = uf & block;
    expg = ug & block;
 
    if ((!(expf ^ block)) & !!(uf << 9)) {
	nanf = 1;
    }

    if ((!(expg ^ block)) & !!(ug << 9)) {
	nang = 1;
    }
    
    zeros = !(zerof || zerog);
    r = same | zeros;

    if (nanf || nang) {
	return 0;
    }
   return r;
}
/* 
 * floatScale1d2 - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale1d2(unsigned uf) {
/*separates parts of the float, then checks special cases of 0s and NaNs. Then checks if exponent
 * is 1. Then checks if there is no exponent. Finally checks normal case.*/
	unsigned block = ~0; //2139095040;

	unsigned exp = 0; //get the exponent term
		
	unsigned frac = (uf <<9)>>9;//get the fraction term

	unsigned sign = (uf >>31)<<31;	//get the sign term	

	unsigned fracodd = (frac & 1) && ((frac >>1) & 1); //checks whether to round up

	int r = 0;

	int exptmp = 0;

	block = block << 24;
        block = block >> 1; 

	exp = uf & block;
	exptmp = exp;

	if ((!(exp ^ block))){
                return uf;
        } //checks if NaN

	if (!(frac || exp)){
		return uf;
	} //checks for 0

        if (exp){
                exp = exp >> 23;
                exp = exp -1;
                exp = exp << 23;
        }//normal case, removes 1 from the exponent

	if (!exp){
		frac = (frac >>1) + fracodd;
	}// if there is no exponent, then modify frac accordingly, if nonzero odd round up.

	if (exptmp && (!(exptmp >>24))){
		frac = frac + (1 <<22);
	}// if exponent is 00000001, modify frac accordingly

	

	r = sign | exp | frac; //combines resulting sign, exponent, and fraction
	
	return r;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
/* checks whether x is too large or too small, otherwise move it into the exponent spot.*/
        unsigned exp = x +127;
	unsigned expsign = x>>31;
	unsigned block = 2147483392;
	
	if ((block & exp) && !expsign){
		return 2139095040;//checks whether x is too big
	}

	if ((block ^ x) && expsign){
		return 0;//checks whether x is too small
	}

	exp = exp <<23;

	return exp;}
