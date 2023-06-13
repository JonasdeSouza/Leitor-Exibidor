#include "../include/header.h"

void decodeAccessFlag(u2 flag)
{
    char aux[4];
    sprintf(aux, "%.4x", flag);

    switch (aux[3] - '0')
    {
    case ACC_PUBLIC:
        printf("[public]\n");
        return;
    case ACC_PRIVATE:
        printf("[private]\n");
        return;
    case ACC_PROTECTED:
        printf("[protected]\n");
        return;
    case ACC_STATIC:
        printf("[static]\n");
        return;
    }

    switch (aux[2] - '0')
    {
    case ACC_FINAL:
        printf("[final]\n");
        return;
    case ACC_SYNCHRONIZED:
        printf("[synchronized]\n");
        return;
    case ACC_BRIDGE:
        printf("[bridge]\n");
        return;
    case ACC_VARARGS:
        printf("[varargs]\n");
        return;
    }

    switch (aux[1] - '0')
    {
    case ACC_NATIVE:
        printf("[native]\n");
        return;
    case ACC_ABSTRACT:
        printf("[abstract]\n");
        return;
    case ACC_STRICT:
        printf("[strict]\n");
        return;
    }
    switch (aux[0] - '0')
    {
    case ACC_SYNTHETIC:
        printf("[synthetic]\n");
        return;
    case ACC_ANNOTATION:
        printf("[annotation]\n");
        return;
    case ACC_ENUM:
        printf("[enum]\n");
        return;
    }
}

void getJavaVersion(int version)
{
    switch (version)
    {
    case 64:
        printf("[20]\n");
        break;
    case 63:
        printf("[19]\n");
        break;
    case 62:
        printf("[18]\n");
        break;
    case 61:
        printf("[17]\n");
        break;
    case 60:
        printf("[16]\n");
        break;
    case 59:
        printf("[15]\n");
        break;
    case 58:
        printf("[14]\n");
        break;
    case 57:
        printf("[13]\n");
        break;
    case 56:
        printf("[12]\n");
        break;
    case 55:
        printf("[11]\n");
        break;
    case 54:
        printf("[10]\n");
        break;
    case 53:
        printf("[9]\n");
        break;
    case 52:
        printf("[8]\n");
        break;
    case 51:
        printf("[7]\n");
        break;
    case 50:
        printf("[6]\n");
        break;
    case 49:
        printf("[5]\n");
        break;
    case 48:
        printf("[1.4]\n");
        break;
    case 47:
        printf("[1.3]\n");
        break;
    case 46:
        printf("[1.2]\n");
        break;
    case 45:
        printf("[1.1]\n");
        break;
    default:
        printf("[Versão inválida]\n");
        break;
    }
}

double decodeDoubleInfo(cp_info cp)
{
    uint64_t valor = ((uint64_t)cp.UnionCP.CONSTANT_Double.high_bytes << 32) | (uint64_t)cp.UnionCP.CONSTANT_Double.low_bytes;
    int sinal = ((valor >> 63) == 0) ? 1 : -1;
    int exp = ((valor >> 52) & 0x7ffL);
    long mant = (exp == 0) ? ((valor & 0xfffffffffffffL) << 1) : ((valor & 0xfffffffffffffL) | 0x10000000000000L);

    double retorno = sinal * mant * ((exp - 1075) * (exp - 1075));
    return retorno;
}

uint64_t decodeLongInfo(cp_info cp)
{
    return ((((uint64_t)cp.UnionCP.CONSTANT_Long.high_bytes) << 32) | ((uint64_t)cp.UnionCP.CONSTANT_Long.low_bytes));
}

void printConstantPool(cp_info aux[], int constant_pool_count)
{
    for (int i = 0; i < constant_pool_count - 1; i++)
    {
        switch (aux[i].tag)
        {
        case CONSTANT_Class:
            printf("[%i] Class_info\n\tClass name: cp_info #%d <%s>\n\n", i + 1, aux[i].UnionCP.CONSTANT_Class.name_index, aux[aux[i].UnionCP.CONSTANT_Class.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            aux[i].UnionCP.CONSTANT_Class.name_index;
            break;
        case CONSTANT_Fieldref:
            printf("[%i] Fieldref_info\n\tClass name: cp_info #%d <%s>\n", i + 1, aux[i].UnionCP.CONSTANT_Fieldref.class_index, aux[aux[aux[i].UnionCP.CONSTANT_Fieldref.class_index - 1].UnionCP.CONSTANT_Class.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            printf("\tName and type: cp_info #%d <%s : ", aux[i].UnionCP.CONSTANT_Fieldref.name_and_type_index, aux[aux[aux[i].UnionCP.CONSTANT_Fieldref.name_and_type_index - 1].UnionCP.CONSTANT_Class.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            printf("%s>\n\n", aux[aux[aux[i].UnionCP.CONSTANT_Fieldref.name_and_type_index - 1].UnionCP.CONSTANT_NameAndType.descriptor_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            aux[i].UnionCP.CONSTANT_Fieldref.class_index;
            aux[i].UnionCP.CONSTANT_Fieldref.name_and_type_index;
            break;
        case CONSTANT_Methodref:
            printf("[%i] Methodref_info\n\tClass name: cp_info #%d <%s>\n", i + 1, aux[i].UnionCP.CONSTANT_Methodref.class_index, aux[aux[aux[i].UnionCP.CONSTANT_Methodref.class_index - 1].UnionCP.CONSTANT_Class.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            printf("\tName and type: cp_info #%d <%s : ", aux[i].UnionCP.CONSTANT_Methodref.name_and_type_index, aux[aux[aux[i].UnionCP.CONSTANT_Methodref.name_and_type_index - 1].UnionCP.CONSTANT_Class.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            printf("%s>\n\n", aux[aux[aux[i].UnionCP.CONSTANT_Methodref.name_and_type_index - 1].UnionCP.CONSTANT_NameAndType.descriptor_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            break;
        case CONSTANT_InterfaceMethodref:
            aux[i].UnionCP.CONSTANT_InterfaceMethodref.class_index;
            aux[i].UnionCP.CONSTANT_InterfaceMethodref.name_and_type_index;
            break;
        case CONSTANT_String:
            printf("[%i] String_info\n\tString: cp_info #%d <%s>\n\n", i + 1, aux[i].UnionCP.CONSTANT_String.string_index, aux[aux[i].UnionCP.CONSTANT_String.string_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            aux[i].UnionCP.CONSTANT_String.string_index;
            break;
        case CONSTANT_Integer:
            printf("[%i] Integer_info\n\tInteger: %d", i + 1, aux[i].UnionCP.CONSTANT_Integer.bytes);
            break;
        case CONSTANT_Float:
            printf("[%i] Float_info\n\tFloat: %.2f", i + 1, aux[i].UnionCP.CONSTANT_Float.bytes);
            break;
        case CONSTANT_Long:
            printf("[%i] Long_info\n\tHigh bytes: 0x%x\n", i + 1, aux[i].UnionCP.CONSTANT_Long.high_bytes);
            printf("\tLow bytes: 0x%x\n", i + 1, aux[i].UnionCP.CONSTANT_Long.low_bytes);
            printf("\tLong: %lu\n\n", decodeLongInfo(aux[i]));
            break;
        case CONSTANT_Double:
            printf("[%i] Double_info\n\tHigh bytes: 0x%x\n", i + 1, aux[i].UnionCP.CONSTANT_Double.high_bytes);
            printf("\tLow bytes: 0x%x\n", i + 1, aux[i].UnionCP.CONSTANT_Double.low_bytes);
            double temp = decodeDoubleInfo(aux[i]);
            printf("\tDouble: %.2f\n\n", temp);
            break;
        case CONSTANT_NameAndType:
            printf("[%i] NameAndType_info\n\tName: cp_info #%d <%s>\n", i + 1, aux[i].UnionCP.CONSTANT_NameAndType.name_index, aux[aux[i].UnionCP.CONSTANT_NameAndType.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            printf("\tDescriptor: %d <%s>\n\n", aux[i].UnionCP.CONSTANT_NameAndType.descriptor_index, aux[aux[i].UnionCP.CONSTANT_NameAndType.descriptor_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            break;
        case CONSTANT_Utf8:
            printf("[%i] Utf8_info\n\tLength of byte array: %d \n", i + 1, aux[i].UnionCP.CONSTANT_UTF8.length);
            printf("\tLength of string: %d\n", aux[i].UnionCP.CONSTANT_UTF8.length);
            printf("\tString: %s\n\n", aux[i].UnionCP.CONSTANT_UTF8.bytes);
            break;
        case CONSTANT_MethodHandle:
            printf("[%i] MethodHandle_info\n\tReference kind: ", i + 1);
            printRefValue(aux[i].UnionCP.CONSTANT_MethodHandle.reference_kind);

            //to do
            aux[i].UnionCP.CONSTANT_MethodHandle.reference_index;
            break;
        case CONSTANT_MethodType:
            aux[i].UnionCP.CONSTANT_MethodType.descriptor_index;
            break;
        case CONSTANT_InvokeDynamic:
            printf("[%i] InvokeDynamic_info\n\tName and type: cp_info #%d <%s : ", i + 1, aux[i].UnionCP.CONSTANT_InvokeDynamicInfo.name_and_type_index, aux[aux[aux[i].UnionCP.CONSTANT_InvokeDynamicInfo.name_and_type_index - 1].UnionCP.CONSTANT_NameAndType.name_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            printf("%s>\n", aux[aux[aux[i].UnionCP.CONSTANT_InvokeDynamicInfo.name_and_type_index - 1].UnionCP.CONSTANT_NameAndType.descriptor_index - 1].UnionCP.CONSTANT_UTF8.bytes);
            printf("\tBootstrap method: #%d\n\n", aux[i].UnionCP.CONSTANT_InvokeDynamicInfo.bootstrap_method_attr_index);
            break;
        default:
            printf("(large numeric continued)\n\n");
            break;
        }
    }
    return readConstantPool;
}

void printRefValue(int value)
{
    switch (value)
    {
    case 1:
        printf("REF_getField\n");
        break;
    case 2:
        printf("REF_getStatic\n");
        break;
    case 3:
        printf("REF_putField\n");
        break;
    case 4:
        printf("REF_putStatic\n");
        break;
    case 5:
        printf("REF_invokeVirtual\n");
        break;
    case 6:
        printf("REF_invokeStatic\n");
        break;
    case 7:
        printf("REF_invokeSpecial\n");
        break;
    case 8:
        printf("REF_newInvokeSpecial\n");
        break;
    case 9:
        printf("REF_invokeInterface\n");
        break;
    default:
        printf("Valor inválido\n");
        break;
    }
}