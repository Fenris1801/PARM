#include "as.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

InstructionFormat format_table[FORMAT_COUNT] = {
    {"%9s %[^,], [sp, #%[^]]]", IMMEDIATE_8, 3, "[sp,"},
    {"%9s %[^,], [sp]", IMMEDIATE_8, 2, "[sp]"},
    {"%9s sp, #%9s", SP_INDEXED, 2, "sp, #"},
    {"%9s %[^,], %[^,], #%9s", IMMEDIATE_3_5, 4, ", #"},
    {"%9s %[^,], #%9s", IMMEDIATE_8, 3, ", #"},
    {"%9s %[^,], %[^,], %9s", REGISTER, 4, ","},
    {"%9s %[^,], %9s", REGISTER, 3, ","},
};

Opcode opcode_table[OPCODE_COUNT] = {
    {"LSLS", IMMEDIATE_3_5, 0x000},
    {"LSRS", IMMEDIATE_3_5, 0x020},
    {"ASRS", IMMEDIATE_3_5, 0x040},
    {"ADDS", REGISTER, 0x060},
    {"SUBS", REGISTER, 0x068},
    {"ADDS", IMMEDIATE_3_5, 0x070},
    {"SUBS", IMMEDIATE_3_5, 0x078},
    {"MOVS", IMMEDIATE_8, 0x080},
    {"CMP", IMMEDIATE_8, 0x0A0},
    {"ADDS", IMMEDIATE_8, 0x0C0},
    {"SUBS", IMMEDIATE_8, 0x0E0},
    {"ANDS", REGISTER, 0x100},
    {"EORS", REGISTER, 0x101},
    {"LSLS", REGISTER, 0x102},
    {"LSRS", REGISTER, 0x103},
    {"ASRS", REGISTER, 0x104},
    {"ADCS", REGISTER, 0x105},
    {"SBCS", REGISTER, 0x106},
    {"RORS", REGISTER, 0x107},
    {"TST", REGISTER, 0x108},
    {"RSBS", IMMEDIATE_3_5, 0x109},
    {"CMP", REGISTER, 0x10A},
    {"CMN", REGISTER, 0x10B},
    {"ORRS", REGISTER, 0x10C},
    {"MULS", REGISTER, 0x10D},
    {"BICS", REGISTER, 0x10E},
    {"MVNS", REGISTER, 0x10F},
    {"STR", IMMEDIATE_8, 0x240},
    {"LDR", IMMEDIATE_8, 0x260},
    {"ADD", SP_INDEXED, 0x2C0},
    {"SUB", SP_INDEXED, 0x2C2},
    {"B", RELATIVE, 0x380},
    {"BEQ", RELATIVE, 0x340},
    {"BNE", RELATIVE, 0x344},
    {"BCS", RELATIVE, 0x348},
    {"BHS", RELATIVE, 0x348},
    {"BCC", RELATIVE, 0x34C},
    {"BLO", RELATIVE, 0x34C},
    {"BMI", RELATIVE, 0x350},
    {"BVS", RELATIVE, 0x358},
    {"BVC", RELATIVE, 0x35C},
    {"BHI", RELATIVE, 0x360},
    {"BLS", RELATIVE, 0x364},
    {"BGE", RELATIVE, 0x368},
    {"BLT", RELATIVE, 0x36C},
    {"BGT", RELATIVE, 0x370},
    {"BLE", RELATIVE, 0x374},
    {"BAL", RELATIVE, 0x378},
};

int parse_instruction(char *line, Instruction *instr, int instr_count)
{
    instr->operand2[0] = '\0';
    instr->operand3[0] = '\0';
    if (!strchr(line, ','))
    {
        sscanf(line, "%9s %49s", instr->mnemonic, instr->operand1);
        instr->addr_mode = RELATIVE;
        instr->addr = instr_count;
        return 1;
    }
    for (int i = 0; i < FORMAT_COUNT; i++)
    {
        int result = sscanf(line, format_table[i].format, instr->mnemonic, instr->operand1, instr->operand2, instr->operand3);
        if (result == format_table[i].operand_count && strstr(line, format_table[i].expected_token))
        {
            instr->addr_mode = format_table[i].addr_mode;
            instr->addr = instr_count;
            return 1;
        }
    }
    return 0;
}

uint16_t get_opcode(const char *mnemonic, AdressingMode addr_mode)
{
    for (int i = 0; i < OPCODE_COUNT; i++)
        if (strstr(opcode_table[i].mnemonic, mnemonic) && opcode_table[i].addr_mode == addr_mode)
            return opcode_table[i].opcode;
    return 0;
}

uint8_t reg_to_int(const char *reg)
{
    if (!reg)
        return 0;
    if (strcmp(reg, "sp") == 0)
        return 15;
    if (strcmp(reg, "pc") == 0)
        return 14;
    return atoi(reg + 1);
}

uint16_t encode_instruction(Instruction *instr, Label *labels, int label_count)
{
    uint16_t instruction = 0x0000;
    uint16_t opcode = get_opcode(strupr(instr->mnemonic), instr->addr_mode);
    switch (instr->addr_mode)
    {
    case REGISTER:
        instruction |= (reg_to_int(instr->operand3) << 6) | (reg_to_int(instr->operand2) << 3) | reg_to_int(instr->operand1);
        break;
    case IMMEDIATE_3_5:
        instruction |= (atoi(instr->operand3) << 6) | (reg_to_int(instr->operand2) << 3) | reg_to_int(instr->operand1);
        break;
    case IMMEDIATE_8:
        instruction |= (reg_to_int(instr->operand1) << 8) | (opcode == 0x240 || opcode == 0x260 ? atoi(instr->operand2) / WORD_SIZE : atoi(instr->operand2));
        break;
    case SP_INDEXED:
        instruction |= atoi(instr->operand1) / WORD_SIZE;
        break;
    case RELATIVE:
        for (int i = 0; i < label_count; i++)
            if (strcmp(instr->operand1, labels[i].name) == 0)
            {
                int offset = labels[i].addr - instr->addr - 3;
                int bit_width = opcode == 0x380 ? 11 : 8;
                instruction |= ((offset < 0 ? ((1 << bit_width) + offset) : offset) & 0x7FF);
                break;
            }
        break;
    }
    return instruction | (opcode << 6);
}

char *trim(char *str)
{
    char *end;
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    *(end + 1) = 0;
    return str;
}

int assemble_file(FILE *file, uint16_t **instructions)
{
    char line[100];
    Instruction *instrs = malloc(sizeof(Instruction));
    Label *labels = malloc(sizeof(Label));
    int instr_count = 0;
    int label_count = 0;

    while (fgets(line, sizeof(line), file))
    {
        char *trimmed = trim(line);
        if (strcmp(ENTRYPOINT, trimmed) == 0)
            break;
    }
    if (feof(file))
    {
        printf("Error: Entrypoint '%s' not found in file.\n", ENTRYPOINT);
        return 0;
    }

    while (fgets(line, sizeof(line), file))
    {
        char *trimmed = trim(line);
        char *comment = strchr(trimmed, '@');
        if (comment)
            *comment = '\0';
        if (strlen(trimmed) == 0)
            continue;
        if (strchr(trimmed, '.') && strchr(trimmed, ':'))
        {
            sscanf(trimmed, "%[^:]:", labels[label_count].name);
            labels[label_count].addr = instr_count;
            labels = realloc(labels, (++label_count + 1) * sizeof(Label));
        }
        else if (trimmed[0] != '.' && parse_instruction(trimmed, &instrs[instr_count], instr_count))
            instrs = realloc(instrs, (++instr_count + 1) * sizeof(Instruction));
    }
    fclose(file);

    for (int i = 0; i < instr_count; i++)
    {
        *instructions = realloc(*instructions, (i + 1) * sizeof(uint16_t));
        (*instructions)[i] = encode_instruction(&instrs[i], labels, label_count);
    }
    free(instrs);
    free(labels);

    return instr_count;
}

void write_logisim_file(const char *filename, uint16_t *instructions, int count)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file\n");
        exit(1);
    }
    printf("v2.0 raw\n");
    fprintf(file, "v2.0 raw\n");
    for (int i = 0; i < count; i++)
    {
        printf("%04x ", instructions[i]);
        fprintf(file, "%04x ", instructions[i]);
        if ((i + 1) % 16 == 0)
            fprintf(file, "\n");
    }
    printf("\n");
    fclose(file);

    printf("Writing completed successfully!\n");
}
