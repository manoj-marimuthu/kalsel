#include<iostream>
#include<lexer.h>
#include<vector>
#include<string>

int main(){
	std::cout << "Working" << std::endl;
	std::vector<Token> tokens = line_lexer(std::string("int x = 1 + 3 * 4; "), 1);
	traverse_tokens(tokens);
	return 0;
}
