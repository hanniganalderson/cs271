/****************************************
 * C-ploration 6 for CS 271
 *
 * [NAME] $HANNIGAN ALDERSON$
 * [TERM] FALL $2025$
 *
 ****************************************/
#include "parser.h"
#include "error.h"

bool is_Atype(const char *line) { return line[0] == '@'; }

bool is_label(const char *line) {
  size_t n = strlen(line);
  return n >= 2 && line[0] == '(' && line[n - 1] == ')';
}

bool is_Ctype(const char *line) { return !is_Atype(line) && !is_label(line); }

char *extract_label(const char *line, char *label) {
  int i = 0;
  for (int j = 0; line[j]; j++)
    if (line[j] != '(' && line[j] != ')')
      label[i++] = line[j];
  label[i] = '\0';
  return label;
}
/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s) {
  char s_new[strlen(s) + 1];
  int i = 0;

  for (char *s2 = s; *s2; s2++) {
    if (*s2 == '/' && *(s2 + 1) == '/') {
      break;
    } else if (!isspace(*s2)) {
      s_new[i++] = *s2;
    }
  }
  s_new[i] = '\0';
  strcpy(s, s_new);

  return s;
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments.
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE *file) {
  char line[MAX_LINE_LENGTH];
  unsigned int line_num = 0;
  unsigned int instr_num = 0;

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line_num++;

    if (instr_num > MAX_INSTRUCTIONS) {
      exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
    }

    strip(line);
    if (!*line)
      continue;

    char inst_type = 'C';

    if (is_Atype(line)) {
      inst_type = 'A';
    } else if (is_label(line)) {
      inst_type = 'L';

      char label[MAX_LABEL_LENGTH];
      char original_line[MAX_LINE_LENGTH];

      strcpy(original_line, line); // "(_start)" or "(add)"
      extract_label(line, label);  // label becomes "_start" or "add"

      if (!isalpha(label[0])) {
        exit_program(EXIT_INVALID_LABEL, line_num, original_line);
      }
      if (symtable_find(label) != NULL) {
        exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, original_line);
      }

      symtable_insert(label, instr_num);
      continue;
    }

    printf("%u: %c  %s\n", instr_num, inst_type, line);
    instr_num++;
  }
}
