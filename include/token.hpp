// token.hpp
#include <string>
#pragma once
enum TokenType
{
    KW_LOOPS_FOR,                                       // for
    KW_LOOPS_DO,                                        // dp
    KW_LOOPS_UNTIL,                                     // until
    KW_LOOPS_CONTINUE,                                  // continue
    KW_FUNC_FUNCTION,                                   // function
    KW_FUNC_RETURN,                                     // return
    KW_CONDITIONAL_IF,                                  // if
    KW_CONDITIONAL_ELSE,                                // else
    KW_CONDITIONAL_ELSEIF,                              // elseif
    KW_CONDITIONAL_CASEOF,                              // caseof
    KW_CONDITIONAL_CASE,                                // case
    KW_CONDITIONAL_DEFAULT,                             // defualt
    KW_WORDBASED_LOGICREL_OPS_AND,                      // and
    KW_WORDBASED_LOGICREL_OPS_OR,                       // or
    KW_WORDBASED_LOGICREL_OPS_NOT,                      // not
    KW_WORDBASED_LOGICREL_OPS_IS,                       // is
    KW_WORDBASED_LOGICREL_OPS_IN,                       // in
    KW_MISC_BREAK,                                      // break
    DT_SCALAR,                                          // i64 i32 i16 f64 f32 f16 bool
    DT_VECTOR,                                          // vector
    DT_MATRIX,                                          // matrix
    DT_STRING,                                          // string
    PUNCTUATION_LBRACE,                                 // {
    PUNCTUATION_RBRACE,                                 // }
    PUNCTUATION_LPAREN,                                 // (
    PUNCTUATION_RPAREN,                                 //)
    PUNCTUATION_LBRACKET,                               // [
    PUNCTUATION_RBRACKET,                               // ]
    PUNCTUATION_SEMICOLON,                              //;
    PUNCTUATION_ARROW,                                  // ->
    PUNCTUATION_COMMA,                                  // ,
    PUNCTUATION_ELLIPSIS,                               // ...
    PUNCTUATION_COLON,                                  // :
    OPERATORS_STANDARD_PLUSMINUS,                       // + -
    OPERATORS_STANDARD_STAR_SLASH_MOD,                  // * / %
    OPERATORS_MATRIX_TRANSPOSE,                         // '
    OPERATORS_MATRIX_DOT_STAR,                          // .*
    OPERATORS_MATRIX_DOT_SLASH,                         // ./
    OPERATORS_RELATIONAL_AND_COMPARISON_OPS_LESS,       // <
    OPERATORS_RELATIONAL_AND_COMPARISON_OPS_GREATER,    // >
    OPERATORS_RELATIONAL_AND_COMPARISON_OPS_LESS_EQ,    // <=
    OPERATORS_RELATIONAL_AND_COMPARISON_OPS_GREATER_EQ, // >=
    OPERATORS_ASSIGNMENT,                               //=
    IDENTIFIER,                                         //[a - zA - Z][a - zA - Z0 - 9_] *
    CONSTANTS_BOOL_CONSTANT,                            // 0 or 1 not produced by lexer, but by parser
    CONSTANTS_INT_LITERAL,                              //[0 - 9] +
    CONSTANTS_FLOAT_LITERAL,                            //[0 - 9] + . [0 - 9] +
    CONSTANTS_STRING_LITERAL,                           //" [^"\n]* "   (no escapes, one line)
    COMPILER_EOF,                                       // End of file
    COMPILER_ERROR,                                     // unrecognised lexeme; value part is
                                                        // the bad text, for the error report
    NUM_TOKEN_TYPES   // sentinel = 50, number of token types;
    };

struct Token
{
    TokenType type; //class part
    std::string value;// value part
    int line; // 1-based line number of the token in the source file
    int column;
};

const char *tokenTypeName(TokenType type);
TokenType lookupKeyword(const std::string &lexeme);
TokenType lookupOperator(const std::string &lexeme);
bool hasValuePart(TokenType type);
