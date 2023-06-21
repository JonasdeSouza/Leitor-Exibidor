#include "../include/header.h"

int main()
{
    FILE *file = fopen("assets/class/method_test.class", "rb"); // Substitua "Example.class" pelo nome do arquivo .class desejado

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler e verificar a assinatura do arquivo .class
    uint32_t magic = readUInt32(file);
    if (magic != 0xCAFEBABE)
    {
        printf("Arquivo inválido.\n");
        return 1;
    }

    // Ler a versão do arquivo .class
    uint16_t minorVersion = readUInt16(file);
    uint16_t majorVersion = readUInt16(file);

    printf("Minor Version: %u\n", minorVersion);
    printf("Major Version: %u ", majorVersion);
    getJavaVersion(majorVersion);

    // Ler a quantidade de entradas no pool de constantes
    uint16_t constantPoolCount = readUInt16(file);
    printf("Quantidade de entradas no pool de constantes: %u\n", constantPoolCount);

    cp_info *resConstantPool = readConstantPool(file, constantPoolCount);

    uint16_t accessFlag = readUInt16(file);
    printf("Access Flags: 0x%.4X ", accessFlag);
    decodeAccessFlag(accessFlag);

    uint16_t thisClass = readUInt16(file);
    printf("This class: cp_info #%u ", thisClass);
    printf("<%s>\n", resConstantPool[resConstantPool[thisClass - 1].UnionCP.CONSTANT_Class.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);

    uint16_t superClass = readUInt16(file);
    printf("Super class: cp_info #%u ", superClass);
    printf("<%s>\n", resConstantPool[resConstantPool[superClass - 1].UnionCP.CONSTANT_Class.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);

    // Interfaces
    uint16_t interfaceCount = readUInt16(file);
    printf("Interfaces Count: %u\n", interfaceCount);
    readInterfaces(file, interfaceCount);

    // Fields
    uint16_t fieldsCount = readUInt16(file);
    printf("Fields Count: %u\n", fieldsCount);
    readFields(file, fieldsCount);

    // Methods
    uint16_t methodsCount = readUInt16(file);
    printf("Methods Count: %u\n", methodsCount);
    method_info *resMethods = readMethods(file, methodsCount);

    // Attributes
    uint16_t attributesCount = readUInt16(file);
    printf("Attributes Count: %u\n", attributesCount);
    attribute_info *resAttributes = readAttributes(file, attributesCount);

    // Fechar o arquivo
    fclose(file);

    // printConstantPool(resConstantPool, constantPoolCount);
    // printMethods(resMethods, methodsCount, resConstantPool); // TODO: printf access flags
    // printAttributes(resAttributes, attributesCount, resConstantPool); // TODO: printf info/specific info
    return 0;
}