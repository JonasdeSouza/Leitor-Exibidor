#ifndef HEADER_H
#define HEADER_H

// Libs utilizadas
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Libs locais
#include "structures.h"
#include "attributes.h"
#include "constants.h"

// Para rodar o trabalho no windows o gcc definirá o seguinte macro
#ifdef _WIN32
#include <winsock.h>
#endif

// Headers para funcs
// Leitor
char *getMnemonic(uint8_t bytecode);
void printConstantValue(FILE *file, uint8_t tag);
uint16_t readUInt16(FILE *file);
uint32_t readUInt32(FILE *file);
u2 *readInterfaces(FILE *fp, u2 size);
field_info *readFields(FILE *fp, u2 fields_count);
cp_info *readConstantPool(FILE *fp, u2 constant_pool_count);
// Exibidor
void decodeAccessFlag(u2 flag);
void printConstantPool(cp_info aux[], int constant_pool_count);
void printRefValue(int value);
void getJavaVersion(int version);
#endif