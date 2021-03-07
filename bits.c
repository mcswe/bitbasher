// AUTHOR: github.com/mcswe
// DATE: February 9, 2021

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    int y = 255;
    n = n << 3;
    x = x >> n;
    return (x & y);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    int y = x >> n;
    int mask = (1 << 31) >> n;
    mask = mask << 1;
    mask = ~mask;
    return y & mask;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    int y = (x | (~x + 1));
    y = y >> 31;
    return y + 1;
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return(1 << 31);
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    int y = 32 + (~n + 1);
    int z = (x << y) >> y;
    return !(z^x);
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int sign = x >> 31;
    int signbit = sign & 1;
    int mask = (signbit << n) + sign;
    return (x + mask) >> n;
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x + 1;
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    int ifZero = !!x;
    int xSign = x >> 31;
    xSign = ~xSign;
    xSign = xSign & 1;
    xSign = xSign & ifZero;
    return xSign;
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int xsign = (x>>31) & 1;
    int ysign = (y>>31) & 1;
    int samesign = !(xsign ^ ysign);
    int diff = ((y + (~x + 1)) >> 31) & 1;
    return ((xsign & !ysign) | (samesign & !diff));
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
/* Any power of 2 will have ONE 1 and remaining 0's
    Brute force: check all 31 positions for a 1
    Efficient approach: return 2^31 by adding up values of 16+8+4+2+1 (5 positions) 
                                                  10000, 01000, 00100, 00010, 00001
*/
    int log2, p4, p3, p2, p1, p0;
    p4 = !! (x >> 16); // will be 1 if x > 2^16
    log2 = (p4 << 4); // moves the 1 to position 5: 2^4  (add 16 to floor -- 10000)
    p3 = !! (x >> (log2 + 8));
    log2 += (p3 << 3); // add 8 to the floor 01000
    p2 = !! (x >> (log2 + 4));
    log2 += (p2 << 2); // add 4 to the floor 00100
    p1 = !! (x >> (log2 +2 ));
    log2 += (p1 << 1); // add 2 to the floor 00010
    p0 = !! (x >> (log2 + 1));
    return log2 += p0; // add 1 to the floor 00001
}

/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    int negf = uf ^ 0x80000000; // change sign bit
    int frac = uf & 0x7FFFFFFF; // mask with all 1's. if last 23 bits = 0, we know #=infinity
    if(frac > 0x7F800000) { // if frac field = nonzero, we know it is NaN
        return uf;
    }  
    return negf;
}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    // sign s
    int s, exp, frac;
    s = (1 << 31) & x;
    if (x == 0) {
        return x;
    }
    if (x & s) { 
        x = ~x+1; 
    }

    // exp field
    exp = 31;
    while (!(x & 0x80000000)) {
        x = x << 1;
        exp -= 1;
    }

    // mantissa (frac field)
    frac = (x & 0x7FFFFFFF) >> 8;
    if ((x & 0x80) && ((x & 0x7F) != 0 || frac & 1)) { // if x >= half, we need to round up 
        frac += 1;
    }

    exp = (exp + 127) << 23; // shift back to rightful positions (24-30)
    return s + exp + frac;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    int s, e, frac;

    s = (uf >> 31) & 1; 

    e = uf >> 23; // fill in exp bits (8 bits)
    e = e & 0xFF;
    frac = uf & 0x7FFFFF; //frac - last 23 bits

    if (e == 0xFF) { //if exp all 1's (NaN)
        return uf;
    }

    if (e == 0) { //if e is all 0s (denormalized form)
        frac = frac << 1; 
    }

    else {
        e = e + 1; 
        if (e == 0xFF) {
            frac = frac << 1;
        }
    }

    s = s << 31; // shift sign to correct position
    e = e << 23; // shift exp field bits to correct position
    return s + e + frac;
}
