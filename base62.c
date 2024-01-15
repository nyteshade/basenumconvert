#include <exec/types.h>
#include <dos/dos.h>
#include <dos/rdargs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <proto/dos.h>
#include "strnumconvert.h"

const char __ver[40] = "$VER: Base62 1.0 (15.01.2024)";

int main(int argc, char *argv[]) {
  struct RDArgs *args;
  LONG number = 0;
  STRPTR from62 = NULL;
  Base62Str output = "\0"; // Buffer for base 62 output, change size if necessary

  // Define the template
  STRPTR template = "FROM62/K,NUMBER/N";
  LONG result[2] = {0};

  // Parse arguments
  args = ReadArgs(template, result, NULL);

  if (args) {
    from62 = (STRPTR)result[0];
    number = *(LONG*)result[1];

    if (from62) {
      // Convert from Base 62 to decimal
      signed long decimalValue = bb_strtosl(from62, NULL, 62);
      printf("%ld\n", decimalValue);
    } else if (number) {
      // Convert from decimal to Base 62
      bb_itoa(number, output, 62);
      printf("%s\n", output);
    }

    // Clean up
    FreeArgs(args);
  } else {
    // Error handling
    Printf("Usage: base62 FROM62/K,NUMBER/N\n");
    return RETURN_FAIL;
  }

  return RETURN_OK;
}