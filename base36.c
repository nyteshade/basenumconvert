#include <exec/types.h>
#include <dos/dos.h>
#include <dos/rdargs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <proto/dos.h>
#include "strnumconvert.h"

const char __ver[40] = "$VER: Base36 1.0 (15.01.2024)";

int main(int argc, char *argv[]) {
  struct RDArgs *args;
  LONG number = 0;
  STRPTR from36 = NULL;
  Base36Str output = "\0"; // Buffer for base 36 output, change size if necessary

  // Define the template
  STRPTR template = "FROM36/K,NUMBER/N";
  LONG result[2] = {0};

  // Parse arguments
  args = ReadArgs(template, result, NULL);

  if (args) {
    from36 = (STRPTR)result[0];
    number = *(LONG*)result[1];

    if (from36) {
      // Convert from Base 36 to decimal
      signed long decimalValue = bb_strtosl(from36, NULL, 36);
      printf("%ld\n", decimalValue);
    } else if (number) {
      // Convert from decimal to Base 36
      bb_itoa(number, output, 36);
      printf("%s\n", output);
    }

    // Clean up
    FreeArgs(args);
  } else {
    // Error handling
    Printf("Usage: base36 FROM36/K,NUMBER/N\n");
    return RETURN_FAIL;
  }

  return RETURN_OK;
}