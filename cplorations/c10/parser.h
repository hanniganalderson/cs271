/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] $HANNIGAN ALDERSON$
 * [TERM] FALL $2025$
 * 
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include "symtable.h"
#include "hack.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t opcode;

enum instr_type {INVALID = -1, INST_A, INST_C};

typedef struct {
int a : 1;
int comp : 7;
int dest : 4;
int jump : 4;
} c_instruction;

typedef struct {
union {
hack_addr address;
char *label;
};
bool is_addr;
} a_instruction;

typedef struct {
union {
a_instruction a;
c_instruction c;
} instr;
enum instr_type itype;
} instruction;

char *strip(char *s);
int parse(FILE *file, instruction *instructions);
bool is_Atype(const char *line);
bool is_label(const char *line);
bool is_Ctype(const char *line);
char *extract_label(const char *line, char *label);
void add_predefined_symbols();
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);
#endif
