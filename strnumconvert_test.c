#include <stdio.h>
#include <string.h>
#include "strnumconvert.h"

const char PASS[] = "\x1b[32mPASS\x1b[0m";
const char FAIL[] = "\x1b[31mFAIL\x1b[0m";

const char* ulPass(unsigned long left, unsigned long right) {
  return left == right ? PASS : FAIL;
}

const char* slPass(signed long left, signed long right) {
  return left == right ? PASS : FAIL;
}

const char *strPass(const char* left, const char* right) {
  return strcmp(left, right) == 0 ? PASS : FAIL;
}

int main(int argc, char **argv) {
  Base62Str output62;
  Base36Str output36;
  Base16Str output16;
  Base10Str output10;
  Base7Str output7;
  Base2Str output2;

  unsigned long outputUL;
  signed long outputSL;

  /* --------------------- Unsigned Long Test Cases ------------------------ */

  printf("Testing Unsigned Long Conversions\n");
  printf("Base 62 (0-9a-zA-Z)\n");
  outputUL = bb_parseInt(MAX_BASE62_STR, 62);
  bb_itoa(4294967295UL, output62, 62);
  printf("[%s] Expected: 4294967295, Actual: %lu\n", ulPass(4294967295UL, outputUL), outputUL);
  printf("[%s] Expected: %s, Actual: %s\n\n", strPass(MAX_BASE62_STR, output62), MAX_BASE62_STR, output62);

  printf("Base 36 (0-9a-z) [case insensitive]\n");
  outputUL = bb_parseInt(MAX_BASE36_STR, 36);
  bb_itoa(4294967295UL, output36, 36);
  printf("[%s] Expected: 4294967295, Actual: %lu\n", ulPass(4294967295UL, outputUL), outputUL);
  printf("[%s] Expected: %s, Actual: %s\n\n", strPass(MAX_BASE36_STR, output36), MAX_BASE36_STR, output36);

  printf("Base 16 (0-f)\n");
  outputUL = bb_parseInt(MAX_BASE16_STR, 16);
  bb_itoa(4294967295UL, output16, 16);
  printf("[%s] Expected: 4294967295, Actual: %lu\n", ulPass(4294967295UL, outputUL), outputUL);
  printf("[%s] Expected: 0x%s, Actual: 0x%s\n\n", strPass(MAX_BASE16_STR, output16), MAX_BASE16_STR, output16);

  printf("Base 10 (n)\n");
  outputUL = bb_parseInt(MAX_BASE10_STR, 10);
  bb_itoa(4294967295UL, output10, 10);
  printf("[%s] Expected: 4294967295, Actual: %lu\n", ulPass(4294967295UL, outputUL), outputUL);
  printf("[%s] Expected: %s, Actual: 0x%s\n\n", strPass(MAX_BASE10_STR, output10), MAX_BASE10_STR, output10);

  printf("Base 7\n");
  outputUL = bb_parseInt(MAX_BASE7_STR, 7);
  bb_itoa(4294967295UL, output7, 7);
  printf("[%s] Expected: 4294967295, Actual: %lu\n", ulPass(4294967295UL, outputUL), outputUL);
  printf("[%s] Expected: 0%s, Actual: 0%s\n\n", strPass(MAX_BASE7_STR, output7), MAX_BASE7_STR, output7);

  printf("Base 2\n");
  outputUL = bb_parseInt(MAX_BASE2_STR, 2);
  bb_itoa(4294967295UL, output2, 2);
  printf("[%s] Expected: 4294967295, Actual: %lu\n", ulPass(4294967295UL, outputUL), outputUL);
  printf("[%s] Expected: %s, Actual: %s\n\n", strPass(MAX_BASE2_STR, output2), MAX_BASE2_STR, output2);

  /* ---------------------- Signed Long Test Cases ------------------------- */


  printf("Testing Signed Long Conversions\n");
  printf("Base 62 (0-9a-zA-Z)\n");
  outputSL = bb_strtosl(MAX_SIGNED_BASE62_STR, NULL, 62);
  bb_itoa(2147483647L, output62, 62);
  printf("[%s] Expected: 2147483647, Actual: %ld\n", slPass(2147483647L, outputSL), outputSL);
  printf("[%s] Expected: %s, Actual: %s\n\n", strPass(MAX_SIGNED_BASE62_STR, output62), MAX_SIGNED_BASE62_STR, output62);

  printf("Base 36 (0-9a-z) [case insensitive]\n");
  outputSL = bb_strtosl(MAX_SIGNED_BASE36_STR, NULL, 36);
  bb_itoa(2147483647L, output36,36);
  printf("[%s] Expected: 2147483647, Actual: %ld\n", slPass(2147483647, outputSL), outputSL);
  printf("[%s] Expected: %s, Actual: %s\n\n", strPass(MAX_SIGNED_BASE36_STR, output36), MAX_SIGNED_BASE36_STR, output36);

  printf("Base 16 (0-f)\n");
  outputSL = bb_strtosl(MAX_SIGNED_BASE16_STR, NULL, 16);
  bb_itoa(2147483647L, output16, 16);
  printf("[%s] Expected: 2147483647, Actual: %ld\n", slPass(2147483647, outputSL), outputSL);
  printf("[%s] Expected: 0x%s, Actual: 0x%s\n\n", strPass(MAX_SIGNED_BASE16_STR, output16), MAX_SIGNED_BASE16_STR, output16);

  printf("Base 10 (n)\n");
  outputSL = bb_strtosl(MAX_SIGNED_BASE10_STR, NULL, 10);
  bb_itoa(2147483647L, output10, 10);
  printf("[%s] Expected: 2147483647, Actual: %ld\n", slPass(2147483647, outputSL), outputSL);
  printf("[%s] Expected: %s, Actual: %s\n\n", strPass(MAX_SIGNED_BASE10_STR, output10), MAX_SIGNED_BASE10_STR, output10);

  printf("Base 7\n");
  outputSL = bb_strtosl(MAX_SIGNED_BASE7_STR, NULL, 7);
  bb_itoa(2147483647L, output7, 7);
  printf("[%s] Expected: 2147483647, Actual: %ld\n", slPass(2147483647, outputSL), outputSL);
  printf("[%s] Expected: 0%s, Actual: 0%s\n\n", strPass(MAX_SIGNED_BASE7_STR, output7), MAX_SIGNED_BASE7_STR, output7);

  printf("Base 2\n");
  outputSL = bb_strtosl(MAX_SIGNED_BASE2_STR, NULL, 2);
  bb_itoa(2147483647L, output2, 2);
  printf("[%s] Expected: 2147483647, Actual: %ld\n", slPass(2147483647, outputSL), outputSL);
  printf("[%s] Expected: %s, Actual: %s\n\n", strPass(MAX_SIGNED_BASE2_STR, output2), MAX_SIGNED_BASE2_STR, output2);

  return 0;
}
