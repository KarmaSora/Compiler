#include <iostream>
#include "parser.tab.hh"
# include "symtab.h"
# include "ast_visitor.h"
# include "visit_IR.h"

extern Node *root;
extern FILE *yyin;
extern int yylineno;
extern int lexical_errors;
extern yy::parser::symbol_type yylex();

enum errCodes
{
	SUCCESS = 0,
	LEXICAL_ERROR = 1,
	SYNTAX_ERROR = 2,
	AST_ERROR = 3,
	SEMANTIC_ERROR = 4,
	SEGMENTATION_FAULT = 139
};

int errCode = errCodes::SUCCESS;

// Handling Syntax Errors
void yy::parser::error(std::string const &err)
{
	if (!lexical_errors)
	{
		std::cerr << "Syntax errors found! See the logs below:" << std::endl;
		std::cerr << "\t@error at line " << yylineno << ". Cannot generate a syntax for this input:" << err.c_str() << std::endl;
		std::cerr << "End of syntax errors!" << std::endl;
		errCode = errCodes::SYNTAX_ERROR;
	}
}

int main(int argc, char **argv)
{
	// Reads from file if a file name is passed as an argument. Otherwise, reads from stdin.
	if (argc > 1)
	{
		if (!(yyin = fopen(argv[1], "r")))
		{
			perror(argv[1]);
			return 1;
		}
	}
	//
	if (USE_LEX_ONLY)
		yylex();
	else
	{
		yy::parser parser;

		bool parseSuccess = !parser.parse();

		if (lexical_errors)
			errCode = errCodes::LEXICAL_ERROR;

		if (parseSuccess && !lexical_errors)
		{
			printf("\nThe compiler successfuly generated a syntax tree for the given input! \n");

			printf("\nPrint Tree:  \n");
			try
			{
				//old:
				root->print_tree();
				root->generate_tree();
				//new:
				// Build the Symbol Table
				SymbolTable symtab;
				ASTVisitor visitor(symtab);
				
				visitor.visit_THE_WHOLE_AST_FOR_THE_SYMTAB(root); //visit all the nodes in the AST for the symtab.
				visitor.visit(root); //visit it again for the semantic errors.

				visitor.printCorrect();

				



				if (symtab.get_error_count() > 0) {
					errCode = errCodes::SEMANTIC_ERROR;
					std::cerr << "\n\nSemantic errors found!\n" 
							  << symtab.get_error_count() 
							  << " errors DETECTED!!! " << std::endl;
				} else {
					std::cerr << "\n\nSymbol table constructed successfully!\n" << std::endl;
					
					// --- IR Generation ---
					IRvisitor ir_visitor;
					CFG* cfg = ir_visitor.generate_IR(root); // Generate CFG from AST
					
					// Serialize IR to a file
    				cfg->serializeToFile("output.ir");

					// Generate DOT FILE for CFG
					cfg->generateDot("cfg.dot");

					// Generate Byte-Code
					ByteCode byteCode;
					generateByteCode(cfg, byteCode);

					// Serialize Byte-Code to a file
					byteCode.serializeToFile("output.bytecode");

					std::cout << "\n\nByte-code successfully generated and serialized to output.bytecode.\n";

					delete cfg; // Free memory
				}
			}
			catch (...)
			{
				errCode = errCodes::AST_ERROR;
			}
		}
	}

	return errCode;
}