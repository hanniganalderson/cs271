/****************************************
 * C-ploration 6 for CS 271
 *
 * [NAME] $HANNIGAN ALDERSON$
 * [TERM] FALL $2025$
 *
 ****************************************/
#include "parser.h"

bool is_Atype(const char *line)
    { return line[0]=='@';}
bool is_label(const char *line){
    size_t n=strlen(line);
    return n>=2&&line[0]=='('&&line[n-1]==')';
}
bool is_Ctype(const char *line){ return !is_Atype(line)&&!is_label(line);}

char *extract_label(const char *line, char *label) {
    int i=0; for (int j=0; line[j];j++) if (line[j]!='(' && line[j] !=')') label[i++]=line[j];
    label[i] ='\0'; return label;
}
/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){
    char s_new[strlen(s) + 1];
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break;
        }
        else if (!isspace(*s2)) {
            s_new[i++] = *s2 ;
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
 void parse(FILE *file){
     char line[MAX_LINE_LENGTH];
     hack_addr rom_addr=0;
     while (fgets(line, MAX_LINE_LENGTH, file)){
         strip(line);
         if(!*line) continue;
         char t='C';
         if(is_Atype(line)){ t='A'; rom_addr++; }
         else if(is_label(line)){
             t='L';
             char l[MAX_LABEL_LENGTH];
             extract_label(line,l);
             strcpy(line,l);
             symtable_insert(line,rom_addr);
         } else {
             t='C';
             rom_addr++;
         }
         //printf("%c  %s\n", t, line);
     }
 }
