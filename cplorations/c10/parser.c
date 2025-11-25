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

void add_predefined_symbols() {
for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
predefined_symbol symbol = predefined_symbols[i];
symtable_insert(symbol.name, symbol.address);
}
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
char *s = malloc(strlen(line));
strcpy(s, line + 1);

char *s_end = NULL;
long result = strtol(s, &s_end, 10);

if (s == s_end) {
instr->label = malloc(strlen(line));
strcpy(instr->label, s);
instr->is_addr = false;
} else if (*s_end != 0) {
free(s);
return false;
} else {
instr->address = result;
instr->is_addr = true;
}

free(s);
return true;
}

void parse_C_instruction(char *line, c_instruction *instr) {
char *temp = strtok(line, ";");
char *jump = strtok(NULL, ";");

char *dest = strtok(temp, "=");
char *comp = strtok(NULL, "=");

if (comp == NULL) {
comp = dest;
dest = NULL;
}

int a = 0;
instr->jump = str_to_jumpid(jump);
instr->dest = str_to_destid(dest);
instr->comp = str_to_compid(comp, &a);
instr->a = a ? 1 : 0;
}

int parse(FILE *file, instruction *instructions) {
char line[MAX_LINE_LENGTH];
unsigned int line_num = 0;
unsigned int instr_num = 0;
instruction instr;

add_predefined_symbols();

while (fgets(line, MAX_LINE_LENGTH, file)) {
line_num++;

if (instr_num > MAX_INSTRUCTIONS) {
exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
}

strip(line);
if (!*line)
continue;

if (is_Atype(line)) {
if (!parse_A_instruction(line, &instr.instr.a)) {
exit_program(EXIT_INVALID_A_INSTR, line_num, line);
}
instr.itype = INST_A;
if (instr.instr.a.is_addr) {
printf("A: %d\n", instr.instr.a.address);
} else {
printf("A: %s\n", instr.instr.a.label);
}
} else if (is_label(line)) {
char label[MAX_LABEL_LENGTH];
extract_label(line, label);

if (!isalpha(label[0])) {
exit_program(EXIT_INVALID_LABEL, line_num, label);
}

if (symtable_find(label) != NULL) {
exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
}

symtable_insert(label, instr_num);
continue;
} else {
char tmp_line[MAX_LINE_LENGTH];
strcpy(tmp_line, line);
parse_C_instruction(tmp_line, &instr.instr.c);

if (instr.instr.c.dest == DEST_INVALID) {
exit_program(EXIT_INVALID_C_DEST, line_num, line);
}
if (instr.instr.c.comp == COMP_INVALID) {
exit_program(EXIT_INVALID_C_COMP, line_num, line);
}
if (instr.instr.c.jump == JMP_INVALID) {
exit_program(EXIT_INVALID_C_JUMP, line_num, line);
}
instr.itype = INST_C;
printf("C: d=%d, c=%d, j=%d\n", instr.instr.c.dest, instr.instr.c.comp, instr.instr.c.jump);
}

instructions[instr_num++] = instr;
}
return instr_num;
}
