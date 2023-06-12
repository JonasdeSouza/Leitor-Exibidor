#include "./header.h"

typedef struct ATTRIBUTE_source_file
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 source_file_index;
} ATTRIBUTE_source_file;

typedef struct ATTRIBUTE_exceptions
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table; // [number_of_exceptions]
} ATTRIBUTE_exceptions;

typedef struct classes
{
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} classes;

typedef struct ATTRIBUTE_innerClasses
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    classes **classes_vector;
} ATTRIBUTE_innerClasses;

typedef struct TABLE_exception
{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} TABLE_exception;

typedef struct ATTRIBUTE_constantValue
{
    u2 constantValue_index;
} ATTRIBUTE_constantValue;

typedef struct ATTRIBUTE_code
{
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    TABLE_exception *table;
    u2 attributes_count;
    attribute_info *attributes;
} ATTRIBUTE_code;

typedef struct line_number_tableInfo
{
    u2 start_pc;
    u2 line_number;
} line_number_tableInfo;

typedef struct ATTRIBUTE_deprecated
{
    u2 attribute_name_index;
    u4 attribute_length;
} ATTRIBUTE_deprecated;

typedef struct TABLE_line_number
{
    u2 line_number_table_length;
    line_number_tableInfo *info;
} TABLE_line_number;