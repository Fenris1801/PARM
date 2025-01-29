#include "as.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Error opening source file\n");
        return 1;
    }

    uint16_t *instructions = malloc(sizeof(uint16_t));
    int instr_count = assemble_file(file, &instructions);
    if (!instr_count)
        printf("Error while assembling file, exiting...\n");
    else
        printf("Assembly completed\n");

    char output_file[50];
    strcpy(output_file, argv[1]);
    strcpy(output_file + (int)(strchr(argv[1], '.') - argv[1]), OUTPUT_EXT);
    write_logisim_file(output_file, instructions, instr_count);
    free(instructions);
    return 0;
}
