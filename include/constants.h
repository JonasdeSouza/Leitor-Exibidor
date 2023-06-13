#ifndef CONSTANTS_H
#define CONSTANTS_H

enum access_flags{
	ACC_PUBLIC = 1,				    
	ACC_PRIVATE = 2,			    
	ACC_PROTECTED = 4,			    
	ACC_STATIC = 8,				    
	ACC_FINAL = 16,				    
	ACC_SYNCHRONIZED = 32,		    
	ACC_BRIDGE = 64,			    
	ACC_VARARGS = 128,			    
	ACC_NATIVE = 256,			    
	ACC_ABSTRACT = 1024,		    
	ACC_STRICT = 2048,			    
	ACC_SYNTHETIC = 4096,		    
	ACC_ENUM = 16384,               
	ACC_VOLATILE = 64,			    
	ACC_TRANSIENT = 128,
	ACC_ANNOTATION = 8192            
};

enum constant_pool_tags
{
	CONSTANT_Utf8 = 1,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_Long = 5,
	CONSTANT_Double = 6,
	CONSTANT_Class = 7,
	CONSTANT_String = 8,
	CONSTANT_Fieldref = 9,
	CONSTANT_Methodref = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_NameAndType = 12,
	CONSTANT_MethodHandle = 15,
	CONSTANT_MethodType = 16,
	CONSTANT_InvokeDynamic = 18
};

#endif