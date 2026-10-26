#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<lexer.h>
#include<ctype.h>

std::vector<Token> line_lexer(const std::string& line, size_t line_no){
	std::vector<Token> out;
	int i = 0;
	int n = line.size();
	while(i < n){
		if(isspace(line[i])){
			i++;
			continue;
		}
		else if(isalpha(line[i]) || line[i] == '_'){
			std::string identifier_name = "";
			while(i < n && (isalnum(line[i]) || line[i] == '_')){
				identifier_name += line[i++];
			}
			if(identifier_name == "int"){
				out.push_back(Token(TokenType::INT));
			}else{
				out.push_back(Token(TokenType::IDENTIFIER, identifier_name));
			}
		}
		else if(isdigit(line[i])){
			double num = 0;
			while(i < n && isdigit(line[i])){
				num = num*10 + (line[i++] - '0');
			}
			out.push_back(Token(TokenType::NUMBER, num));
		}else if(line[i] == '+' || line[i] == '-' || line[i] == '/' || line[i] == '*'){
			out.push_back(Token(TokenType::OPERATOR, line[i++]));
		}
		else if(line[i] == ';'){
			out.push_back(Token(TokenType::SEMI_COLON));
			i++;
		}
		else if(line[i] == '='){
			out.push_back(Token(TokenType::EQUAL));
			i++;
		}
		else{
			throw std::runtime_error("Undefined character found by lexer");
		}
	}
	return out;
}

void traverse_tokens(const std::vector<Token>& tokens){
	for(const Token& tok : tokens){
		switch(tok.type){
			case TokenType::IDENTIFIER:
				std::cout << tok.string_data << "-> " << std::endl;
				break;
			case TokenType::NUMBER:
				std::cout << tok.num_data << "-> " << std::endl;
			case TokenType::OPERATOR:
				std::cout << tok.char_data << "-> " << std::endl;
				break;
			case TokenType::INT:
				std::cout << "INT -> " << std::endl;
				break;
			case TokenType::SEMI_COLON:
				std::cout  << "; ->" << std::endl;
				break;
			case TokenType::EQUAL:
				std::cout << "= ->" << std::endl;
				break;
			default:
				std::cout << "UNKNOWN ->" << std::endl;
				break;
		}
	}	
}
