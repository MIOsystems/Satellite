#ifndef UTILITY_H_
#define UTILITY_H_

// gets the length of an array as a decimal
#define ARRAY_SIZEOF(x) sizeof(x) / sizeof((x)[0])

// shifts a value a certain amount to the left
#define BITSHIFT_LEFT(val, amount) val << amount

#define FIND_MAX(x,y) (((x) >= (y)) ? (x) : (y))
#define FIND_MIN(x,y) (((x) <= (y)) ? (x) : (y))



#endif
