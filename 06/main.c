#include "error.h"
#include "parser.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
  }
  instruction *instructions =
      malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
  int num_instructions = parse(file, instructions);
  fclose(file);
  assemble(argv[1], instructions, num_instructions);
  free(instructions);
  return 0;
}