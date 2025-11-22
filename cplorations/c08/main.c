/****************************************
 * C-ploration 6 for CS 271
 *
 * [NAME] $HANNIGAN ALDERSON$
 * [TERM] FALL $2025$
 *
 ****************************************/
#include "error.h"
#include "parser.h"

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
  }
  parse(file);
  fclose(file);
  return 0;
}
