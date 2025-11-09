/****************************************
 * C-ploration 6 for CS 271
 *
 * [NAME] $HANNIGAN ALDERSON$
 * [TERM] FALL $2025$
 *
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type {
    INVALID = -1,
    A_TYPE,
    C_TYPE
};

typedef struct {
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
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
    };
    enum instr_type type;
} instruction;

char *strip(char *s);
void parse(FILE * file);
/** for cploration 5 */
bool is_Atype(const char *line);
bool is_label(const char *line);
bool is_Ctype(const char *line);
char *extract_label(const char *line, char *label);
