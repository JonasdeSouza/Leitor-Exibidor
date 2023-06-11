#include <stdio.h>
#include <stdint.h>
#include <winsock.h>
#include <string.h>

// Função para ler um valor de 16 bits em formato big-endian
uint16_t readUInt16(FILE *file)
{
    uint16_t value;
    fread(&value, sizeof(value), 1, file);
    return ntohs(value);
}

// Função para ler um valor de 32 bits em formato big-endian
uint32_t readUInt32(FILE *file)
{
    uint32_t value;
    fread(&value, sizeof(value), 1, file);
    return ntohl(value);
}

char *getMnemonic(uint8_t bytecode);

// Função para imprimir o valor da constante de acordo com o tipo de tag
void printConstantValue(FILE *file, uint8_t tag);

int main()
{
    FILE *file = fopen("MyClass.class", "rb"); // Substitua "Example.class" pelo nome do arquivo .class desejado

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

    // Iterar sobre as entradas do pool de constantes
    for (uint16_t i = 1; i < constantPoolCount; i++)
    {
        printf("Constante %u: ", i);

        uint8_t tag = fgetc(file);
        Mneumonico = getMnemonic(tag);

        printf("Tag: %.8X\n", tag);

        if (tag == 5 || tag == 6) 
        {
            // Entradas do tipo Long (tag 5) e Double (tag 6) ocupam duas posições no pool de constantes
            printf("(Ocupa 2 posicoes)\n");
            ++i;  // Avançar para a próxima posição no pool
        } else 
        {
            printf("(Ocupa 1 posicao)\n");
        }

        if (tag == 7 || tag == 8 || tag == 9 || tag == 10 || tag == 11 || tag == 12 || tag == 15 || tag == 16 || tag == 18) 
        {
            uint16_t index = readUInt16(file);
            printf("Referencia: #%u ", index);
            // Adicione o código aqui para imprimir o valor da constante referenciada
            printf("-> ");
            printConstantValue(file, tag);
        } else {
            // A entrada não faz referência ao pool de constantes, imprimir apenas o valor da constante
            printConstantValue(file, tag);
        }
    }

    // Fechar o arquivo
    fclose(file);

    return 0;
}

void printConstantValue(FILE *file, uint8_t tag)
{
    switch (tag) {
        case 1: {
            // Tag Utf8 - ler o tamanho e o valor da string
            uint16_t length = readUInt16(file);
            char *value = (char *)malloc(length + 1);
            fread(value, sizeof(char), length, file);
            value[length] = '\0';
            printf("Valor: %s\n", value);
            free(value);
            break;
        }
        case 3: {
            // Tag Integer - ler o valor de 32 bits
            uint32_t value = readUInt32(file);
            printf("Valor: %u\n", value);
            break;
        }
        case 4: {
            // Tag Float - ler o valor de 32 bits
            uint32_t value = readUInt32(file);
            float floatValue;
            memcpy(&floatValue, &value, sizeof(float));
            printf("Valor: %f\n", floatValue);
            break;
        }
        case 5: {
            // Tag Long - ler o valor de 64 bits
            uint32_t highBytes = readUInt32(file);
            uint32_t lowBytes = readUInt32(file);
            uint64_t value = ((uint64_t)highBytes << 32) | lowBytes;
            printf("Valor: %llu\n", value);
            break;
        }
        case 6: {
            // Tag Double - ler o valor de 64 bits
            uint32_t highBytes = readUInt32(file);
            uint32_t lowBytes = readUInt32(file);
            uint64_t value = ((uint64_t)highBytes << 32) | lowBytes;
            double doubleValue;
            memcpy(&doubleValue, &value, sizeof(double));
            printf("Valor: %lf\n", doubleValue);
            break;
        }
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 18:
            // Para essas tags, apenas exibir o tipo de constante
            printf("Tipo: %s\n", getMnemonic(tag));
            break;
        default:
            printf("Tipo: %s\n", getMnemonic(tag));
            break;
    }
}

char *getMnemonic(uint8_t bytecode) {
    switch (bytecode) {
        case 0x00:
            return("nop\n");
            break;
        case 0x01:
            return("aconst_null\n");
            break;
        case 0x02:
            return("iconst_m1\n");
            break;
        case 0x03:
            return("iconst_0\n");
            break;
        case 0x04:
            return("iconst_1\n");
            break;
        case 0x05:
            return("iconst_2\n");
            break;
        case 0x06:
            return("iconst_3\n");
            break;
        case 0x07:
            return("iconst_4\n");
            break;
        case 0x08:
            return("iconst_5\n");
            break;
        case 0x09:
            return("lconst_0\n");
            break;
        case 0x0A:
            return("lconst_1\n");
            break;
        case 0x0B:
            return("fconst_0\n");
            break;
        case 0x0C:
            return("fconst_1\n");
            break;
        case 0x0D:
            return("fconst_2\n");
            break;
        case 0x0E:
            return("dconst_0\n");
            break;
        case 0x0F:
            return("dconst_1\n");
            break;
        case 0x10:
            return("bipush\n");
            break;
        case 0x11:
            return("sipush\n");
            break;
        case 0x12:
            return("ldc\n");
            break;
        case 0x13:
            return("ldc_w\n");
            break;
        case 0x14:
            return("ldc2_w\n");
            break;
        case 0x15:
            return("iload\n");
            break;
        case 0x16:
            return("lload\n");
            break;
        case 0x17:
            return("fload\n");
            break;
        case 0x18:
            return("dload\n");
            break;
        case 0x19:
            return("aload\n");
            break;
        case 0x1A:
            return("iload_0\n");
            break;
        case 0x1B:
            return("iload_1\n");
            break;
        case 0x1C:
            return("iload_2\n");
            break;
        case 0x1D:
            return("iload_3\n");
            break;
        case 0x1E:
            return("lload_0\n");
            break;
        case 0x1F:
            return("lload_1\n");
            break;
        case 0x20:
            return("lload_2\n");
            break;
        case 0x21:
            return("lload_3\n");
            break;
        case 0x22:
            return("fload_0\n");
            break;
        case 0x23:
            return("fload_1\n");
            break;
        case 0x24:
            return("fload_2\n");
            break;
        case 0x25:
            return("fload_3\n");
            break;
        case 0x26:
            return("dload_0\n");
            break;
        case 0x27:
            return("dload_1\n");
            break;
        case 0x28:
            return("dload_2\n");
            break;
        case 0x29:
            return("dload_3\n");
            break;
        case 0x2A:
            return("aload_0\n");
            break;
        case 0x2B:
            return("aload_1\n");
            break;
        case 0x2C:
            return("aload_2\n");
            break;
        case 0x2D:
            return("aload_3\n");
            break;
        case 0x2E:
            return("iaload\n");
            break;
        case 0x2F:
            return("laload\n");
            break;
        case 0x30:
            return("faload\n");
            break;
        case 0x31:
            return("daload\n");
            break;
        case 0x32:
            return("aaload\n");
            break;
        case 0x33:
            return("baload\n");
            break;
        case 0x34:
            return("caload\n");
            break;
        case 0x35:
            return("saload\n");
            break;
        case 0x36:
            return("istore\n");
            break;
        case 0x37:
            return("lstore\n");
            break;
        case 0x38:
            return("fstore\n");
            break;
        case 0x39:
            return("dstore\n");
            break;
        case 0x3A:
            return("astore\n");
            break;
        case 0x3B:
            return("istore_0\n");
            break;
        case 0x3C:
            return("istore_1\n");
            break;
        case 0x3D:
            return("istore_2\n");
            break;
        case 0x3E:
            return("istore_3\n");
            break;
        case 0x3F:
            return("lstore_0\n");
            break;
        case 0x40:
            return("lstore_1\n");
            break;
        case 0x41:
            return("lstore_2\n");
            break;
        case 0x42:
            return("lstore_3\n");
            break;
        case 0x43:
            return("fstore_0\n");
            break;
        case 0x44:
            return("fstore_1\n");
            break;
        case 0x45:
            return("fstore_2\n");
            break;
        case 0x46:
            return("fstore_3\n");
            break;
        case 0x47:
            return("dstore_0\n");
            break;
        case 0x48:
            return("dstore_1\n");
            break;
        case 0x49:
            return("dstore_2\n");
            break;
        case 0x4A:
            return("dstore_3\n");
            break;
        case 0x4B:
            return("astore_0\n");
            break;
        case 0x4C:
            return("astore_1\n");
            break;
        case 0x4D:
            return("astore_2\n");
            break;
        case 0x4E:
            return("astore_3\n");
            break;
        case 0x4F:
            return("iastore\n");
            break;
        case 0x50:
            return("lastore\n");
            break;
        case 0x51:
            return("fastore\n");
            break;
        case 0x52:
            return("dastore\n");
            break;
        case 0x53:
            return("aastore\n");
            break;
        case 0x54:
            return("bastore\n");
            break;
        case 0x55:
            return("castore\n");
            break;
        case 0x56:
            return("sastore\n");
            break;
        case 0x57:
            return("pop\n");
            break;
        case 0x58:
            return("pop2\n");
            break;
        case 0x59:
            return("dup\n");
            break;
        case 0x5A:
            return("dup_x1\n");
            break;
        case 0x5B:
            return("dup_x2\n");
            break;
        case 0x5C:
            return("dup2\n");
            break;
        case 0x5D:
            return("dup2_x1\n");
            break;
        case 0x5E:
            return("dup2_x2\n");
            break;
        case 0x5F:
            return("swap\n");
            break;
        case 0x60:
            return("iadd\n");
            break;
        case 0x61:
            return("ladd\n");
            break;
        case 0x62:
            return("fadd\n");
            break;
        case 0x63:
            return("dadd\n");
            break;
        case 0x64:
            return("isub\n");
            break;
        case 0x65:
            return("lsub\n");
            break;
        case 0x66:
            return("fsub\n");
            break;
        case 0x67:
            return("dsub\n");
            break;
        case 0x68:
            return("imul\n");
            break;
        case 0x69:
            return("lmul\n");
            break;
        case 0x6A:
            return("fmul\n");
            break;
        case 0x6B:
            return("dmul\n");
            break;
        case 0x6C:
            return("idiv\n");
            break;
        case 0x6D:
            return("ldiv\n");
            break;
        case 0x6E:
            return("fdiv\n");
            break;
        case 0x6F:
            return("ddiv\n");
            break;
        case 0x70:
            return("irem\n");
            break;
        case 0x71:
            return("lrem\n");
            break;
        case 0x72:
            return("frem\n");
            break;
        case 0x73:
            return("drem\n");
            break;
        case 0x74:
            return("ineg\n");
            break;
        case 0x75:
            return("lneg\n");
            break;
        case 0x76:
            return("fneg\n");
            break;
        case 0x77:
            return("dneg\n");
            break;
        case 0x78:
            return("ishl\n");
            break;
        case 0x79:
            return("lshl\n");
            break;
        case 0x7A:
            return("ishr\n");
            break;
        case 0x7B:
            return("lshr\n");
            break;
        case 0x7C:
            return("iushr\n");
            break;
        case 0x7D:
            return("lushr\n");
            break;
        case 0x7E:
            return("iand\n");
            break;
        case 0x7F:
            return("land\n");
            break;
        case 0x80:
            return("ior\n");
            break;
        case 0x81:
            return("lor\n");
            break;
        case 0x82:
            return("ixor\n");
            break;
        case 0x83:
            return("lxor\n");
            break;
        case 0x84:
            return("iinc\n");
            break;
        case 0x85:
            return("i2l\n");
            break;
        case 0x86:
            return("i2f\n");
            break;
        case 0x87:
            return("i2d\n");
            break;
        case 0x88:
            return("l2i\n");
            break;
        case 0x89:
            return("l2f\n");
            break;
        case 0x8A:
            return("l2d\n");
            break;
        case 0x8B:
            return("f2i\n");
            break;
        case 0x8C:
            return("f2l\n");
            break;
        case 0x8D:
            return("f2d\n");
            break;
        case 0x8E:
            return("d2i\n");
            break;
        case 0x8F:
            return("d2l\n");
            break;
        case 0x90:
            return("d2f\n");
            break;
        case 0x91:
            return("i2b\n");
            break;
        case 0x92:
            return("i2c\n");
            break;
        case 0x93:
            return("i2s\n");
            break;
        case 0x94:
            return("lcmp\n");
            break;
        case 0x95:
            return("fcmpl\n");
            break;
        case 0x96:
            return("fcmpg\n");
            break;
        case 0x97:
            return("dcmpl\n");
            break;
        case 0x98:
            return("dcmpg\n");
            break;
        case 0x99:
            return("ifeq\n");
            break;
        case 0x9A:
            return("ifne\n");
            break;
        case 0x9B:
            return("iflt\n");
            break;
        case 0x9C:
            return("ifge\n");
            break;
        case 0x9D:
            return("ifgt\n");
            break;
        case 0x9E:
            return("ifle\n");
            break;
        case 0x9F:
            return("if_icmpeq\n");
            break;
        case 0xA0:
            return("if_icmpne\n");
            break;
        case 0xA1:
            return("if_icmplt\n");
            break;
        case 0xA2:
            return("if_icmpge\n");
            break;
        case 0xA3:
            return("if_icmpgt\n");
            break;
        case 0xA4:
            return("if_icmple\n");
            break;
        case 0xA5:
            return("if_acmpeq\n");
            break;
        case 0xA6:
            return("if_acmpne\n");
            break;
        case 0xA7:
            return("goto\n");
            break;
        case 0xA8:
            return("jsr\n");
            break;
        case 0xA9:
            return("ret\n");
            break;
        case 0xAA:
            return("tableswitch\n");
            break;
        case 0xAB:
            return("lookupswitch\n");
            break;
        case 0xAC:
            return("ireturn\n");
            break;
        case 0xAD:
            return("lreturn\n");
            break;
        case 0xAE:
            return("freturn\n");
            break;
        case 0xAF:
            return("dreturn\n");
            break;
        case 0xB0:
            return("areturn\n");
            break;
        case 0xB1:
            return("return\n");
            break;
        case 0xB2:
            return("getstatic\n");
            break;
        case 0xB3:
            return("putstatic\n");
            break;
        case 0xB4:
            return("getfield\n");
            break;
        case 0xB5:
            return("putfield\n");
            break;
        case 0xB6:
            return("invokevirtual\n");
            break;
        case 0xB7:
            return("invokespecial\n");
            break;
        case 0xB8:
            return("invokestatic\n");
            break;
        case 0xB9:
            return("invokeinterface\n");
            break;
        case 0xBA:
            return("invokedynamic\n");
            break;
        case 0xBB:
            return("new\n");
            break;
        case 0xBC:
            return("newarray\n");
            break;
        case 0xBD:
            return("anewarray\n");
            break;
        case 0xBE:
            return("arraylength\n");
            break;
        case 0xBF:
            return("athrow\n");
            break;
        case 0xC0:
            return("checkcast\n");
            break;
        case 0xC1:
            return("instanceof\n");
            break;
        case 0xC2:
            return("monitorenter\n");
            break;
        case 0xC3:
            return("monitorexit\n");
            break;
        case 0xC4:
            return("wide\n");
            break;
        case 0xC5:
            return("multianewarray\n");
            break;
        case 0xC6:
            return("ifnull\n");
            break;
        case 0xC7:
            return("ifnonnull\n");
            break;
        case 0xC8:
            return("goto_w\n");
            break;
        case 0xC9:
            return("jsr_w\n");
            break;
        case 0xCA:
            return("breakpoint\n");
            break;
        case 0xFE:
            return("impdep1\n");
            break;
        case 0xFF:
            return("impdep2\n");
            break;
        default:
            return("Bytecode desconhecido\n");
    }
}
