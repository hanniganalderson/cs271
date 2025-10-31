/****************************************
 * C-ploration 5 for CS 271
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

#define MAX_LINE_LENGTH  200

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);
/** for cploration 5 */
bool is_Atype(const char *line);
bool is_label(const char *line);
bool is_Ctype(const char *line);
