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
#line 72 "parser.yy"
             {root = yystack_[0].value.as < Node * > (); }
#line 868 "parser.tab.cc"
    break;

  case 3: // goal: mainClass classDeclaration "end of file"
#line 75 "parser.yy"
                                     { 
		yylhs.value.as < Node * > () = new Node("goal", "", yylineno); 
		yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
		yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
	}
#line 878 "parser.tab.cc"
    break;

  case 4: // classDeclaration: singleClassDeclaration
#line 83 "parser.yy"
                                          { 
			yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
			}
#line 886 "parser.tab.cc"
    break;

  case 5: // singleClassDeclaration: CLASS identifier LEFT_CURLY varDeclaration methodDeclaration RIGHT_CURLY
#line 91 "parser.yy"
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
#line 104 "parser.yy"
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
#line 125 "parser.yy"
                                     { yylhs.value.as < Node * > () = new Node("INT LB RB", "", yylineno); }
#line 924 "parser.tab.cc"
    break;

  case 8: // type: BOOLEAN
#line 126 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("BOOLEAN", "", yylineno); }
#line 930 "parser.tab.cc"
    break;

  case 9: // type: INT
#line 127 "parser.yy"
              { yylhs.value.as < Node * > () = new Node("INT", "", yylineno); }
#line 936 "parser.tab.cc"
    break;

  case 10: // type: identifier
#line 128 "parser.yy"
                     { yylhs.value.as < Node * > () = new Node("typechar", "", yylineno); yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); }
#line 942 "parser.tab.cc"
    break;

  case 11: // mainClass: PUBLIC CLASS identifier LEFT_CURLY PUBLIC STATIC VOID MAIN LP STRING LEFT_BRACKET RIGHT_BRACKET identifier RP LEFT_CURLY statement reqStatement RIGHT_CURLY RIGHT_CURLY
#line 146 "parser.yy"
                   {
				yylhs.value.as < Node * > () = new Node("MAIN CLASS", "", yylineno);

				Node* methods = new Node("MAIN METHOD", "", yylineno);

				

				yylhs.value.as < Node * > ()->children.push_back(yystack_[16].value.as < Node * > ());


				yylhs.value.as < Node * > ()->children.push_back(methods);
				methods->children.push_back(yystack_[6].value.as < Node * > ());
				methods->children.push_back(yystack_[3].value.as < Node * > ());
				methods->children.push_back(yystack_[2].value.as < Node * > ());
				
		   }
#line 963 "parser.tab.cc"
    break;

  case 12: // varDeclaration: %empty
#line 177 "parser.yy"
                       { yylhs.value.as < Node * > () = new Node("var declarations", "", yylineno); }
#line 969 "parser.tab.cc"
    break;

  case 13: // varDeclaration: reqVarDeclaration
#line 178 "parser.yy"
                                                    { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 975 "parser.tab.cc"
    break;

  case 14: // reqVarDeclaration: type identifier SEMI_COLON
#line 182 "parser.yy"
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
#line 191 "parser.yy"
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
#line 203 "parser.yy"
                 { yylhs.value.as < Node * > () = new Node("RETURN SEMI_COLON", "", yylineno); }
#line 1009 "parser.tab.cc"
    break;

  case 17: // retSTMT: RETURN expression SEMI_COLON
#line 205 "parser.yy"
                                                     { 
			yylhs.value.as < Node * > () = new Node("RETURN", "", yylineno);
			yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
		}
#line 1018 "parser.tab.cc"
    break;

  case 18: // reqVarOrStmt: %empty
#line 214 "parser.yy"
                     {	yylhs.value.as < Node * > () = new Node("methodBody", "", yylineno); }
#line 1024 "parser.tab.cc"
    break;

  case 19: // reqVarOrStmt: reqVarOrStmt type identifier SEMI_COLON
#line 215 "parser.yy"
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
#line 227 "parser.yy"
                                     { 
				yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
				Node* varDec = new Node("statement", "", yylineno);
				varDec->children.push_back(yystack_[0].value.as < Node * > ());

				yylhs.value.as < Node * > ()->children.push_back(varDec);
	
			}
#line 1051 "parser.tab.cc"
    break;

  case 21: // parameters: %empty
#line 239 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("parameters", "", yylineno);  }
#line 1057 "parser.tab.cc"
    break;

  case 22: // parameters: parameter_list
#line 240 "parser.yy"
                           { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();}
#line 1063 "parser.tab.cc"
    break;

  case 23: // parameter_list: type identifier
#line 243 "parser.yy"
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
#line 252 "parser.yy"
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
#line 271 "parser.yy"
                                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1098 "parser.tab.cc"
    break;

  case 26: // reqMethodDeclaration: PUBLIC type identifier LP parameters RP LEFT_CURLY reqVarOrStmt retSTMT RIGHT_CURLY
#line 278 "parser.yy"
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
#line 295 "parser.yy"
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
#line 307 "parser.yy"
                           { yylhs.value.as < Node * > () = new Node("NOOOOOO methodDeclarations", "", yylineno); }
#line 1139 "parser.tab.cc"
    break;

  case 29: // statement: LEFT_CURLY reqStatement RIGHT_CURLY
#line 313 "parser.yy"
                                               { /* recursive "*" */
				yylhs.value.as < Node * > () = new Node("LC statement RC", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1148 "parser.tab.cc"
    break;

  case 30: // statement: IF LP expression RP statement
#line 318 "parser.yy"
                                                        {/* if without else */
				yylhs.value.as < Node * > () = new Node("IF LP expression RP statement", "", yylineno);
            	yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
            	yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1158 "parser.tab.cc"
    break;

  case 31: // statement: IF LP expression RP statement ELSE statement
#line 323 "parser.yy"
                                                                       { /* special with "?" ? */
				yylhs.value.as < Node * > () = new Node("IF LP expression RP statement ELSE statement", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1169 "parser.tab.cc"
    break;

  case 32: // statement: WHILE LP expression RP statement
#line 329 "parser.yy"
                                                           { /* ( " else " Statement ) ? */
				yylhs.value.as < Node * > () = new Node("WHILE LP expression RP statement", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1179 "parser.tab.cc"
    break;

  case 33: // statement: SYSTEM_OUT_PRINTLN LP expression RP SEMI_COLON
#line 334 "parser.yy"
                                                                         {
				yylhs.value.as < Node * > () = new Node("SIMPLE PRINT LOL", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
			}
#line 1188 "parser.tab.cc"
    break;

  case 34: // statement: identifier ASSIGN expression SEMI_COLON
#line 338 "parser.yy"
                                                                  {
				yylhs.value.as < Node * > () = new Node("SOMETHING ASSIGNED = TO SOMETHING", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1198 "parser.tab.cc"
    break;

  case 35: // statement: identifier LEFT_BRACKET expression RIGHT_BRACKET ASSIGN expression SEMI_COLON
#line 343 "parser.yy"
                                                                                                        {
				yylhs.value.as < Node * > () = new Node("SOMETHING [ASSIGNED] = TO SOMETHING", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1209 "parser.tab.cc"
    break;

  case 36: // reqStatement: %empty
#line 352 "parser.yy"
                     { 	yylhs.value.as < Node * > () = new Node("statements", "", yylineno);}
#line 1215 "parser.tab.cc"
    break;

  case 37: // reqStatement: reqStatement statement
#line 353 "parser.yy"
                                                 {
				yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();				
				Node * reqSTMT = new Node("statement", "", yylineno);
				reqSTMT->children.push_back(yystack_[0].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(reqSTMT);

			}
#line 1227 "parser.tab.cc"
    break;

  case 38: // expression: expression PLUSOP expression
#line 365 "parser.yy"
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
#line 1242 "parser.tab.cc"
    break;

  case 39: // expression: expression MINUSOP expression
#line 375 "parser.yy"
                                            {
				yylhs.value.as < Node * > () = new Node("SubExpression", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				/* printf("r2 "); */
			}
#line 1253 "parser.tab.cc"
    break;

  case 40: // expression: expression MULTOP expression
#line 381 "parser.yy"
                                           {
				yylhs.value.as < Node * > () = new Node("MultExpression", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				/* printf("r3 "); */
			}
#line 1264 "parser.tab.cc"
    break;

  case 41: // expression: expression AND expression
#line 387 "parser.yy"
                                        {
				yylhs.value.as < Node * > () = new Node("AND", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1274 "parser.tab.cc"
    break;

  case 42: // expression: expression OR expression
#line 392 "parser.yy"
                                                   {
				yylhs.value.as < Node * > () = new Node("OR", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1284 "parser.tab.cc"
    break;

  case 43: // expression: expression LESS_THAN expression
#line 397 "parser.yy"
                                                          {
				yylhs.value.as < Node * > () = new Node("LESS_THAN", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1294 "parser.tab.cc"
    break;

  case 44: // expression: expression MORE_THAN expression
#line 402 "parser.yy"
                                                          {
				yylhs.value.as < Node * > () = new Node("MORE_THAN", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1304 "parser.tab.cc"
    break;

  case 45: // expression: expression EQUAL expression
#line 407 "parser.yy"
                                                      {
				yylhs.value.as < Node * > () = new Node("EQUAL", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1314 "parser.tab.cc"
    break;

  case 46: // expression: expression LEFT_BRACKET expression RIGHT_BRACKET
#line 414 "parser.yy"
                                                                           {
				yylhs.value.as < Node * > () = new Node("expression LEFT_BRACKET expression RIGHT_BRACKET", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1324 "parser.tab.cc"
    break;

  case 47: // expression: expression DOT LENGTH
#line 419 "parser.yy"
                                                {
				yylhs.value.as < Node * > () = new Node("expression DOT LENGTH", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
			}
#line 1333 "parser.tab.cc"
    break;

  case 48: // expression: TRUE
#line 428 "parser.yy"
                               {
				yylhs.value.as < Node * > () = new Node("TRUE", "True", yylineno);
			}
#line 1341 "parser.tab.cc"
    break;

  case 49: // expression: FALSE
#line 431 "parser.yy"
                                {
				yylhs.value.as < Node * > () = new Node("FALSE", "False", yylineno);
			}
#line 1349 "parser.tab.cc"
    break;

  case 50: // expression: THIS
#line 440 "parser.yy"
                               {
				yylhs.value.as < Node * > () = new Node("THIS", "", yylineno);
			}
#line 1357 "parser.tab.cc"
    break;

  case 51: // expression: NEW INT LEFT_BRACKET expression RIGHT_BRACKET
#line 443 "parser.yy"
                                                                        {
				yylhs.value.as < Node * > () = new Node("NEW INT LEFT_BRACKET expression RIGHT_BRACKET", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
			}
#line 1366 "parser.tab.cc"
    break;

  case 52: // expression: NEW identifier LP RP
#line 450 "parser.yy"
                                               { yylhs.value.as < Node * > () = new Node("NEW identifier LP RP", "", yylineno);
									 yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
			}
#line 1374 "parser.tab.cc"
    break;

  case 53: // expression: EXCLAMATION_MARK expression
#line 455 "parser.yy"
                                                      {
				yylhs.value.as < Node * > () = new Node("EXCLAMATION_MARK expression", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
			}
#line 1383 "parser.tab.cc"
    break;

  case 54: // expression: factor
#line 467 "parser.yy"
                              { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); /* printf("r4 ");*/ }
#line 1389 "parser.tab.cc"
    break;

  case 55: // expression: identifier
#line 468 "parser.yy"
                                     { /* empty because we have it in root */ yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();  }
#line 1395 "parser.tab.cc"
    break;

  case 56: // expression: expression DOT identifier LP arguments RP
#line 473 "parser.yy"
                                     {
				yylhs.value.as < Node * > () = new Node("exp DOT ident LP exp COMMA exp RP", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ()); /* `new A()` */
        		yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ()); /* `a2` */
				yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
				
			}
#line 1407 "parser.tab.cc"
    break;

  case 57: // expression: expression DOT identifier LP arguments RP dotExpTest
#line 481 "parser.yy"
                                                {
				yylhs.value.as < Node * > () = new Node("functionCall", "", yylineno);
				yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ()); /* `new A()` */
        		yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ()); /* `a2` */
				yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				
			}
#line 1420 "parser.tab.cc"
    break;

  case 58: // dotExpTest: DOT identifier LP arguments RP
#line 495 "parser.yy"
                                           { yylhs.value.as < Node * > () = new Node("DOT identifier LP arguments RP", "", yylineno);
											  yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
											  yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
											}
#line 1429 "parser.tab.cc"
    break;

  case 59: // dotExpTest: DOT identifier LP arguments RP dotExpTest
#line 500 "parser.yy"
                                                                  { yylhs.value.as < Node * > () = new Node("DOT identifier LP arguments RP dotExpTest", "", yylineno);
														yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
														yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
														yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
				}
#line 1439 "parser.tab.cc"
    break;

  case 60: // dotExpTest: DOT LENGTH
#line 505 "parser.yy"
                                    { yylhs.value.as < Node * > () = new Node("DOT LENGTH", "", yylineno); }
#line 1445 "parser.tab.cc"
    break;

  case 61: // arguments: %empty
#line 511 "parser.yy"
                  { yylhs.value.as < Node * > () = new Node("empty argument", "", yylineno); }
#line 1451 "parser.tab.cc"
    break;

  case 62: // arguments: argument_list
#line 512 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1457 "parser.tab.cc"
    break;

  case 63: // argument_list: expression
#line 515 "parser.yy"
                          { yylhs.value.as < Node * > () = new Node("argument_list", "", yylineno);  yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());}
#line 1463 "parser.tab.cc"
    break;

  case 64: // argument_list: argument_list COMMA expression
#line 516 "parser.yy"
                                              {
				yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
				Node* arg = new Node("argument", "", yylineno);
				arg->children.push_back(yystack_[0].value.as < Node * > ());
				yylhs.value.as < Node * > ()->children.push_back(arg);
			 
			 }
#line 1475 "parser.tab.cc"
    break;

  case 65: // identifier: IDENTIFIER
#line 527 "parser.yy"
                       { yylhs.value.as < Node * > () = new Node("identifier", yystack_[0].value.as < std::string > (), yylineno); }
#line 1481 "parser.tab.cc"
    break;

  case 66: // factor: INTEGER_LITERAL
#line 534 "parser.yy"
                                      {  yylhs.value.as < Node * > () = new Node("INT", yystack_[0].value.as < std::string > (), yylineno); /* printf("r5 ");  Here we create a leaf node Int. The value of the leaf node is $1 */}
#line 1487 "parser.tab.cc"
    break;

  case 67: // factor: LP expression RP
#line 536 "parser.yy"
                               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); /* printf("r6 ");  simply return the expression */}
#line 1493 "parser.tab.cc"
    break;


#line 1497 "parser.tab.cc"

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


  const signed char parser::yypact_ninf_ = -68;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -24,     3,    15,   -68,    17,   -16,   -68,   -16,    45,    18,
     -68,    28,    33,   -68,   -16,    37,    -3,    43,    31,    62,
     -68,   -16,    51,    -3,   -68,    -3,    50,    60,    63,    -3,
      78,    53,   -16,    51,    70,   -68,   -68,   -16,   -68,    -3,
      64,     7,    97,   100,   -16,   -68,   -68,    73,    -3,   103,
      94,   -16,   105,    79,    -3,   109,   -68,   106,    -3,   128,
     -16,   -68,   -16,   114,   133,    95,   -68,   -68,   119,   -68,
     136,   138,   142,   191,   -16,   127,   -68,   -11,    95,   -15,
      44,   191,   191,   191,   191,   -68,   -68,   -68,    -1,   191,
     -68,   143,   -68,   -68,   115,   -68,   191,   191,   134,   -68,
     -11,   -68,   -68,   206,   230,   248,   266,   141,   155,   314,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   -20,
     -68,   -68,   278,   161,   -68,    93,   -15,   125,   -15,   -68,
     191,   160,     1,     1,    20,   337,   326,    32,    32,   348,
     290,   -68,   162,   150,   -68,   152,   146,   -68,   -68,   302,
     -68,   -68,   191,   191,   -68,   -15,   -68,   314,   170,   137,
     179,   -68,   166,   191,   -68,   -17,   -68,   314,   -68,   180,
     191,   185,   166,   -68
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     0,     1,     0,     0,     4,
      65,     0,     0,     3,     0,     0,    12,     0,     0,     9,
       8,     0,    28,    13,    10,    12,     0,     0,     0,     0,
       0,    25,     0,    28,     0,     7,    14,     0,     5,     0,
       0,     0,     0,     0,     0,    15,     6,     0,    21,     0,
       0,     0,     0,    22,    21,     0,    23,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    24,    18,     0,    36,
       0,     0,     0,    16,     0,     0,    20,    10,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,     0,     0,
      66,     0,    55,    54,     0,    26,     0,     0,     0,    36,
       0,    29,    37,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    19,     0,     0,    27,     0,     0,     0,     0,    67,
       0,     0,    38,    39,    40,    41,    42,    43,    44,    45,
       0,    47,     0,     0,    34,     0,    30,    33,    32,     0,
      52,    46,    61,     0,    11,     0,    51,    63,     0,    62,
       0,    31,    56,     0,    35,     0,    57,    64,    60,     0,
      61,     0,    58,    59
  };

  const short
  parser::yypgoto_[] =
  {
     -68,   -68,   -68,   -68,   -68,    61,   -68,   169,   -68,   117,
     129,   147,   -68,   -68,   167,   -67,   113,   -19,    30,    34,
     -68,    -5,   -68
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,     9,    21,     4,    22,    23,    75,
      65,    52,    53,    30,    31,    76,    80,   157,   166,   158,
     159,    92,    93
  };

  const unsigned char
  parser::yytable_[] =
  {
      11,   141,    12,    19,   168,   107,   112,    96,    69,    17,
       1,    24,    99,   102,    97,     6,    28,    70,    24,   118,
      24,   119,    71,    72,    24,    10,    20,    40,    10,    10,
      10,    46,    43,     5,    24,   110,   111,   112,   118,    49,
     119,    39,    10,    24,    10,    13,    56,     7,    14,    24,
     118,    15,   119,    24,    91,    64,    16,    66,   102,   146,
      77,   148,   103,   104,   105,   106,    25,    69,   101,    94,
     109,    18,    26,    77,   100,   100,    70,   122,   123,    35,
      27,    71,    72,   108,    32,    29,    34,    39,   161,    10,
      37,   132,   133,   134,   135,   136,   137,   138,   139,   140,
      44,    19,    38,    42,    47,    36,    45,    48,    50,    51,
      54,   149,    55,    57,   142,    51,    69,   145,    69,    62,
     100,   100,    58,   100,    20,    70,    74,    70,    60,    61,
      71,    72,    71,    72,   160,    73,    63,    67,    10,    74,
      10,    68,    79,    81,   167,    82,   110,   111,   112,    83,
     100,    95,   113,   114,   115,   116,   117,   121,   124,   130,
     169,   118,   131,   119,   110,   111,   112,   147,   150,   152,
     113,   114,   115,   116,   117,   153,   154,   155,   162,   118,
     163,   119,   110,   111,   112,   120,   165,   170,   113,   114,
     115,   116,   117,   172,    33,    98,    78,   118,    84,   119,
      41,    59,   173,   144,   171,    85,    86,    87,    88,   110,
     111,   112,   125,    89,   126,   113,   114,   115,   116,   117,
       0,   164,     0,     0,   118,     0,   119,     0,     0,     0,
       0,     0,     0,   110,   111,   112,    10,    90,   127,   113,
     114,   115,   116,   117,     0,     0,     0,     0,   118,     0,
     119,   110,   111,   112,     0,     0,   128,   113,   114,   115,
     116,   117,     0,     0,     0,     0,   118,     0,   119,   110,
     111,   112,     0,     0,   129,   113,   114,   115,   116,   117,
       0,   110,   111,   112,   118,     0,   119,   113,   114,   115,
     116,   117,     0,   110,   111,   112,   118,   143,   119,   113,
     114,   115,   116,   117,     0,   110,   111,   112,   118,   151,
     119,   113,   114,   115,   116,   117,     0,   110,   111,   112,
     118,   156,   119,   113,   114,   115,   116,   117,     0,   110,
     111,   112,   118,     0,   119,   113,     0,   115,   116,   117,
     110,   111,   112,     0,   118,     0,   119,     0,   115,   116,
     117,   110,   111,   112,     0,   118,     0,   119,     0,   115,
     116,     0,     0,     0,     0,     0,   118,     0,   119
  };

  const short
  parser::yycheck_[] =
  {
       5,    21,     7,     6,    21,     6,     5,    18,    23,    14,
      34,    16,    79,    80,    25,     0,    21,    32,    23,    18,
      25,    20,    37,    38,    29,    45,    29,    32,    45,    45,
      45,    24,    37,    30,    39,     3,     4,     5,    18,    44,
      20,    34,    45,    48,    45,     0,    51,    30,    30,    54,
      18,    23,    20,    58,    73,    60,    23,    62,   125,   126,
      65,   128,    81,    82,    83,    84,    23,    23,    24,    74,
      89,    34,    41,    78,    79,    80,    32,    96,    97,    19,
      18,    37,    38,    88,    23,    34,    36,    34,   155,    45,
      29,   110,   111,   112,   113,   114,   115,   116,   117,   118,
      39,     6,    24,    33,     7,    42,    42,     7,    35,    48,
       7,   130,    18,     8,   119,    54,    23,    24,    23,    58,
     125,   126,    43,   128,    29,    32,    65,    32,    19,    23,
      37,    38,    37,    38,   153,    40,     8,    23,    45,    78,
      45,     8,    23,     7,   163,     7,     3,     4,     5,     7,
     155,    24,     9,    10,    11,    12,    13,    42,    24,    18,
     165,    18,     7,    20,     3,     4,     5,    42,     8,     7,
       9,    10,    11,    12,    13,    25,    24,    31,     8,    18,
      43,    20,     3,     4,     5,    42,    20,     7,     9,    10,
      11,    12,    13,     8,    25,    78,    67,    18,     7,    20,
      33,    54,   172,    42,   170,    14,    15,    16,    17,     3,
       4,     5,    99,    22,     8,     9,    10,    11,    12,    13,
      -1,    42,    -1,    -1,    18,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    45,    46,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    18,    -1,
      20,     3,     4,     5,    -1,    -1,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    18,    -1,    20,     3,
       4,     5,    -1,    -1,     8,     9,    10,    11,    12,    13,
      -1,     3,     4,     5,    18,    -1,    20,     9,    10,    11,
      12,    13,    -1,     3,     4,     5,    18,    19,    20,     9,
      10,    11,    12,    13,    -1,     3,     4,     5,    18,    19,
      20,     9,    10,    11,    12,    13,    -1,     3,     4,     5,
      18,    19,    20,     9,    10,    11,    12,    13,    -1,     3,
       4,     5,    18,    -1,    20,     9,    -1,    11,    12,    13,
       3,     4,     5,    -1,    18,    -1,    20,    -1,    11,    12,
      13,     3,     4,     5,    -1,    18,    -1,    20,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    18,    -1,    20
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
      63,     7,     7,     7,     7,    14,    15,    16,    17,    22,
      46,    64,    68,    69,    68,    24,    18,    25,    56,    62,
      68,    24,    62,    64,    64,    64,    64,     6,    68,    64,
       3,     4,     5,     9,    10,    11,    12,    13,    18,    20,
      42,    42,    64,    64,    24,    63,     8,     8,     8,     8,
      18,     7,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    21,    68,    19,    42,    24,    62,    42,    62,    64,
       8,    19,     7,    25,    24,    31,    19,    64,    66,    67,
      64,    62,     8,    43,    42,    20,    65,    64,    21,    68,
       7,    66,     8,    65
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    47,    48,    49,    50,    51,    51,    52,    52,    52,
      52,    53,    54,    54,    55,    55,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    60,    61,    61,    61,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      65,    66,    66,    67,    67,    68,    69,    69
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     1,     6,     7,     3,     1,     1,
       1,    19,     0,     1,     3,     4,     1,     3,     0,     4,
       2,     0,     1,     2,     4,     1,    10,    11,     0,     3,
       5,     7,     5,     5,     4,     7,     0,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     3,     1,     1,
       1,     5,     4,     2,     1,     1,     6,     7,     5,     6,
       2,     0,     1,     1,     3,     1,     1,     3
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
       0,    72,    72,    75,    83,    90,   103,   125,   126,   127,
     128,   144,   177,   178,   182,   191,   203,   205,   214,   215,
     227,   239,   240,   243,   252,   271,   275,   292,   307,   313,
     318,   323,   329,   334,   338,   343,   352,   353,   365,   375,
     381,   387,   392,   397,   402,   407,   414,   419,   428,   431,
     440,   443,   450,   455,   467,   468,   472,   480,   495,   500,
     505,   511,   512,   515,   516,   527,   534,   536
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
#line 2108 "parser.tab.cc"

