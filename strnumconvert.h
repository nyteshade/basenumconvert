#ifndef BB_STRNUM_CONVERT_H
#define BB_STRNUM_CONVERT_H

#include <stddef.h>

#define MAX_BASE62_STR_LEN 7
#define MAX_BASE36_STR_LEN 8
#define MAX_BASE16_STR_LEN 9
#define MAX_BASE10_STR_LEN 11
#define MAX_BASE7_STR_LEN 13
#define MAX_BASE2_STR_LEN 33

#define MAX_BASE62_STR "4GFfc3"
#define MAX_BASE36_STR "1z141z3"
#define MAX_BASE16_STR "ffffffff"
#define MAX_BASE10_STR "4294967295"
#define MAX_BASE7_STR "211301422353"
#define MAX_BASE2_STR "11111111111111111111111111111111"

#define MAX_SIGNED_BASE62_STR_LEN 8
#define MAX_SIGNED_BASE36_STR_LEN 8
#define MAX_SIGNED_BASE16_STR_LEN 10
#define MAX_SIGNED_BASE10_STR_LEN 12
#define MAX_SIGNED_BASE7_STR_LEN 14
#define MAX_SIGNED_BASE2_STR_LEN 34

#define MAX_SIGNED_BASE62_STR "2lkCB1"
#define MAX_SIGNED_BASE36_STR "zik0zj"
#define MAX_SIGNED_BASE16_STR "7fffffff"
#define MAX_SIGNED_BASE10_STR "2147483647"
#define MAX_SIGNED_BASE7_STR "104134211161"
#define MAX_SIGNED_BASE2_STR "1111111111111111111111111111111"

#define MIN_SIGNED_BASE62_STR "-2lkCB2"
#define MIN_SIGNED_BASE36_STR "-zik0zk"
#define MIN_SIGNED_BASE16_STR "-80000000"
#define MIN_SIGNED_BASE10_STR "-2147483648"
#define MIN_SIGNED_BASE7_STR "-104134211162"
#define MIN_SIGNED_BASE2_STR "-10000000000000000000000000000000"

typedef char Base62Str[7];
typedef char Base36Str[8];
typedef char Base16Str[9];
typedef char Base10Str[11];
typedef char Base7Str[13];
typedef char Base2Str[33];

typedef struct {
  int base;
  size_t maxStrLen;
} BaseMaxStrLen;

unsigned long bb_parseInt(const char *str, int base);
unsigned long bb_strtoul(const char *str, char **endptr, int base);
signed long bb_strtosl(const char *str, char **endptr, int base);
char* bb_itoa(unsigned long value, char *str, int base);

size_t bb_getMaxStrLenForBase(int base);

#endif