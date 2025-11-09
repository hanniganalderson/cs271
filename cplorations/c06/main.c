/****************************************
 * C-ploration 6 for CS 271
 *
 * [NAME] $HANNIGAN ALDERSON$
 * [TERM] FALL $2025$
 *
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{
    if (argc!=2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    parse(file);
    fclose(file);
    return 0;
}
