#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "strnumconvert.h"

#define MAX_BASES 6

/* ------------------------ getMaxStrLenForBase -------------------------- */

static const BaseMaxStrLen baseMaxStrLenArray[MAX_BASES] = {
    {62, MAX_BASE62_STR_LEN + 1},
    {36, MAX_BASE36_STR_LEN + 1},
    {16, MAX_BASE16_STR_LEN + 1},
    {10, MAX_BASE10_STR_LEN + 1},
    {7, MAX_BASE7_STR_LEN + 1},
    {2, MAX_BASE2_STR_LEN + 1}
};

static const BaseMaxStrLen baseMaxSignedStrLenArray[MAX_BASES] = {
    {62, MAX_SIGNED_BASE62_STR_LEN + 1},
    {36, MAX_SIGNED_BASE36_STR_LEN + 1},
    {16, MAX_SIGNED_BASE16_STR_LEN + 1},
    {10, MAX_SIGNED_BASE10_STR_LEN + 1},
    {7, MAX_SIGNED_BASE7_STR_LEN + 1},
    {2, MAX_SIGNED_BASE2_STR_LEN + 1}
};

size_t bb_getMaxStrLenForBase(int base) {
  int i = 0;

  for (i = 0; i < MAX_BASES; ++i) {
    if (baseMaxStrLenArray[i].base == base) {
      return baseMaxStrLenArray[i].maxStrLen;
    }
  }
  return 0; // Return 0 if base not found
}

size_t bb_getMaxSignedStrLenForBase(int base) {
  int i = 0;

  for (i = 0; i < MAX_BASES; ++i) {
    if (baseMaxSignedStrLenArray[i].base == base) {
      return baseMaxSignedStrLenArray[i].maxStrLen;
    }
  }
  return 0; // Return 0 if base not found
}

/* --------------------- String to Unsigned Long ------------------------- */

unsigned long bb_strtoul(const char *str, char **endptr, int base) {
  const char *p = str;
  unsigned long result = 0;
  unsigned long max_value;
  int digit, overflow = 0;
  int strlength = strlen(str);
  int sign = 1;

  // Return 0 if string is too long for the given base
  if (strlength >= bb_getMaxStrLenForBase(base)) {
    fprintf(stderr, "The supplied string is too long for the requested base");
    return 0;
  }

  // Skip whitespace
  while (isspace((unsigned char)*p)) p++;

  // Handle optional sign
  if (*p == '+' || *p == '-') {
    sign = (*p++ == '-') ? -1 : 1;
  }

  if (base < 2 || base > 62) {
    // Invalid base
    if (endptr) *endptr = (char *)str;
    return 0;
  }

  // Convert
  max_value = ULONG_MAX / base;
  while ((digit = isdigit((unsigned char)*p) ? *p - '0' :
           islower((unsigned char)*p) ? *p - 'a' + 10 :
           isupper((unsigned char)*p) ? *p - 'A' + 36 : -1) >= 0 &&
       digit < base) {
    if (result > max_value || (ULONG_MAX - digit) / base < result) {
      overflow = 1;
    }
    result = result * base + digit;
    p++;
  }

  // Set endptr
  if (endptr != NULL) {
    *endptr = (char *)(overflow ? str : p);
  }

  // Handle overflow
  if (overflow) {
    return ULONG_MAX;
  }

  return result * sign;
}

/* ---------------------- String to Signed Long ------------------------- */

signed long bb_strtosl(const char *str, char **endptr, int base) {
  const char *p = str;
  unsigned long result = 0;
  unsigned long max_value;
  int digit, overflow = 0;
  int strlength = strlen(str);
  int sign = 1;

  if (strlength > bb_getMaxSignedStrLenForBase(base)) {
    fprintf(stderr, "The supplied string is too long for the requested base\n");
    return 0;
  }

  while (isspace((unsigned char)*p)) p++;

  if (*p == '+' || *p == '-') {
    sign = (*p++ == '-') ? -1 : 1;
  }

  if (base < 2 || base > 62) {
    if (endptr) *endptr = (char *)str;
    return 0;
  }

  max_value = (sign == 1) ? LONG_MAX / base : -(LONG_MIN / base);

while (1) {
    if (isdigit((unsigned char)*p)) {
      digit = *p - '0';
    } else if (base > 10 && isalpha((unsigned char)*p)) {
      char lower_p = tolower((unsigned char)*p);
      if (base <= 36) {
        // For bases up to 36, treat 'a' to 'z' as 10 to 35
        digit = lower_p - 'a' + 10;
      } else if (base == 62) {
        // For base 62, treat 'A' to 'Z' as 10 to 35 and 'a' to 'z' as 36 to 61
        digit = islower((unsigned char)*p) ? *p - 'a' + 36 : *p - 'A' + 10;
      } else {
        // Invalid character for this base
        break;
      }
    } else {
      // Invalid character
      break;
    }

    if (digit < 0 || digit >= base) {
      break;
    }

    if (result > max_value || (result == max_value && digit > LONG_MAX % base)) {
      overflow = 1;
      break;
    }

    result = result * base + digit;
    p++;
  }

  if (endptr != NULL) {
    *endptr = (char *)(overflow ? str : p);
  }

  if (overflow) {
    return (sign == 1) ? LONG_MAX : LONG_MIN;
  }

  return (sign == 1) ? (long)result : -(long)result;
}

/* ---------------------------- Reverse ---------------------------------- */

void reverse(char *str, int length) {
  int start = 0;
  int end = length - 1;

  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

/* --------------------- Integer to ASCII (String) ----------------------- */

char* bb_itoa(unsigned long value, char *str, int base) {
  int i = 0;
  int isNegative = 0;

  // Handle 0 explicitly
  if (value == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // Handle negative numbers for base 10
  if (value < 0 && base == 10) {
    isNegative = 1;
    value = -value;
  }

  // Convert to string
  while (value != 0) {
    int rem = value % base;

    if (rem < 10) {
      str[i++] = rem + '0';
    } else if (rem < 36) {
      str[i++] = rem - 10 + 'a';
    } else {
      str[i++] = rem - 36 + 'A';
    }

    value = value / base;
  }

  // If number is negative, append '-'
  if (isNegative) {
    str[i++] = '-';
  }

  str[i] = '\0'; // Null-terminate string

  // Reverse the string
  reverse(str, i);

  return str;
}

unsigned long bb_parseInt(const char *str, int base) {
  switch(base) {
    case 62:
    case 36:
    case 16:
    case 10:
    case 7:
    case 2:
      return bb_strtoul(str, NULL, base);

    default:
      fprintf(stderr, "Cannot parse in that base; only 62, 36, 16, 10, 7 and 2 are supported\n");
      return 0;
  }
}