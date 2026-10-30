#ifndef IR_H
#define IR_H

#include<string>
#include<memory>
#include<vector>
#include<parser.h>

enum class Ir_InstructionType{
	MOV,
	MOV_FROM_ST,
	ADD,
	MUL,
	SUB,
	DIV,
	NULL_NODE
};

class Ir_Instruction{
	public:
		Ir_InstructionType type;
		std::string ir_instruction_string{};
		size_t temp_id{};
		size_t offset{};
		Ir_Instruction(Ir_InstructionType type):type(type){}
		Ir_Instruction(Ir_InstructionType type, std::string ir_instruction_string, size_t temp_id):
			type(type), ir_instruction_string(ir_instruction_string), temp_id(temp_id){}

};

extern size_t current_temp_id;
extern std::vector<Ir_Instruction> ir_instructions;
size_t generate_ir(const std::unique_ptr<AstNode>& node);
void traverse_ir_instructions();
#endif
