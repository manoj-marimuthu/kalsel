#include<iostream>
#include<lexer.h>
#include<parser.h>
#include<ir.h>
#include<symbol_table.h>
#include<vector>
#include<string>

std::vector<Token> tokens{};
size_t current_token_index = 0;

void reset_states(){
	ir_instructions.clear();
	tokens.clear();
	current_token_index = 0;
}

static void compile(std::string line){
	reset_states();
	std::cout << "--------------------------" << std::endl;
	tokens = line_lexer(line, 1);
	auto ast_root = Parse();
	generate_ir(ast_root);
	traverse_ir_instructions();
	std::cout << "--------------------------" << std::endl;
}

int main(){
	compile(std::string("int x = 1 + 2 * 3;"));
	compile(std::string("int y = 1 / x * 20;"));
	compile(std::string("int z = 1 + x + y - 5;"));
	for(const auto& pair : symbol_table){
		std::cout << pair.first << " = " << pair.second << std::endl;
	}
	return 0;
}
