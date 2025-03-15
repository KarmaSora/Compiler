// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 26 "parser.yy"

  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;

#line 54 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 127 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_classDeclaration: // classDeclaration
      case symbol_kind::S_singleClassDeclaration: // singleClassDeclaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_mainClass: // mainClass
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_reqVarDeclaration: // reqVarDeclaration
      case symbol_kind::S_retSTMT: // retSTMT
      case symbol_kind::S_reqVarOrStmt: // reqVarOrStmt
      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_methodDeclaration: // methodDeclaration
      case symbol_kind::S_reqMethodDeclaration: // reqMethodDeclaration
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_reqStatement: // reqStatement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_dotExpTest: // dotExpTest
      case symbol_kind::S_arguments: // arguments
      case symbol_kind::S_argument_list: // argument_list
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_MORE_THAN: // MORE_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_EXCLAMATION_MARK: // EXCLAMATION_MARK
      case symbol_kind::S_LEFT_CURLY: // LEFT_CURLY
      case symbol_kind::S_RIGHT_CURLY: // RIGHT_CURLY
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_MORE_THAN_EQUAL: // MORE_THAN_EQUAL
      case symbol_kind::S_LESS_THAN_EQUAL: // LESS_THAN_EQUAL
      case symbol_kind::S_UNDER_SCORE: // UNDER_SCORE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_SEMI_COLON: // SEMI_COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_classDeclaration: // classDeclaration
      case symbol_kind::S_singleClassDeclaration: // singleClassDeclaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_mainClass: // mainClass
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_reqVarDeclaration: // reqVarDeclaration
      case symbol_kind::S_retSTMT: // retSTMT
      case symbol_kind::S_reqVarOrStmt: // reqVarOrStmt
      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_methodDeclaration: // methodDeclaration
      case symbol_kind::S_reqMethodDeclaration: // reqMethodDeclaration
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_reqStatement: // reqStatement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_dotExpTest: // dotExpTest
      case symbol_kind::S_arguments: // arguments
      case symbol_kind::S_argument_list: // argument_list
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_factor: // factor
        value.move< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_MORE_THAN: // MORE_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_EXCLAMATION_MARK: // EXCLAMATION_MARK
      case symbol_kind::S_LEFT_CURLY: // LEFT_CURLY
      case symbol_kind::S_RIGHT_CURLY: // RIGHT_CURLY
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_MORE_THAN_EQUAL: // MORE_THAN_EQUAL
      case symbol_kind::S_LESS_THAN_EQUAL: // LESS_THAN_EQUAL
      case symbol_kind::S_UNDER_SCORE: // UNDER_SCORE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_SEMI_COLON: // SEMI_COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_classDeclaration: // classDeclaration
      case symbol_kind::S_singleClassDeclaration: // singleClassDeclaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_mainClass: // mainClass
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_reqVarDeclaration: // reqVarDeclaration
      case symbol_kind::S_retSTMT: // retSTMT
      case symbol_kind::S_reqVarOrStmt: // reqVarOrStmt
      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_methodDeclaration: // methodDeclaration
      case symbol_kind::S_reqMethodDeclaration: // reqMethodDeclaration
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_reqStatement: // reqStatement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_dotExpTest: // dotExpTest
      case symbol_kind::S_arguments: // arguments
      case symbol_kind::S_argument_list: // argument_list
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_factor: // factor
        value.copy< Node * > (that.value);
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_MORE_THAN: // MORE_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_EXCLAMATION_MARK: // EXCLAMATION_MARK
      case symbol_kind::S_LEFT_CURLY: // LEFT_CURLY
      case symbol_kind::S_RIGHT_CURLY: // RIGHT_CURLY
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_MORE_THAN_EQUAL: // MORE_THAN_EQUAL
      case symbol_kind::S_LESS_THAN_EQUAL: // LESS_THAN_EQUAL
      case symbol_kind::S_UNDER_SCORE: // UNDER_SCORE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_SEMI_COLON: // SEMI_COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_classDeclaration: // classDeclaration
      case symbol_kind::S_singleClassDeclaration: // singleClassDeclaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_mainClass: // mainClass
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_reqVarDeclaration: // reqVarDeclaration
      case symbol_kind::S_retSTMT: // retSTMT
      case symbol_kind::S_reqVarOrStmt: // reqVarOrStmt
      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_methodDeclaration: // methodDeclaration
      case symbol_kind::S_reqMethodDeclaration: // reqMethodDeclaration
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_reqStatement: // reqStatement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_dotExpTest: // dotExpTest
      case symbol_kind::S_arguments: // arguments
      case symbol_kind::S_argument_list: // argument_list
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_factor: // factor
        value.move< Node * > (that.value);
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_MORE_THAN: // MORE_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_EXCLAMATION_MARK: // EXCLAMATION_MARK
      case symbol_kind::S_LEFT_CURLY: // LEFT_CURLY
      case symbol_kind::S_RIGHT_CURLY: // RIGHT_CURLY
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_MORE_THAN_EQUAL: // MORE_THAN_EQUAL
      case symbol_kind::S_LESS_THAN_EQUAL: // LESS_THAN_EQUAL
      case symbol_kind::S_UNDER_SCORE: // UNDER_SCORE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_SEMI_COLON: // SEMI_COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_classDeclaration: // classDeclaration
      case symbol_kind::S_singleClassDeclaration: // singleClassDeclaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_mainClass: // mainClass
      case symbol_kind::S_varDeclaration: // varDeclaration
      case symbol_kind::S_reqVarDeclaration: // reqVarDeclaration
      case symbol_kind::S_retSTMT: // retSTMT
      case symbol_kind::S_reqVarOrStmt: // reqVarOrStmt
      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_methodDeclaration: // methodDeclaration
      case symbol_kind::S_reqMethodDeclaration: // reqMethodDeclaration
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_reqStatement: // reqStatement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_dotExpTest: // dotExpTest
      case symbol_kind::S_arguments: // arguments
      case symbol_kind::S_argument_list: // argument_list
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< Node * > ();
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_MORE_THAN: // MORE_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_LEFT_BRACKET: // LEFT_BRACKET
      case symbol_kind::S_RIGHT_BRACKET: // RIGHT_BRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_EXCLAMATION_MARK: // EXCLAMATION_MARK
      case symbol_kind::S_LEFT_CURLY: // LEFT_CURLY
      case symbol_kind::S_RIGHT_CURLY: // RIGHT_CURLY
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_MORE_THAN_EQUAL: // MORE_THAN_EQUAL
      case symbol_kind::S_LESS_THAN_EQUAL: // LESS_THAN_EQUAL
      case symbol_kind::S_UNDER_SCORE: // UNDER_SCORE
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_SEMI_COLON: // SEMI_COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // root: goal
#line 74 "parser.yy"
             {root = yystack_[0].value.as < Node * > (); }
#line 868 "parser.tab.cc"
    break;

  case 3: // goal: mainClass classDeclaration "end of file"
#line 77 "parser.yy"
                                     { 
		yylhs.value.as < Node * > () = new Node("goal", "", yylineno); 
		yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
		yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
	}
#line 878 "parser.tab.cc"
    break;

  case 4: // classDeclaration: singleClassDeclaration
#line 85 "parser.yy"
                                          { 
			yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
			}
#line 886 "parser.tab.cc"
    break;

  case 5: // singleClassDeclaration: CLASS identifier LEFT_CURLY varDeclaration methodDeclaration RIGHT_CURLY
#line 93 "parser.yy"
                                                                       {
						yylhs.value.as < Node * > () = new Node("classDeclarations", "", yylineno);
						Node* classes =	new Node("classDeclaration", yystack_[4].value.as < Node * > ()->value , yylineno);
						
						classes->children.push_back(yystack_[4].value.as < Node * > ());
						classes->children.push_back(yystack_[2].value.as < Node * > ());
						classes->children.push_back(yystack_[1].value.as < Node * > ());

						yylhs.value.as < Node * > ()->children.push_back(classes);
					}
#line 901 "parser.tab.cc"
    break;

  case 6: // singleClassDeclaration: singleClassDeclaration CLASS identifier LEFT_CURLY varDeclaration reqMethodDeclaration RIGHT_CURLY
#line 106 "parser.yy"
                                                                         {
						yylhs.value.as < Node * > () = yystack_[6].value.as < Node * > (); // singleClassDeclaration
						//$$ = new Node("ClassDeclarationsHERERERERE", "", yylineno);

						Node* classes = new Node("classDeclaration", yystack_[4].value.as < Node * > ()->value, yylineno);

						classes->children.push_back(yystack_[4].value.as < Node * > ());
						classes->children.push_back(yystack_[2].value.as < Node * > ());
						classes->children.push_back(yystack_[1].value.as < Node * > ());

						yylhs.value.as < Node * > ()->children.push_back(classes);
					}
#line 918 "parser.tab.cc"
    break;

  case 7: // type: INT LEFT_BRACKET RIGHT_BRACKET
#line 127 "parser.yy"
                                     { yylhs.value.as < Node * > () = new Node("INT LB RB", "", yylineno); }
#line 924 "parser.tab.cc"
    break;

  case 8: // type: BOOLEAN
#line 128 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("BOOLEAN", "", yylineno); }
#line 930 "parser.tab.cc"
    break;

  case 9: // type: INT
#line 129 "parser.yy"
              { yylhs.value.as < Node * > () = new Node("INT", "", yylineno); }
#line 936 "parser.tab.cc"
    break;

  case 10: // type: identifier
#line 130 "parser.yy"
                     { yylhs.value.as < Node * > () = new Node("typechar", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 942 "parser.tab.cc"
    break;

  case 11: // mainClass: PUBLIC CLASS identifier LEFT_CURLY PUBLIC STATIC VOID MAIN LP STRING LEFT_BRACKET RIGHT_BRACKET identifier RP LEFT_CURLY reqStatement RIGHT_CURLY RIGHT_CURLY
#line 148 "parser.yy"
                   {
				yylhs.value.as < Node * > () = new Node("MAIN CLASS", "", yylineno);

				Node* methods = new Node("MAIN METHOD", "", yylineno);

				

				yylhs.value.as < Node * > ()->children.push_back(yystack_[15].value.as < Node * > ());


				yylhs.value.as < Node * > ()->children.push_back(methods);
				methods->children.push_back(yystack_[5].value.as < Node * > ());
				methods->children.push_back(yystack_[2].value.as < Node * > ());
				
				
		   }
#line 963 "parser.tab.cc"
    break;

  case 12: // varDeclaration: %empty
#line 179 "parser.yy"
                       { yylhs.value.as < Node * > () = new Node("var declarations", "", yylineno); }
#line 969 "parser.tab.cc"
    break;

  case 13: // varDeclaration: reqVarDeclaration
#line 180 "parser.yy"
                                                    { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 975 "parser.tab.cc"
    break;

  case 14: // reqVarDeclaration: type identifier SEMI_COLON
#line 184 "parser.yy"
                                              {
		
				yylhs.value.as < Node * > () = new Node("var declarations", "", yylineno);
				Node * varDec = new Node("var declaration", "", yylineno);
				varDec->children.push_back(yystack_[2].value.as < Node * > ());
				varDec->children.push_back(yystack_[1].value.as < Node * > ());

				yylhs.value.as < Node * > ()->children.push_back(varDec);
			}
#line 989 "parser.tab.cc"
    break;

  case 15: // reqVarDeclaration: reqVarDeclaration type identifier SEMI_COLON
#line 193 "parser.yy"
                                                                               {
				yylhs.value.as < Node * > () = yystack_[3].value.as < Node * > ();
				Node* varDec = new Node("var declaration", "", yylineno);
				varDec->children.push_back(yystack_[2].value.as < Node * > ());
				varDec->children.push_back(yystack_[1].value.as < Node * > ());

				yylhs.value.as < Node * > ()->children.push_back(varDec);
		
			}
#line 1003 "parser.tab.cc"
    break;

  case 16: // retSTMT: RETURN
#line 205 "parser.yy"
                 { yylhs.value.as < Node * > () = new Node("RETURN SEMI_COLON", "", yylineno); }
#line 1009 "parser.tab.cc"
    break;

  case 17: // retSTMT: RETURN expression SEMI_COLON
#line 207 "parser.yy"
                                                     { 
			yylhs.value.as < Node * > () = new Node("RETURN", "", yylineno);
			yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
		}
#line 1018 "parser.tab.cc"
    break;

  case 18: // reqVarOrStmt: %empty
#line 216 "parser.yy"
                     {	yylhs.value.as < Node * > () = new Node("methodBody", "", yylineno); }
#line 1024 "parser.tab.cc"
    break;

  case 19: // reqVarOrStmt: reqVarOrStmt type identifier SEMI_COLON
#line 217 "parser.yy"
                                                      {
				yylhs.value.as < Node * > () = yystack_[3].value.as < Node * > ();
				Node* varDec = new Node("var declaration", "", yylineno);
				varDec->children.push_back(yystack_[2].value.as < Node * > ());
				varDec->children.push_back(yystack_[1].value.as < Node * > ());

				yylhs.value.as < Node * > ()->children.push_back(varDec);
			
			}
#line 1038 "parser.tab.cc"
    break;

  case 20: // reqVarOrStmt: reqVarOrStmt statement
#line 229 "parser.yy"
                                     { 
				yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
				Node* varDec = new Node("statement", "", yylineno);
				varDec->children.push_back(yystack_[0].value.as < Node * > ());

				yylhs.value.as < Node * > ()->children.push_back(varDec);
	
			}
#line 1051 "parser.tab.cc"
    break;

  case 21: // parameters: %empty
#line 241 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("parameters", "", yylineno);  }
#line 1057 "parser.tab.cc"
    break;

  case 22: // parameters: parameter_list
#line 242 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();}
#line 1063 "parser.tab.cc"
    break;

  case 23: // parameter_list: type identifier
#line 245 "parser.yy"
                                { 
				yylhs.value.as < Node * > () = new Node("parameters", "", yylineno);
				Node* params = new Node("parameter", "", yylineno);

				params->children.push_back(yystack_[1].value.as < Node * > ());
				params->children.push_back(yystack_[0].value.as < Node * > ());

				yylhs.value.as < Node * > ()->children.push_back(params);
			}
#line 1077 "parser.tab.cc"
    break;

  case 24: // parameter_list: parameter_list COMMA type identifier
#line 254 "parser.yy"
                                                     { 
				yylhs.value.as < Node * > () = yystack_[3].value.as < Node * > ();
				Node* params = new Node("parameter", "", yylineno);

				params->children.push_back(yystack_[1].value.as < Node * > ());
				params->children.push_back(yystack_[0].value.as < Node * > ());
				
				yylhs.value.as < Node * > ()->children.push_back(params);

			  }
#line 1092 "parser.tab.cc"
    break;

  case 25: // methodDeclaration: reqMethodDeclaration
#line 273 "parser.yy"
                                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1098 "parser.tab.cc"
    break;

  case 26: // reqMethodDeclaration: PUBLIC type identifier LP parameters RP LEFT_CURLY reqVarOrStmt retSTMT RIGHT_CURLY
#line 280 "parser.yy"
                                        {
						yylhs.value.as < Node * > () = new Node("methodDeclarations", "", yylineno);
						Node * methDec = new Node("methodDec", yystack_[7].value.as < Node * > ()->value, yylineno);
						methDec->children.push_back(yystack_[8].value.as < Node * > ());
						methDec->children.push_back(yystack_[7].value.as < Node * > ());
						methDec->children.push_back(yystack_[5].value.as < Node * > ());
						methDec->children.push_back(yystack_[2].value.as < Node * > ());
						methDec->children.push_back(yystack_[1].value.as < Node * > ());

						yylhs.value.as < Node * > ()->children.push_back(methDec);
						


					}
#line 1117 "parser.tab.cc"
    break;

  case 27: // reqMethodDeclaration: reqMethodDeclaration PUBLIC type identifier LP parameters RP LEFT_CURLY reqVarOrStmt retSTMT RIGHT_CURLY
#line 297 "parser.yy"
                                        {
						yylhs.value.as < Node * > () = yystack_[10].value.as < Node * > ();
						Node * methDec = new Node("methodDec", yystack_[7].value.as < Node * > ()->value, yylineno);
						methDec->children.push_back(yystack_[8].value.as < Node * > ());
						methDec->children.push_back(yystack_[7].value.as < Node * > ());
						methDec->children.push_back(yystack_[5].value.as < Node * > ());
						methDec->children.push_back(yystack_[2].value.as < Node * > ());
						methDec->children.push_back(yystack_[1].value.as < Node * > ());

						yylhs.value.as < Node * > ()->children.push_back(methDec);
					}
#line 1133 "parser.tab.cc"
    break;

  case 28: // reqMethodDeclaration: %empty
#line 309 "parser.yy"
                           { yylhs.value.as < Node * > () = new Node("NOOOOOO methodDeclarations", "", yylineno); }
#line 1139 "parser.tab.cc"
    break;

  case 29: // statement: LEFT_CURLY reqStatement RIGHT_CURLY
#line 315 "parser.yy"
                                               { /* recursive "*" */
				yylhs.value.as < Node * > () = new Node("LC statement RC", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());


			}
#line 1150 "parser.tab.cc"
    break;

  case 30: // statement: IF LP expression RP statement
#line 322 "parser.yy"
                                                        {/* if without else */
				yylhs.value.as < Node * > () = new Node("IF LP expression RP statement", "", yylineno);
            	yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
            	yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1160 "parser.tab.cc"
    break;

  case 31: // statement: IF LP expression RP statement ELSE statement
#line 327 "parser.yy"
                                                                       { /* special with "?" ? */
				yylhs.value.as < Node * > () = new Node("IF LP expression RP statement ELSE statement", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
				Node* stmt = new Node("statements", "", yylineno);
				stmt->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(stmt);

			Node* secStmt = new Node("statements", "", yylineno);
				secStmt->children.push_back(yystack_[0].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(secStmt);

			}
#line 1177 "parser.tab.cc"
    break;

  case 32: // statement: IF LP expression RP statement ELSE LEFT_CURLY RIGHT_CURLY
#line 340 "parser.yy"
                                                                                    { /* special with "?" ? */
				yylhs.value.as < Node * > () = new Node("IF LP expression RP statement ELSE statement", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ());
				Node* stmt = new Node("statements", "", yylineno);
				stmt->children.push_back(yystack_[3].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(stmt);

			Node* secStmt = new Node("empty statements", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(secStmt);

			}
#line 1193 "parser.tab.cc"
    break;

  case 33: // statement: WHILE LP expression RP statement
#line 351 "parser.yy"
                                                           { /* ( " else " Statement ) ? */
				yylhs.value.as < Node * > () = new Node("WHILE LP expression RP statement", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1203 "parser.tab.cc"
    break;

  case 34: // statement: SYSTEM_OUT_PRINTLN LP expression RP SEMI_COLON
#line 356 "parser.yy"
                                                                         {
				yylhs.value.as < Node * > () = new Node("SIMPLE PRINT LOL", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
			}
#line 1212 "parser.tab.cc"
    break;

  case 35: // statement: identifier ASSIGN expression SEMI_COLON
#line 360 "parser.yy"
                                                                  {
				yylhs.value.as < Node * > () = new Node("SOMETHING ASSIGNED = TO SOMETHING", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1222 "parser.tab.cc"
    break;

  case 36: // statement: identifier LEFT_BRACKET expression RIGHT_BRACKET ASSIGN expression SEMI_COLON
#line 365 "parser.yy"
                                                                                                        {
				yylhs.value.as < Node * > () = new Node("SOMETHING [ASSIGNED] = TO SOMETHING", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1233 "parser.tab.cc"
    break;

  case 37: // reqStatement: statement
#line 374 "parser.yy"
                       {
				yylhs.value.as < Node * > () = new Node("statements", "", yylineno);
				Node * reqSTMT = new Node("statement", "", yylineno);
				reqSTMT->children.push_back(yystack_[0].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(reqSTMT);
			}
#line 1244 "parser.tab.cc"
    break;

  case 38: // reqStatement: reqStatement statement
#line 381 "parser.yy"
                                                 {
				yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();				
				Node * reqSTMT = new Node("statement", "", yylineno);
				reqSTMT->children.push_back(yystack_[0].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(reqSTMT);

			}
#line 1256 "parser.tab.cc"
    break;

  case 39: // expression: expression PLUSOP expression
#line 393 "parser.yy"
                                         {      /*
                                                  Create a subtree that corresponds to the AddExpression
                                                  The root of the subtree is AddExpression
                                                  The childdren of the AddExpression subtree are the left hand side (expression accessed through $1) and right hand side of the expression (expression accessed through $3)
                                                */
				yylhs.value.as < Node * > () = new Node("AddExpression", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				/* printf("r1 "); */
			}
#line 1271 "parser.tab.cc"
    break;

  case 40: // expression: expression MINUSOP expression
#line 403 "parser.yy"
                                            {
				yylhs.value.as < Node * > () = new Node("SubExpression", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				/* printf("r2 "); */
			}
#line 1282 "parser.tab.cc"
    break;

  case 41: // expression: expression MULTOP expression
#line 409 "parser.yy"
                                           {
				yylhs.value.as < Node * > () = new Node("MultExpression", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				/* printf("r3 "); */
			}
#line 1293 "parser.tab.cc"
    break;

  case 42: // expression: expression AND expression
#line 415 "parser.yy"
                                        {
				yylhs.value.as < Node * > () = new Node("AND", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1303 "parser.tab.cc"
    break;

  case 43: // expression: expression OR expression
#line 420 "parser.yy"
                                                   {
				yylhs.value.as < Node * > () = new Node("OR", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1313 "parser.tab.cc"
    break;

  case 44: // expression: expression LESS_THAN expression
#line 425 "parser.yy"
                                                          {
				yylhs.value.as < Node * > () = new Node("LESS_THAN", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1323 "parser.tab.cc"
    break;

  case 45: // expression: expression MORE_THAN expression
#line 430 "parser.yy"
                                                          {
				yylhs.value.as < Node * > () = new Node("MORE_THAN", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1333 "parser.tab.cc"
    break;

  case 46: // expression: expression EQUAL expression
#line 435 "parser.yy"
                                                      {
				yylhs.value.as < Node * > () = new Node("EQUAL", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1343 "parser.tab.cc"
    break;

  case 47: // expression: expression LEFT_BRACKET expression RIGHT_BRACKET
#line 442 "parser.yy"
                                                                           {
				yylhs.value.as < Node * > () = new Node("expression LEFT_BRACKET expression RIGHT_BRACKET", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1353 "parser.tab.cc"
    break;

  case 48: // expression: expression DOT LENGTH
#line 447 "parser.yy"
                                                {
				yylhs.value.as < Node * > () = new Node("expression DOT LENGTH", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
			}
#line 1362 "parser.tab.cc"
    break;

  case 49: // expression: TRUE
#line 456 "parser.yy"
                               {
				yylhs.value.as < Node * > () = new Node("TRUE", "True", yylineno);
			}
#line 1370 "parser.tab.cc"
    break;

  case 50: // expression: FALSE
#line 459 "parser.yy"
                                {
				yylhs.value.as < Node * > () = new Node("FALSE", "False", yylineno);
			}
#line 1378 "parser.tab.cc"
    break;

  case 51: // expression: THIS
#line 468 "parser.yy"
                               {
				yylhs.value.as < Node * > () = new Node("THIS", "", yylineno);
			}
#line 1386 "parser.tab.cc"
    break;

  case 52: // expression: NEW INT LEFT_BRACKET expression RIGHT_BRACKET
#line 471 "parser.yy"
                                                                        {
				yylhs.value.as < Node * > () = new Node("NEW INT LEFT_BRACKET expression RIGHT_BRACKET", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1395 "parser.tab.cc"
    break;

  case 53: // expression: NEW identifier LP RP
#line 478 "parser.yy"
                                               { yylhs.value.as < Node * > () = new Node("NEW identifier LP RP", "", yylineno);
									 yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
			}
#line 1403 "parser.tab.cc"
    break;

  case 54: // expression: EXCLAMATION_MARK expression
#line 483 "parser.yy"
                                                      {
				yylhs.value.as < Node * > () = new Node("EXCLAMATION_MARK expression", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1412 "parser.tab.cc"
    break;

  case 55: // expression: factor
#line 495 "parser.yy"
                              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); /* printf("r4 ");*/ }
#line 1418 "parser.tab.cc"
    break;

  case 56: // expression: identifier
#line 496 "parser.yy"
                                     { /* empty because we have it in root */ yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();  }
#line 1424 "parser.tab.cc"
    break;

  case 57: // expression: expression DOT identifier LP arguments RP
#line 501 "parser.yy"
                                     {
				yylhs.value.as < Node * > () = new Node("exp DOT ident LP exp COMMA exp RP", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ()); /* `new A()` */
        		yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); /* `a2` */
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
				
			}
#line 1436 "parser.tab.cc"
    break;

  case 58: // expression: expression DOT identifier LP arguments RP dotExpTest
#line 509 "parser.yy"
                                                {
				yylhs.value.as < Node * > () = new Node("functionCall", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ()); /* `new A()` */
        		yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); /* `a2` */
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				
			}
#line 1449 "parser.tab.cc"
    break;

  case 59: // dotExpTest: DOT identifier LP arguments RP
#line 523 "parser.yy"
                                           { yylhs.value.as < Node * > () = new Node("DOT identifier LP arguments RP", "", yylineno);
											  yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
											  yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
											}
#line 1458 "parser.tab.cc"
    break;

  case 60: // dotExpTest: DOT identifier LP arguments RP dotExpTest
#line 528 "parser.yy"
                                                                  { yylhs.value.as < Node * > () = new Node("DOT identifier LP arguments RP dotExpTest", "", yylineno);
														yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
														yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
														yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				}
#line 1468 "parser.tab.cc"
    break;

  case 61: // dotExpTest: DOT LENGTH
#line 533 "parser.yy"
                                    { yylhs.value.as < Node * > () = new Node("DOT LENGTH", "", yylineno); }
#line 1474 "parser.tab.cc"
    break;

  case 62: // arguments: %empty
#line 539 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("empty argument", "", yylineno); }
#line 1480 "parser.tab.cc"
    break;

  case 63: // arguments: argument_list
#line 540 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1486 "parser.tab.cc"
    break;

  case 64: // argument_list: expression
#line 543 "parser.yy"
                          { yylhs.value.as < Node * > () = new Node("argument_list", "", yylineno);  yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());}
#line 1492 "parser.tab.cc"
    break;

  case 65: // argument_list: argument_list COMMA expression
#line 544 "parser.yy"
                                              {
				yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
				Node* arg = new Node("argument", "", yylineno);
				arg->children.push_back(yystack_[0].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(arg);
			 
			 }
#line 1504 "parser.tab.cc"
    break;

  case 66: // identifier: IDENTIFIER
#line 555 "parser.yy"
                       { yylhs.value.as < Node * > () = new Node("identifier", yystack_[0].value.as < std::string > (), yylineno); }
#line 1510 "parser.tab.cc"
    break;

  case 67: // factor: INTEGER_LITERAL
#line 562 "parser.yy"
                                      {  yylhs.value.as < Node * > () = new Node("INT", yystack_[0].value.as < std::string > (), yylineno); /* printf("r5 ");  Here we create a leaf node Int. The value of the leaf node is $1 */}
#line 1516 "parser.tab.cc"
    break;

  case 68: // factor: LP expression RP
#line 564 "parser.yy"
                               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); /* printf("r6 ");  simply return the expression */}
#line 1522 "parser.tab.cc"
    break;


#line 1526 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -65;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -27,   -20,    19,   -65,     5,   -32,   -65,   -32,    25,     8,
     -65,    -8,    18,   -65,   -32,    20,    -3,    24,     7,    34,
     -65,   -32,    22,    -3,   -65,    -3,    23,    42,    28,    -3,
      38,    37,   -32,    22,    39,   -65,   -65,   -32,   -65,    -3,
      36,   -12,    72,    77,   -32,   -65,   -65,    51,    -3,    82,
      74,   -32,    85,    52,    -3,    75,   -65,    81,    -3,   106,
     -32,   -65,   -32,    83,   109,   179,   -65,   -65,   100,    13,
     130,   131,   132,   190,   -32,   118,   -65,    15,   179,    13,
     -65,    43,    15,   190,   190,   190,   190,   -65,   -65,   -65,
      -1,   190,   -65,    98,   -65,   -65,   107,   -65,   190,   190,
     129,   120,   -65,   -65,   236,   254,   272,   290,   141,   157,
     361,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     -17,   -65,   -65,   302,   171,   -65,   145,    13,   125,    13,
     -65,   190,   163,     3,     3,    11,   361,   350,   116,   116,
     143,   314,   -65,   165,   148,   -65,   -65,   167,   -65,   -65,
     326,   -65,   -65,   190,   190,    45,   -65,   338,   191,   136,
     183,   205,   -65,   180,   190,   -65,   -65,   -15,   -65,   338,
     -65,   202,   190,   206,   180,   -65
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     0,     1,     0,     0,     4,
      66,     0,     0,     3,     0,     0,    12,     0,     0,     9,
       8,     0,    28,    13,    10,    12,     0,     0,     0,     0,
       0,    25,     0,    28,     0,     7,    14,     0,     5,     0,
       0,     0,     0,     0,     0,    15,     6,     0,    21,     0,
       0,     0,     0,    22,    21,     0,    23,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    24,    18,     0,     0,
       0,     0,     0,    16,     0,     0,    20,    10,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    49,    50,    51,
       0,     0,    67,     0,    56,    55,     0,    26,     0,     0,
       0,     0,    29,    38,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    19,     0,     0,    27,     0,     0,     0,     0,
      68,     0,     0,    39,    40,    41,    42,    43,    44,    45,
      46,     0,    48,     0,     0,    35,    11,    30,    34,    33,
       0,    53,    47,    62,     0,     0,    52,    64,     0,    63,
       0,     0,    31,    57,     0,    36,    32,     0,    58,    65,
      61,     0,    62,     0,    59,    60
  };

  const short
  parser::yypgoto_[] =
  {
     -65,   -65,   -65,   -65,   -65,   112,   -65,   185,   -65,   137,
     151,   166,   -65,   -65,   188,   -64,   144,    14,    48,    54,
     -65,    -5,   -65
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,     9,    21,     4,    22,    23,    75,
      65,    52,    53,    30,    31,    80,    81,   157,   168,   158,
     159,    94,    95
  };

  const unsigned char
  parser::yytable_[] =
  {
      11,    76,    12,    19,   142,   108,   170,     1,   113,    17,
       5,    24,    46,    10,    76,    15,    28,   103,    24,     6,
      24,   119,    39,   120,    24,    13,    20,    40,    10,   119,
      10,   120,    43,    98,    24,     7,    69,   103,    14,    49,
      99,    16,    10,    24,    10,    70,    56,    25,    26,    24,
      71,    72,    27,    24,    18,    64,    29,    66,    10,    34,
      77,    35,    38,   147,    82,   149,    69,   102,   161,    96,
      36,    39,    42,    77,    82,    70,    82,    70,    45,    47,
      71,    72,    71,    72,    48,   109,    50,    93,    10,    54,
      10,   162,    55,    57,    60,    58,    82,   104,   105,   106,
     107,   111,   112,   113,    61,   110,    67,   114,   115,   116,
     117,   118,   123,   124,    63,   143,   119,    68,   120,   111,
     112,   113,    82,    79,    82,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   119,    32,   120,    83,    84,    85,
     121,    37,    97,    69,   126,   150,   111,   112,   113,   122,
      82,    44,    70,   125,   116,   117,    82,    71,    72,   131,
      51,   119,   171,   120,   132,    10,    51,   148,   160,   146,
      62,   151,   153,   154,   111,   112,   113,    74,   169,   164,
     114,   115,   116,   117,   118,    19,   111,   112,   113,   119,
      74,   120,   114,   115,   116,   117,   118,    86,   155,   163,
     167,   119,    69,   120,    87,    88,    89,    90,    20,   172,
      33,    70,    91,   145,   174,   100,    71,    72,    78,    73,
      59,    41,   175,   101,    10,   165,   173,     0,    69,   166,
       0,     0,     0,     0,     0,    10,    92,    70,     0,   111,
     112,   113,    71,    72,   127,   114,   115,   116,   117,   118,
      10,     0,     0,     0,   119,     0,   120,   111,   112,   113,
       0,     0,   128,   114,   115,   116,   117,   118,     0,     0,
       0,     0,   119,     0,   120,   111,   112,   113,     0,     0,
     129,   114,   115,   116,   117,   118,     0,     0,     0,     0,
     119,     0,   120,   111,   112,   113,     0,     0,   130,   114,
     115,   116,   117,   118,     0,   111,   112,   113,   119,     0,
     120,   114,   115,   116,   117,   118,     0,   111,   112,   113,
     119,   144,   120,   114,   115,   116,   117,   118,     0,   111,
     112,   113,   119,   152,   120,   114,   115,   116,   117,   118,
       0,   111,   112,   113,   119,   156,   120,   114,   115,   116,
     117,   118,     0,   111,   112,   113,   119,     0,   120,   114,
       0,   116,   117,   118,   111,   112,   113,     0,   119,     0,
     120,     0,   116,   117,   118,     0,     0,     0,     0,   119,
       0,   120
  };

  const short
  parser::yycheck_[] =
  {
       5,    65,     7,     6,    21,     6,    21,    34,     5,    14,
      30,    16,    24,    45,    78,    23,    21,    81,    23,     0,
      25,    18,    34,    20,    29,     0,    29,    32,    45,    18,
      45,    20,    37,    18,    39,    30,    23,   101,    30,    44,
      25,    23,    45,    48,    45,    32,    51,    23,    41,    54,
      37,    38,    18,    58,    34,    60,    34,    62,    45,    36,
      65,    19,    24,   127,    69,   129,    23,    24,    23,    74,
      42,    34,    33,    78,    79,    32,    81,    32,    42,     7,
      37,    38,    37,    38,     7,    90,    35,    73,    45,     7,
      45,   155,    18,     8,    19,    43,   101,    83,    84,    85,
      86,     3,     4,     5,    23,    91,    23,     9,    10,    11,
      12,    13,    98,    99,     8,   120,    18,     8,    20,     3,
       4,     5,   127,    23,   129,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    18,    23,    20,     7,     7,     7,
      42,    29,    24,    23,    24,   131,     3,     4,     5,    42,
     155,    39,    32,    24,    11,    12,   161,    37,    38,    18,
      48,    18,   167,    20,     7,    45,    54,    42,   154,    24,
      58,     8,     7,    25,     3,     4,     5,    65,   164,    43,
       9,    10,    11,    12,    13,     6,     3,     4,     5,    18,
      78,    20,     9,    10,    11,    12,    13,     7,    31,     8,
      20,    18,    23,    20,    14,    15,    16,    17,    29,     7,
      25,    32,    22,    42,     8,    78,    37,    38,    67,    40,
      54,    33,   174,    79,    45,    42,   172,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    45,    46,    32,    -1,     3,
       4,     5,    37,    38,     8,     9,    10,    11,    12,    13,
      45,    -1,    -1,    -1,    18,    -1,    20,     3,     4,     5,
      -1,    -1,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    18,    -1,    20,     3,     4,     5,    -1,    -1,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      18,    -1,    20,     3,     4,     5,    -1,    -1,     8,     9,
      10,    11,    12,    13,    -1,     3,     4,     5,    18,    -1,
      20,     9,    10,    11,    12,    13,    -1,     3,     4,     5,
      18,    19,    20,     9,    10,    11,    12,    13,    -1,     3,
       4,     5,    18,    19,    20,     9,    10,    11,    12,    13,
      -1,     3,     4,     5,    18,    19,    20,     9,    10,    11,
      12,    13,    -1,     3,     4,     5,    18,    -1,    20,     9,
      -1,    11,    12,    13,     3,     4,     5,    -1,    18,    -1,
      20,    -1,    11,    12,    13,    -1,    -1,    -1,    -1,    18,
      -1,    20
  };

  const signed char
  parser::yystos_[] =
  {
       0,    34,    48,    49,    53,    30,     0,    30,    50,    51,
      45,    68,    68,     0,    30,    23,    23,    68,    34,     6,
      29,    52,    54,    55,    68,    23,    41,    18,    68,    34,
      60,    61,    52,    54,    36,    19,    42,    52,    24,    34,
      68,    61,    33,    68,    52,    42,    24,     7,     7,    68,
      35,    52,    58,    59,     7,    18,    68,     8,    43,    58,
      19,    23,    52,     8,    68,    57,    68,    23,     8,    23,
      32,    37,    38,    40,    52,    56,    62,    68,    57,    23,
      62,    63,    68,     7,     7,     7,     7,    14,    15,    16,
      17,    22,    46,    64,    68,    69,    68,    24,    18,    25,
      56,    63,    24,    62,    64,    64,    64,    64,     6,    68,
      64,     3,     4,     5,     9,    10,    11,    12,    13,    18,
      20,    42,    42,    64,    64,    24,    24,     8,     8,     8,
       8,    18,     7,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    21,    68,    19,    42,    24,    62,    42,    62,
      64,     8,    19,     7,    25,    31,    19,    64,    66,    67,
      64,    23,    62,     8,    43,    42,    24,    20,    65,    64,
      21,    68,     7,    66,     8,    65
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    47,    48,    49,    50,    51,    51,    52,    52,    52,
      52,    53,    54,    54,    55,    55,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    60,    61,    61,    61,    62,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65,    65,    66,    66,    67,    67,    68,    69,    69
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     1,     6,     7,     3,     1,     1,
       1,    18,     0,     1,     3,     4,     1,     3,     0,     4,
       2,     0,     1,     2,     4,     1,    10,    11,     0,     3,
       5,     7,     8,     5,     5,     4,     7,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     1,
       1,     1,     5,     4,     2,     1,     1,     6,     7,     5,
       6,     2,     0,     1,     1,     3,     1,     1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PLUSOP", "MINUSOP",
  "MULTOP", "INT", "LP", "RP", "AND", "OR", "LESS_THAN", "MORE_THAN",
  "EQUAL", "TRUE", "FALSE", "THIS", "NEW", "LEFT_BRACKET", "RIGHT_BRACKET",
  "DOT", "LENGTH", "EXCLAMATION_MARK", "LEFT_CURLY", "RIGHT_CURLY",
  "ASSIGN", "MORE_THAN_EQUAL", "LESS_THAN_EQUAL", "UNDER_SCORE", "BOOLEAN",
  "CLASS", "ELSE", "IF", "MAIN", "PUBLIC", "STRING", "VOID",
  "SYSTEM_OUT_PRINTLN", "WHILE", "EXTENDS", "RETURN", "STATIC",
  "SEMI_COLON", "COMMA", "DIVIDE", "IDENTIFIER", "INTEGER_LITERAL",
  "$accept", "root", "goal", "classDeclaration", "singleClassDeclaration",
  "type", "mainClass", "varDeclaration", "reqVarDeclaration", "retSTMT",
  "reqVarOrStmt", "parameters", "parameter_list", "methodDeclaration",
  "reqMethodDeclaration", "statement", "reqStatement", "expression",
  "dotExpTest", "arguments", "argument_list", "identifier", "factor", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    74,    74,    77,    85,    92,   105,   127,   128,   129,
     130,   146,   179,   180,   184,   193,   205,   207,   216,   217,
     229,   241,   242,   245,   254,   273,   277,   294,   309,   315,
     322,   327,   340,   351,   356,   360,   365,   374,   381,   393,
     403,   409,   415,   420,   425,   430,   435,   442,   447,   456,
     459,   468,   471,   478,   483,   495,   496,   500,   508,   523,
     528,   533,   539,   540,   543,   544,   555,   562,   564
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2141 "parser.tab.cc"

