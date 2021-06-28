//////////////////////////////////////////////////////////////////////////
//Painter Engine Interpreter
//code by DBinary, matrixcascade@gmail.com
//QQ:477608346,tel-18959060883
//include script compiler & parser & AST

#ifndef _PX_SCRIPT_TRANSLATOR_H
#define _PX_SCRIPT_TRANSLATOR_H
#include "PX_ScriptCore.h"

#define PX_SCRIPT_TRANSLATOR_FLOAT_PRECISION 6
#define PX_SCRIPT_OPCODE_LEVEL_BOTTOM 255
#define PX_SCRIPT_FUNCTION_MAX_PARAM 16
#define PX_SCRIPT_FUNCTION_NAME_MAX_LEN 48



typedef enum
{
	PX_SCRIPT_PARSER_VAR_TYPE_INT,
	PX_SCRIPT_PARSER_VAR_TYPE_STRING,
	PX_SCRIPT_PARSER_VAR_TYPE_FLOAT,
	PX_SCRIPT_PARSER_VAR_TYPE_MEMORY,
	PX_SCRIPT_PARSER_VAR_TYPE_VOID,
	PX_SCRIPT_PARSER_VAR_TYPE_STRUCT,

	PX_SCRIPT_PARSER_VAR_TYPE_INT_ARRAY,
	PX_SCRIPT_PARSER_VAR_TYPE_STRING_ARRAY,
	PX_SCRIPT_PARSER_VAR_TYPE_FLOAT_ARRAY,
	PX_SCRIPT_PARSER_VAR_TYPE_MEMORY_ARRAY,
	PX_SCRIPT_PARSER_VAR_TYPE_SET_ARRAY,

	PX_SCRIPT_PARSER_VAR_TYPE_INT_PTR,
	PX_SCRIPT_PARSER_VAR_TYPE_STRING_PTR,
	PX_SCRIPT_PARSER_VAR_TYPE_FLOAT_PTR,
	PX_SCRIPT_PARSER_VAR_TYPE_MEMORY_PTR,
	PX_SCRIPT_PARSER_VAR_TYPE_STRUCT_PTR,

}PX_SCRIPT_PARSER_VAR_TYPE;

typedef enum
{
	////
	PX_SCRIPT_TRANSLATOR_EXPRESSION_TOKEN, 
	////

	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_FUNCTION,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_ADD,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_INC,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_POSITIVE,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_SUB,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_DEC,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_NEGATIVE,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_MUL,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_DIV,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_AND,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_OR,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_NOT,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_XOR,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_INV,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_MOD,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_SHL,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_SHR,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_DOT,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_COMMA,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LBRACKETBEGIN,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LBRACKETEND,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_MBRACKETBEGIN,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_MBRACKETEND,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LARGE,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LARGEEUQ,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LESS,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LESSEQU,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_UNEQU,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_EQU,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LGEQU,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LAND,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_LOR,
	//pointer
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_PTR, //*
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_ADR, //&
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_OFT, //->

	//transfer
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_INT,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_FLOAT,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_STRING,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_MEMORY,

	//key word
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_STRLEN,
	PX_SCRIPT_TRANSLATOR_EXPRESSION_OP_MEMLEN,
}PX_SCRIPT_TRANSLATOR_EXPRESSION_TYPE;

typedef enum
{
	PX_SCRIPT_AST_OPCODE_TYPE_ADD,
	PX_SCRIPT_AST_OPCODE_TYPE_INC,
	PX_SCRIPT_AST_OPCODE_TYPE_POSITIVE,
	PX_SCRIPT_AST_OPCODE_TYPE_SUB,
	PX_SCRIPT_AST_OPCODE_TYPE_DEC,
	PX_SCRIPT_AST_OPCODE_TYPE_NEGATIVE,
	PX_SCRIPT_AST_OPCODE_TYPE_MUL,
	PX_SCRIPT_AST_OPCODE_TYPE_DIV,
	PX_SCRIPT_AST_OPCODE_TYPE_AND,
	PX_SCRIPT_AST_OPCODE_TYPE_OR,
	PX_SCRIPT_AST_OPCODE_TYPE_NOT,
	PX_SCRIPT_AST_OPCODE_TYPE_XOR,
	PX_SCRIPT_AST_OPCODE_TYPE_INV,
	PX_SCRIPT_AST_OPCODE_TYPE_MOD,
	PX_SCRIPT_AST_OPCODE_TYPE_SHL,
	PX_SCRIPT_AST_OPCODE_TYPE_SHR,
	
	PX_SCRIPT_AST_OPCODE_TYPE_COMMA,
	PX_SCRIPT_AST_OPCODE_TYPE_LARGE,
	PX_SCRIPT_AST_OPCODE_TYPE_LARGEEQU,
	PX_SCRIPT_AST_OPCODE_TYPE_LESS,
	PX_SCRIPT_AST_OPCODE_TYPE_LESSEQU,
	PX_SCRIPT_AST_OPCODE_TYPE_UNEQU,
	PX_SCRIPT_AST_OPCODE_TYPE_EQU,
	PX_SCRIPT_AST_OPCODE_TYPE_LGEQU,
	PX_SCRIPT_AST_OPCODE_TYPE_LAND,
	PX_SCRIPT_AST_OPCODE_TYPE_LOR,
	//pointer
	PX_SCRIPT_AST_OPCODE_TYPE_PTR, //*
	PX_SCRIPT_AST_OPCODE_TYPE_ADR, //&
	PX_SCRIPT_AST_OPCODE_TYPE_DOT, //.
	PX_SCRIPT_AST_OPCODE_TYPE_IDX, //[]
	PX_SCRIPT_AST_OPCODE_TYPE_OFT, //->
	//transfer
	PX_SCRIPT_AST_OPCODE_TYPE_INT,
	PX_SCRIPT_AST_OPCODE_TYPE_STRING,
	PX_SCRIPT_AST_OPCODE_TYPE_FLOAT,
	PX_SCRIPT_AST_OPCODE_TYPE_MEMORY,
	PX_SCRIPT_AST_OPCODE_TYPE_STRLEN,
	PX_SCRIPT_AST_OPCODE_TYPE_MEMLEN,
	PX_SCRIPT_AST_OPCODE_TYPE_SIN,
	PX_SCRIPT_AST_OPCODE_TYPE_COS,
}PX_SCRIPT_AST_OPCODE_TYPE;

typedef enum
{
	PX_SCRIPT_AST_OPERAND_TYPE_VOID,

	PX_SCRIPT_AST_OPERAND_TYPE_INT,    //int var //region G/L/
	PX_SCRIPT_AST_OPERAND_TYPE_FLOAT,  //float var
	PX_SCRIPT_AST_OPERAND_TYPE_STRING, //string var
	PX_SCRIPT_AST_OPERAND_TYPE_MEMORY,//memory var
	PX_SCRIPT_AST_OPERAND_TYPE_STRUCT,   //set xx var

	PX_SCRIPT_AST_OPERAND_TYPE_INT_CONST,//int const
	PX_SCRIPT_AST_OPERAND_TYPE_FLOAT_CONST,//float const
	PX_SCRIPT_AST_OPERAND_TYPE_STRING_CONST,//string const
	PX_SCRIPT_AST_OPERAND_TYPE_MEMORY_CONST,//memory const

	PX_SCRIPT_AST_OPERAND_TYPE_INT_PTR, //int var[x]
	PX_SCRIPT_AST_OPERAND_TYPE_FLOAT_PTR,//float var[x]
	PX_SCRIPT_AST_OPERAND_TYPE_STRING_PTR,//string var[x]
	PX_SCRIPT_AST_OPERAND_TYPE_MEMORY_PTR,//memory var[x]
	PX_SCRIPT_AST_OPERAND_TYPE_STRUCT_PTR,//set xx var[x]

	PX_SCRIPT_AST_OPERAND_TYPE_INT_PTR_CONST, //int var[] 
	PX_SCRIPT_AST_OPERAND_TYPE_FLOAT_PTR_CONST,//float var[]
	PX_SCRIPT_AST_OPERAND_TYPE_STRING_PTR_CONST,//string var[]
	PX_SCRIPT_AST_OPERAND_TYPE_MEMORY_PTR_CONST,//memory var[]
	PX_SCRIPT_AST_OPERAND_TYPE_SET_PTR_CONST,//set xx var[]

	PX_SCRIPT_AST_OPERAND_TYPE_STRING_IDX,
	PX_SCRIPT_AST_OPERAND_TYPE_MEMORY_IDX,
}PX_SCRIPT_AST_OPERAND_TYPE;

typedef enum
{
	PX_SCRIPT_TRANSLATOR_OP_CLASS_SINGLE,
	PX_SCRIPT_TRANSLATOR_OP_CLASS_BINARY,
	PX_SCRIPT_TRANSLATOR_OP_CLASS_CONTAINER,
	PX_SCRIPT_TRANSLATOR_OP_CLASS_CONST,
	PX_SCRIPT_TRANSLATOR_OP_CLASS_VAR,
	PX_SCRIPT_TRANSLATOR_OP_CLASS_FUNC,
	PX_SCRIPT_TRANSLATOR_OP_CLASS_UNDEFINED,
}PX_SCRIPT_TRANSLATOR_OP_CLASS;


typedef enum
{
	PX_SCRIPT_TRANSLATOR_FUNCTION_TYPE_HOST,
	PX_SCRIPT_TRANSLATOR_FUNCTION_TYPE_EXPORT,
	PX_SCRIPT_TRANSLATOR_FUNCTION_TYPE_CUSTOM,
}PX_SCRIPT_TRANSLATOR_FUNCTION_TYPE;

typedef enum
{
	PX_SCRIPT_VARIABLE_REGION_LOCAL,
	PX_SCRIPT_VARIABLE_REGION_GLOBAL,
	PX_SCRIPT_VARIABLE_REGION_POP,
}PX_SCRIPT_VARIABLE_REGION;

#define PX_SCRIPT_TRANSLATOR_KEYWORD_RUNTIME "#RUNTIME"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_STACK "STACK"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_THREAD "THREAD"

#define PX_SCRIPT_TRANSLATOR_KEYWORD_VAR_INT "INT"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_VAR_STRING "STRING"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_VAR_MEMORY "MEMORY"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_VAR_FLOAT "FLOAT"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_VAR_VOID "VOID"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_VAR_STRUCT "STRUCT"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_RETURN "RETURN"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_VAR_SIZEOF "SIZEOF"

#define PX_SCRIPT_TRANSLATOR_KEYWORD_IF "IF"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_ELSE "ELSE"

#define PX_SCRIPT_TRANSLATOR_KEYWORD_WHILE "WHILE"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_FOR "FOR"

#define PX_SCRIPT_TRANSLATOR_KEYWORD_ASM "_ASM"

#define PX_SCRIPT_TRANSLATOR_KEYWORD_BREAK "BREAK"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_CONTINUE "CONTINUE"

#define PX_SCRIPT_TRANSLATOR_KEYWORD_SWITCH "SWITCH"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_CASE "CASE"

#define PX_SCRIPT_TRANSLATOR_KEYWORD_HOST "HOST"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_FUNCTION "FUNCTION"
#define PX_SCRIPT_TRANSLATOR_KEYWORD_EXPORT "EXPORT"



typedef struct  
{
	px_string name;
	px_string code;
	px_bool	bInclude;
}PX_SCRIPT_CODE;

typedef struct
{
	px_string Name;
	px_vector members;
	px_int size;
}PX_SCRIPT_STRUCT;

typedef struct  
{
	px_string Mnemonic;
	PX_SCRIPT_PARSER_VAR_TYPE type;
	px_int layer;
	px_int setIndex;
	px_int BeginIndex;
	px_int size;
	px_bool bParam;
	px_bool bInitialized;
	px_string GlobalInitializeValue;
}PX_SCRIPT_VARIABLES;

typedef struct
{
	px_int offset;
	PX_SCRIPT_VARIABLES defvar;
}PX_SCRIPT_SETMEMBER;

typedef struct  
{
	px_memorypool	*mp;
	px_vector		codeLibraries;//PX_SCRIPT_CODE vector
}PX_SCRIPT_LIBRARY;


typedef struct
{
	PX_SCRIPT_AST_OPCODE_TYPE operandType;
	px_int level;
}PX_SCRIPT_AST_OPCODE;

typedef struct
{
	PX_SCRIPT_AST_OPERAND_TYPE operandType;
	PX_SCRIPT_VARIABLE_REGION region;
	PX_SCRIPT_STRUCT *pSet;
	union
	{
		px_int	_oft;
		px_int  _int;
		px_float _float;
		px_char *_contaniner;
	};
	px_bool bAtomPopIndex;
	px_int AtomIndex;
}PX_SCRIPT_AST_OPERAND;




typedef struct  
{
	PX_SCRIPT_TRANSLATOR_EXPRESSION_TYPE type;
	PX_SCRIPT_TRANSLATOR_OP_CLASS opclass;
	px_int oplevel;
	px_string code;
	
}PX_SCRIPT_EXPR_STREAM;


typedef struct
{
	PX_SCRIPT_TRANSLATOR_FUNCTION_TYPE type;
	px_char name[48];
	PX_SCRIPT_VARIABLES parameters[PX_SCRIPT_FUNCTION_MAX_PARAM];
	px_int parametersCount;
	px_int parametersSize;

	PX_SCRIPT_PARSER_VAR_TYPE retType;
	px_int retSetIndex;
}PX_SCRIPT_FUNCTION;



typedef struct
{
	px_char name[48];
}PX_SCRIPT_AST_STRUCTURE_FUNCTION;

typedef struct
{
	px_int ifflag;
    px_int elseflag;
	px_bool oneline_expr;
}PX_SCRIPT_AST_STRUCTURE_IF;

typedef struct
{
	px_int elseflag;
	px_bool oneline_expr;
}PX_SCRIPT_AST_STRUCTURE_ELSE;

typedef struct
{
	px_int loopflag;
	
	px_int endflag;
	px_bool oneline_expr;
}PX_SCRIPT_AST_STRUCTURE_WHILE;

typedef struct
{
	px_int additionFlag;
	px_int conditionFlag;
	px_int endFlag;
	px_bool oneline_expr;
}PX_SCRIPT_AST_STRUCTURE_FOR;

typedef struct
{
	px_int endFlag;
	px_bool oneline_expr;
	PX_SCRIPT_AST_OPERAND OriginOperand;
}PX_SCRIPT_AST_STRUCTURE_COMPARE;

typedef struct
{
	px_int endFlag;
	px_bool oneline_expr;
}PX_SCRIPT_AST_STRUCTURE_WITH;


typedef enum
{
	PX_SCRIPT_AST_STRUCTURE_TYPE_FUNCTION,
	PX_SCRIPT_AST_STRUCTURE_TYPE_IF,
	PX_SCRIPT_AST_STRUCTURE_TYPE_ELSE,
	PX_SCRIPT_AST_STRUCTURE_TYPE_WHILE,
	PX_SCRIPT_AST_STRUCTURE_TYPE_FOR,
	PX_SCRIPT_AST_STRUCTURE_TYPE_SWITCH,
	PX_SCRIPT_AST_STRUCTURE_TYPE_CASE
}PX_SCRIPT_AST_STRUCTURE_TYPE;

typedef struct
{
	PX_SCRIPT_AST_STRUCTURE_TYPE type;
	union
	{
		PX_SCRIPT_AST_STRUCTURE_FUNCTION _func;
		PX_SCRIPT_AST_STRUCTURE_IF _if;
		PX_SCRIPT_AST_STRUCTURE_ELSE _else;
		PX_SCRIPT_AST_STRUCTURE_WHILE _while;
		PX_SCRIPT_AST_STRUCTURE_FOR _for;
		PX_SCRIPT_AST_STRUCTURE_COMPARE _compare;
		PX_SCRIPT_AST_STRUCTURE_WITH _with;
	};
}PX_SCRIPT_AST_STRUCTURE;

typedef enum
{
	PX_SCRIPT_AST_SET_TREE_NODE_TYPE_STRUCT,
	PX_SCRIPT_AST_SET_TREE_NODE_TYPE_MEMBER,
}PX_SCRIPT_AST_SET_TREE_NODE_TYPE;




typedef struct  
{
	px_memorypool	*mp;
	px_string bootCode;
	px_string code;
	px_lexer  lexer;
	px_bool functionInside;
	px_bool functionReturn;
	px_int	functionlable;
	px_int  functionguider;
	PX_SCRIPT_FUNCTION currentFunc;
	px_vector v_struct;
	px_vector v_functions;
	px_vector v_variablesGlobalTable;
	px_vector v_variablesStackTable;
	px_int    currentAllocStackSize;
	px_vector v_astStructure;
	px_int _jFlag;
}PX_SCRIPT_Analysis;

px_bool PX_ScriptCompilerInitialize(PX_SCRIPT_LIBRARY *lib,px_memorypool *mp);
px_bool PX_ScriptCompilerLoad(PX_SCRIPT_LIBRARY *lib,const px_char *code);
px_bool PX_ScriptCompilerCompile(PX_SCRIPT_LIBRARY *lib,const px_char *name,px_string *ASM,px_int StackSize);
px_void PX_ScriptCompilerFree(PX_SCRIPT_LIBRARY *lib);
px_char *PX_ScriptCompilerError(void);
px_bool PX_ScriptInterpreterExpression(PX_SCRIPT_Analysis *analysis,px_char *expr,px_string *out,PX_SCRIPT_AST_OPERAND *retOperand);
#endif
