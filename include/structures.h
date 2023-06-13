#ifndef STRUCTURES_H
#define STRUCTURES_H

// Definição para tamanhos estipulados
typedef uint8_t u1;	 // uint8_t       1 byte  (8 bits)
typedef uint16_t u2; // uint16_t      2 bytes (16bits)
typedef uint32_t u4; // uint32_t      4 bytes (32bits)

// _info
typedef struct attribute_info {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 * info;
}attribute_info;

typedef struct field_info
{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info * attributes;
} field_info;

typedef struct method_info{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info * attributes;
}method_info;

typedef struct cp_info
{
	u1 tag;
	union
	{
		struct CONSTANT_Class
		{
			u2 name_index;
		} CONSTANT_Class;

		struct CONSTANT_Fieldref
		{
			u2 class_index;
			u2 name_and_type_index;
		} CONSTANT_Fieldref;

		struct CONSTANT_Methodref
		{
			u2 class_index;
			u2 name_and_type_index;
		} CONSTANT_Methodref;

		struct CONSTANT_InterfaceMethodref
		{
			u2 class_index;
			u2 name_and_type_index;
		} CONSTANT_InterfaceMethodref;

		struct CONSTANT_Integer
		{
			u4 bytes;
		} CONSTANT_Integer;

		struct CONSTANT_Long
		{
			u4 high_bytes;
			u4 low_bytes;
		} CONSTANT_Long;

		struct CONSTANT_Double
		{
			u4 high_bytes;
			u4 low_bytes;
		} CONSTANT_Double;

		struct CONSTANT_Float
		{
			u4 bytes;
		} CONSTANT_Float;

		struct CONSTANT_String
		{
			u2 string_index;
		} CONSTANT_String;

		struct CONSTANT_NameAndType
		{
			u2 name_index;
			u2 descriptor_index;
		} CONSTANT_NameAndType;

		struct CONSTANT_MethodHandle
		{
			u1 reference_kind;
			u2 reference_index;
		} CONSTANT_MethodHandle;

		struct CONSTANT_MethodType
		{
			u2 descriptor_index;
		} CONSTANT_MethodType;

		struct CONSTANT_InvokeDynamicInfo
		{
			u2 bootstrap_method_attr_index;
			u2 name_and_type_index;
		} CONSTANT_InvokeDynamicInfo;

		struct CONSTANT_UTF8
		{
			u2 length;
			u1 *bytes;
		} CONSTANT_UTF8;

	} UnionCP;

} cp_info;

#endif // STRUCTURES_H