#ifndef AS_H
#define AS_H

#include <stdint.h>
#include <stdio.h>

#define FORMAT_COUNT 7
#define OPCODE_COUNT 48

#define WORD_SIZE 4

#define ENTRYPOINT "run:"
#define OUTPUT_EXT ".txt"

typedef enum
{
    IMMEDIATE_3_5,
    IMMEDIATE_8,
    REGISTER,
    SP_INDEXED,
    RELATIVE
} AdressingMode;

typedef struct
{
    char mnemonic[10];
    char operand1[50]; // for label length
    char operand2[10];
    char operand3[10];
    AdressingMode addr_mode;
    uint32_t addr;
} Instruction;

typedef struct
{
    const char *format;
    AdressingMode addr_mode;
    uint8_t operand_count;
    const char *expected_token;
} InstructionFormat;

typedef struct
{
    char mnemonic[10];
    AdressingMode addr_mode;
    uint16_t opcode;
} Opcode;

typedef struct
{
    char name[50];
    int addr;
} Label;

extern InstructionFormat format_table[FORMAT_COUNT];
extern Opcode opcode_table[OPCODE_COUNT];

int parse_instruction(char *line, Instruction *instr, int instr_count);
uint16_t get_opcode(const char *mnemonic, AdressingMode addr_mode);
uint8_t reg_to_int(const char *reg);
uint16_t encode_instruction(Instruction *instr, Label *labels, int label_count);
int assemble_file(FILE *file, uint16_t **instructions);
void write_logisim_file(const char *filename, uint16_t *instructions, int count);

#endif
