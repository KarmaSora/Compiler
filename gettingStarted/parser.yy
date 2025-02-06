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
%token <std::string> PLUSOP MINUSOP MULTOP DIVOP ASSIGN 
%token <std::string> AND OR EXCLAMATION_MARK EQUAL LESS_EQUAL LESS_THAN GREATER_EQUAL GREATER_THAN
%token <std::string> SEMICOLON COMMA UNDERSCORE DOT COLON LENGTH 
%token <std::string> LB RB                /*Square Bracets   [  ]   */
%token <std::string> LP RP                /*Parantheses   (  )   */
%token <std::string> CurlyLB CurlyRB      /*Curly Bracets   {   }   */



%token <std::string> PUBLIC CLASS STATIC VOID MAIN RETURN INT BOOLEAN STRING IF ELSE WHILE SYSTEM_OUT_PRINTLN 
%token <std::string> TRUE FALSE THIS NEW 

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
%type <Node *> root expression factor identifier type statement reqStatement 
%type <Node *> GOAL MainClass ClassDeclaration reqClassDeclaration VarDeclaration reqVarDeclaration MethodDeclaration 
%type <Node *> reqMethodDeclaration varDecOrSTMT ParamList Parameters arguments argumentsList



/* Grammar rules section */
/* This section defines the production rules for the language being parsed */
%%
root:       
        GOAL{root = $1;}
        ;

GOAL : MainClass reqClassDeclaration END{  
            $$ = new Node("GOALLLLL", "", yylineno);
            $$->children.push_back($1);
            $$->children.push_back($2);}
    ;

MainClass: PUBLIC CLASS identifier CurlyLB PUBLIC STATIC 
            VOID MAIN LP STRING LB RB identifier RP CurlyLB statement reqStatement CurlyRB CurlyRB  {
                $$ = new Node("MainClass", "", yylineno);
                $$->children.push_back($3);
                $$->children.push_back($13);
                $$->children.push_back($16);
                $$->children.push_back($17);                
            }
        ;

ClassDeclaration: CLASS identifier CurlyLB reqVarDeclaration reqMethodDeclaration CurlyRB
            {
                $$ = new Node("ClassDeclaration", "", yylineno);
                $$->children.push_back($2);
                $$->children.push_back($4);
                $$->children.push_back($5);
            }
            
        ;
reqClassDeclaration: ClassDeclaration  {
                $$ = new Node("ClassDeclaration", "", yylineno);
                $$->children.push_back($1);
                }
                |
                reqClassDeclaration ClassDeclaration {
                $$ = new Node("reqClassDeclaration ClassDeclaration", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($2);
                }
          
        
        ;


VarDeclaration: type identifier SEMICOLON {
                $$ = new Node("VarDeclaration", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($2);
            }
        ;
reqVarDeclaration: %empty {
      $$ = new Node("EMPTY reqVarDeclaration", "", yylineno);
    }
    |
     reqVarDeclaration VarDeclaration {
        $$ = new Node("VarDeclaration VarDeclaration", "", yylineno);
        $$->children.push_back($1);
        $$->children.push_back($2);
    }
    ;

MethodDeclaration: PUBLIC type identifier LP 
                    Parameters
                    RP
                    CurlyLB 
                    varDecOrSTMT
                    RETURN expression SEMICOLON CurlyRB
                   {
                $$ = new Node("MethodDeclaration", "", yylineno);
                $$->children.push_back($2);
                $$->children.push_back($3);
                $$->children.push_back($5);
                $$->children.push_back($8);
                $$->children.push_back($10);
            }
        ;

/* func(), func( int a, string b, bool c ) */
Parameters:%empty {
      $$ = new Node("EmptyParameters", "", yylineno);
    } | ParamList {
        $$ = new Node("ParamList", "", yylineno);
        $$->children.push_back($1);
        
        }
     ;

ParamList: type identifier {
        $$ = new Node("ParamList, Type ID", "", yylineno);
        $$->children.push_back($1);
        $$->children.push_back($2);
    }
    | ParamList COMMA type identifier
    {
        $$ = new Node("ParamList COMMA type identifier", "", yylineno);
        $$->children.push_back($1);
        $$->children.push_back($3);
        $$->children.push_back($4);
    }
    ;

varDecOrSTMT : %empty {
      $$ = new Node("EMPTY varDecOrSTMT", "", yylineno);
    }
    |varDecOrSTMT statement {
        $$ = new Node("varDecOrSTMT statement", "", yylineno);
        $$->children.push_back($1);
        $$->children.push_back($2);
    }
    |varDecOrSTMT VarDeclaration {
        $$ = new Node("varDecOrSTMT VarDeclaration", "", yylineno);
        $$->children.push_back($1);
        $$->children.push_back($2);
    }
    ;


reqMethodDeclaration: %empty {
      $$ = new Node("EMPTY reqMethodDeclaration", "", yylineno);
    }
    |
     reqMethodDeclaration MethodDeclaration {
      $$ = new Node("reqMethodDeclaration MethodDeclaration", "", yylineno);
      $$->children.push_back($1);
      $$->children.push_back($2);
    }
    ;


reqStatement: %empty {
      $$ = new Node("EMPTY reqStatement", "", yylineno);
    }
    | reqStatement statement {
      $$ = new Node("reqStatement statement", "", yylineno);
      $$->children.push_back($1);
      $$->children.push_back($2);
    }
    ;

statement: CurlyLB reqStatement CurlyRB {
                $$ = new Node("CurlyLB reqStatement CurlyRB", "", yylineno);
                $$->children.push_back($2);
            }
          
          | IF LP expression RP statement  {
                $$ = new Node("IF Only", "", yylineno);
                $$->children.push_back($3); // condition
                $$->children.push_back($5); // if block
            }
          | IF LP expression RP statement ELSE statement {
                $$ = new Node("IfElseStatement", "", yylineno);
                $$->children.push_back($3); // condition
                $$->children.push_back($5); // if block
                $$->children.push_back($7); // else block
            }
          | WHILE LP expression RP statement {
                $$ = new Node("WhileStatement", "", yylineno);
                $$->children.push_back($3); // condition
                $$->children.push_back($5); // loop body
            }
            | SYSTEM_OUT_PRINTLN LP expression RP SEMICOLON
            {
                $$ = new Node("SYSTEM_OUT_PRINTLN", "", yylineno);
                $$->children.push_back($3); // condition
            }
            
            | identifier ASSIGN expression SEMICOLON {
				$$ = new Node("SOMETHING ASSIGNED = TO SOMETHING", "", yylineno);
				$$->children.push_back($1);
				$$->children.push_back($3);
			}
			| identifier LB expression RB ASSIGN expression SEMICOLON {
				$$ = new Node("SOMETHING [ASSIGNED] = TO SOMETHING", "", yylineno);
				$$->children.push_back($1);
				$$->children.push_back($3);
				$$->children.push_back($6);
			}
          ;
/*
*/

type: INT LB RB     {$$ = new Node("TYPE: INT LB RB", "", yylineno);}
	| BOOLEAN       {$$ = new Node("TYPE: BOOLEAN", "", yylineno);}
	| INT           {$$ = new Node("TYPE: INT", "", yylineno);}
	| identifier     
    ;
	

arguments: %empty {
      $$ = new Node("EMPTY arguments", "", yylineno);
    }|
    argumentsList
    {
      $$ = new Node("argumentsList", "", yylineno);
      $$->children.push_back($1);
    }
    ;

argumentsList:
        expression {
            $$ = new Node("argumentsList", "", yylineno);
                $$->children.push_back($1); // condition

            }|
            argumentsList COMMA expression{
                $$ = new Node("argumentsList", "", yylineno);
                $$->children.push_back($1); // condition
                $$->children.push_back($3); // condition
    };


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
                $$ = new Node("EXCLAMATION_MARK", "", yylineno);
                $$->children.push_back($1);
            } 

        	| 
        	expression LB expression RB{
                $$ = new Node("expression LB expression RB", "", yylineno);
                $$->children.push_back($1); /*expression 1*/
                $$->children.push_back($3); /*expression 2*/

        	}
        	| 
        	expression DOT LENGTH{
                $$ = new Node("DOT.Length", "", yylineno);
                $$->children.push_back($1);
        	}
        	|
            expression DOT identifier LP arguments RP {
                $$ = new Node("expression DOT identifier LP arguments RP", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
                $$->children.push_back($5);
        	}

        	| factor      {$$ = $1; /* printf("r4 ");*/}
        	| identifier  {$$ = $1; /* printf("r4 ");*/}

            |TRUE {  $$ = new Node("TRUE", "", yylineno);}
            |FALSE{  $$ = new Node("FALSE", "", yylineno);}

            |THIS{  $$ = new Node("THIS", "", yylineno);}

            |NEW INT LB expression RB  {
                $$ = new Node("NEW INT LB exp RB", "", yylineno);
                $$->children.push_back($4);
        	}

            |NEW identifier LP RP{
                $$ = new Node("NEW Identifier LP RP", "", yylineno);
                $$->children.push_back($2);
        	}
            |EXCLAMATION_MARK expression
            {
                $$ = new Node("NOT exp ", "", yylineno);
                $$->children.push_back($2);
        	}
                

            ;

identifier: IDENTIFIER{
            $$ = new Node("Identifier", $1, yylineno);
        	}
         
    ;


// 

factor: INTERGER_LITERAL{  $$ = new Node("Int", $1, yylineno); /* printf("r5 ");  Here we create a leaf node Int. The value of the leaf node is $1 */}
        | LP expression RP { $$ = $2; /* printf("r6 ");  simply return the expression */}
    ;


