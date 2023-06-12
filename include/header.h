#ifndef HEADER_H
#define HEADER_H

// Libs utilizadas
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Libs locais
#include "structures.h"

// Para rodar o trabalho no windows o gcc definirá o seguinte macro
#ifdef _WIN32
#include <winsock.h>
#endif

// Headers para funcs
char *getMnemonic(uint8_t bytecode);
void printConstantValue(FILE *file, uint8_t tag);
uint16_t readUInt16(FILE *file);
uint32_t readUInt32(FILE *file);
const char *getConstantName(int constant);

#endif