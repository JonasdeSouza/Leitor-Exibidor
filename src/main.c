#include "../include/header.h"

int main()
{
    FILE *file = fopen("assets/fatorial.class", "rb"); // Substitua "Example.class" pelo nome do arquivo .class desejado

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

    printf("Versao: %u.%u\n", majorVersion, minorVersion);

    // Ler a quantidade de entradas no pool de constantes
    uint16_t constantPoolCount = readUInt16(file);
    printf("Quantidade de entradas no pool de constantes: %u\n", constantPoolCount);

    char *Mneumonico;

    readConstantPool(file, constantPoolCount);

    printf("Access Flags: 0x%.4X\n", readUInt16(file));

    printf("This class: %u\n", readUInt16(file));
    printf("Super class: %u\n", readUInt16(file));
    printf("Interfaces Count: %u\n", readUInt16(file));

    //printf("Interfaces: %u\n", readUInt16(file)); // TODO, IF 0 Not READ

    printf("Fields Count: %u\n", readUInt16(file));

    //printf("Fields: %u\n", readUInt16(file)); // TODO, IF 0 Not READ + Typedef

    printf("Methods Count: %u\n", readUInt16(file));

    //printf("Fields: %u\n", readUInt16(file)); // TODO, IF 0 Not READ + Typedef

    printf("Attributes Count: %u\n", readUInt16(file));

    //printf("Fields: %u\n", readUInt16(file)); // TODO, IF 0 Not READ + Typedef


    // Fechar o arquivo
    fclose(file);

    return 0;
}