/* Skeleton and definitions for generating a LALR(1) parser in C++ */
%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

/* Required code included before the parser definition begins */
%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
}

/* Code included in the parser implementation file */
%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;
}

/* Token definitions for the grammar */
/* Tokens represent the smallest units of the language, like operators and parentheses */
%token <std::string> PLUSOP MINUSOP MULTOP LP RP DIVOP ASSIGN 
%token <std::string> AND OR EXCLAMATION_MARK EQUAL LESS_EQUAL LESS_THAN GREATER_EQUAL GREATER_THAN
%token <std::string> SEMICOLON COMMA UNDERSCORE DOT COLON LB RB
%token <std::string> LSQB  RSQB LENGTH 
%token <std::string> PUBLIC CLASS STATIC VOID MAIN RETURN INT BOOLEAN STRING IF ELSE WHILE SYSTEM_OUT_PRINTLN 
%token <std::string> TRUE FALSE THIS NEW CurlyLB CurlyRB

%token <std::string>  IDENTIFIER INTERGER_LITERAL



%token END 0 "end of file"

/* Operator precedence and associativity rules */
/* Used to resolve ambiguities in parsing expressions See https://www.gnu.org/software/bison/manual/bison.html#Precedence-Decl */ 




/*assignment*/
%right ASSIGN

/*Logical */
%left OR    
%left AND 

/*Comparison Operators */
%left EQUAL 
%left LESS_EQUAL LESS_THAN GREATER_EQUAL GREATER_THAN   

/*additive*/
%right PLUSOP MINUSOP EXCLAMATION_MARK

/*multiplicative*/
%left MULTOP DIVOP

/*paranteces*/
%left LP RP

/* Specify types for non-terminals in the grammar */
/* The type specifies the data type of the values associated with these non-terminals */
%type <Node *> root expression factor identifier type //statement reqStatement 

/* Grammar rules section */
/* This section defines the production rules for the language being parsed */
%%
root:       expression {root = $1;}
			|type {root = $1;}
			
			;


/*
reqStatement:  %empty { $$ = "null/nothing";}| reqStatement statement;

statement: CurlyLB reqStatement CurlyRB {
                $$ = new Node("Statement", $2,  yylineno);
                $$->children.push_back();
};
*/

type: INT LB RB {$$ = new Node("TYPE: INT LB RB", "", yylineno);}
	| BOOLEAN {$$ = new Node("TYPE: BOOLEAN", "", yylineno);}
	| INT{$$ = new Node("TYPE: INT", "", yylineno);}
	| identifier ;
	

expression: expression PLUSOP expression {      /*
            Create a subtree that corresponds to the AddExpression
            The root of the subtree is AddExpression
            The childdren of the AddExpression subtree are the left hand side (expression accessed through $1) and right hand side of the expression (expression accessed through $3)
          */
                $$ = new Node("AddExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
                /* printf("r1 "); */
			}
            | expression MINUSOP expression {
                $$ = new Node("SubExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
                /* printf("r2 "); */
			}
            | expression MULTOP expression {
                $$ = new Node("MultExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
                /* printf("r3 "); */
			}
            | expression DIVOP expression {
                $$ = new Node("DivExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
                /* printf("r3 "); */
			}
            | expression ASSIGN expression{
                $$ = new Node("ASSIGN","", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
			}
            | 

            /*Comparesion Operators*/
			expression LESS_THAN expression {
                $$ = new Node("LessThanExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
        	| expression GREATER_THAN expression {
                $$ = new Node("GreaterThanExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
        	| expression EQUAL expression {
                $$ = new Node("EqualExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
        	| expression LESS_EQUAL expression {
                $$ = new Node("LessEqualExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
        	| expression GREATER_EQUAL expression {
                $$ = new Node("GreaterEqualExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
        	|

            /* Logical section */ 
            expression AND expression {
                $$ = new Node("AndExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
        	| expression OR expression {
                $$ = new Node("OrExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }

        	|
            expression EXCLAMATION_MARK  {
                $$ = new Node("NotExpression", "", yylineno);
                $$->children.push_back($1);
            } 

        	| 
        	expression LB expression RB{
                $$ = new Node("Exp left exp right brackets", "", yylineno);
                $$->children.push_back($1); /*expression 1*/
                $$->children.push_back($3); /*expression 2*/

        	}
        	| 
        	expression DOT LENGTH{
                $$ = new Node("DOT.Length", "", yylineno);
                $$->children.push_back($1);
        	}
        	|
            expression DOT identifier expression COMMA expression {
                $$ = new Node("left right brackets", "", yylineno);
                $$->children.push_back($1);
        	}

        	| factor      {$$ = $1; /* printf("r4 ");*/}
        	| identifier  {$$ = $1; /* printf("r4 ");*/}

            |TRUE {  $$ = new Node("TRUE", "", yylineno);}
            |FALSE{  $$ = new Node("FALSE", "", yylineno);}

            |THIS{  $$ = new Node("THIS", "", yylineno);}

            | NEW INT RB expression LB  {
                $$ = new Node("NEW INT RB exp LB", "", yylineno);
                $$->children.push_back($4);
        	}

            |NEW identifier LP RP{
                $$ = new Node("NEW Identifier LP RP", "", yylineno);
                $$->children.push_back($2);
        	}
            | EXCLAMATION_MARK expression
            {
                $$ = new Node("NOT exp ", "", yylineno);
                $$->children.push_back($2);
        	}
                

            ;

identifier: IDENTIFIER{
                $$ = new Node("Identifier", $1, yylineno);

	};


// 

factor:     INTERGER_LITERAL           {  $$ = new Node("Int", $1, yylineno); /* printf("r5 ");  Here we create a leaf node Int. The value of the leaf node is $1 */}
            | LP expression RP { $$ = $2; /* printf("r6 ");  simply return the expression */}
    ;


