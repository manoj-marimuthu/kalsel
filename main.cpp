#include<iostream>
#include<lexer.h>
#include<parser.h>
#include<ir.h>
#include<symbol_table.h>
#include<code_gen.h>
#include<vector>
#include<string>
#include<fstream>
#include<cstdlib>

std::vector<Token> tokens{};
size_t current_token_index = 0;

void reset_states(){
	ir_instructions.clear();
	tokens.clear();
	current_token_index = 0;
}

static void COMPILE(std::ifstream& file){
	reset_states();
	std::string line;
	size_t line_no = 0;
	while(std::getline(file,line)){
		line_lexer(line, line_no++);
	}
	tokens.push_back(Token(TokenType::END_OF_FILE));
	Parse();
	for(const auto& ast_node: ast_nodes){
		generate_ir(ast_node.get());
	}
	std::ofstream out_file("asm-modules/program.asm",std::ios::out | std::ios::trunc);
	code_gen(out_file);
	std::cout << "COMPILATION to x86 asm suceeded" << std::endl;
	int result = std::system("nasm -f elf64 asm-modules/program.asm -o build/program.o");
	if(result != 0) std::runtime_error("KALSEL failed to produce object files for target file \n");
	result = std::system("nasm -f elf64 asm-modules/print.asm -o build/print.o");
	if(result != 0) std::runtime_error("KALSEL failed to produce object files for target file \n");
	result = std::system("ld build/program.o build/print.o -o test");
	if(result != 0) std::runtime_error("KALSEL failed to produce object files for target file \n");
	std::cout << "COMPILATION to object files and linking succeeded" << std::endl;

}

int main(int argc, char* argv[]){
	std::ifstream file("test.kal");
	if(!file.is_open()){
		throw std::runtime_error("Could' nt open file for compilation \n");
	}
	COMPILE(file);
	return 0;
}
