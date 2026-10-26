#pragma once

#include<string>
#include<vector>

enum class TokenType{
	NUMBER,
	IDENTIFIER,
	SEMI_COLON,
	EQUAL,
	INT,
	OPERATOR
};

class Token{
	public:
		TokenType type;
		std::string string_data{};
		double num_data{};
		char char_data{};
		Token(TokenType type):type(type){}
		Token(TokenType type, std::string string_data):type(type),string_data(string_data){}
		Token(TokenType type, double num_data):type(type),num_data(num_data){}
		Token(TokenType type, char char_data):type(type),char_data(char_data){}
};

std::vector<Token> line_lexer(const std::string& line, size_t line_no);
void traverse_tokens(const std::vector<Token>& tokens);
