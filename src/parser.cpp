#include<parser.h>
#include<lexer.h>
#include<iostream>
#include<stdexcept>
#include<memory>

Token current_token;

static void consume(){
	if(current_token_index + 1 >= tokens.size()){
		current_token = Token(TokenType::EOL);
		return;
	}
	current_token = tokens[++current_token_index];
}

static void consume_semi_colon(){
	while(current_token_index < tokens.size() && current_token.type == TokenType::SEMI_COLON){
		consume();	
	}	
}

// parse functions ,recursive descent, top-down approach)

using AstNodePtr = std::unique_ptr<AstNode>;
static AstNodePtr parseVariableAssignment();

static AstNodePtr parseAtom(){
	if(current_token.type == TokenType::NUMBER){
		auto node = std::make_unique<AstNode>(AstNodeType::NUMBER, current_token.num_data);
		consume();
		return node;
	}else if(current_token.type == TokenType::INT){
		return parseVariableAssignment();
	}else if(current_token.type == TokenType::IDENTIFIER){
		auto node = std::make_unique<AstNode>(AstNodeType::IDENTIFIER, current_token.string_data);
		consume();
		return node;
	}
	else{
		std::cout << (int) current_token.type << std::endl;
		throw std::runtime_error("Unknown token type found by parser. Valid token needed at the beginning \n");
	}
}

static AstNodePtr parseMulDiv(){
	auto lhs = parseAtom();
	while(current_token.type == TokenType::OPERATOR && current_token.type != TokenType::SEMI_COLON &&
		(current_token.char_data == '*' || current_token.char_data == '/')
	     )
		{
			auto op_node = std::make_unique<AstNode>(AstNodeType::OPERATOR, current_token.char_data);
			consume();
			auto rhs = parseAtom();
			op_node->left = std::move(lhs);
			op_node->right  = std::move(rhs);
			lhs = std::move(op_node);
		}
	consume_semi_colon();
	return lhs;
}

static AstNodePtr parseAddSub(){
	auto lhs = parseMulDiv();
	while(current_token.type == TokenType::OPERATOR &&
 		(current_token.char_data == '+' || current_token.char_data == '-') &&
		current_token.type != TokenType::SEMI_COLON
	     ){	
			auto op_node = std::make_unique<AstNode>(AstNodeType::OPERATOR, current_token.char_data);
			consume();
			auto rhs = parseMulDiv();
			op_node->left = std::move(lhs);
			op_node->right  = std::move(rhs);
			lhs = std::move(op_node);
		}
	consume_semi_colon();
	return lhs;
}

static AstNodePtr parseVariableAssignment(){
	if(current_token.type == TokenType::INT){
		consume();
		if(current_token.type == TokenType::IDENTIFIER){
			const std::string variable_name = current_token.string_data;
		        consume();
			if(current_token.type == TokenType::EQUAL){
		 		consume();
				auto node = std::make_unique<AstNode>(AstNodeType::ASSIGNMENT);
				node->left = std::make_unique<AstNode>(AstNodeType::STRING, variable_name);
				node->right = parseAddSub();
				if(current_token.type == TokenType::SEMI_COLON){
					consume_semi_colon();
				}else if(current_token.type == TokenType::EOL){
					// do nothing, return the so parsed AST
				}
				else{
					throw std::runtime_error("Expected ';': after variable assignment \n");
				}
				return node;
			}else{
				throw std::runtime_error("Expected '=': after variable name \n");
				
			}
		}else{
			std::cout << (int) current_token.type << std::endl;
			throw std::runtime_error("Expected Identifier: after 'int', use a valid variable name \n");
		}
	}else{
		return nullptr;
	}
}

AstNodePtr Parse(){
	current_token = tokens[0];
	if(current_token.type == TokenType::INT){
		return parseVariableAssignment();
	}else {
		return parseAddSub();
	//	throw std::runtime_error("Unknown token type found by parser. Valid token type needed \n");
	}	
	return nullptr;
}
