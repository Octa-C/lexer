// dfa.hpp

#pragma once

enum CharClass
{
    CC_LETTER,     // a-z A-Z
    CC_DIGIT,      // 0-9
    CC_UNDERSCORE, //_
    CC_WS,         // space, \t ,\r ,\f ,\v
    CC_NEWLINE,    //\n
    CC_QUOTE,      // "
    CC_DOT,        // .
    CC_MINUS,      // -
    CC_LT,         // <
    CC_GT,         // >
    CC_EQ,         // =
    CC_STAR_SLASH, // * /
    CC_SIMPLE,     // { } ( ) [ ] ; , : + ' % single char that cannot be extended to a longer operator
    CC_OTHER,      // any other character not in the above classes
    NUM_CLASSES    // sentinel=14, sizes the table's columns
};

enum State
{
    S_DEAD = 0, // error state
    S_START,    // 1 nothing consumed yet
    S_IDENT,    // 2 [a-zA-Z][a-zA-Z0-9_]* accepting
    S_INT,      // 3 [0-9]+ accepting
    S_INT_DOT,  // 4 [0-9]+\. not accepting
    S_FLOAT,    // 5 [0-9]+\.[0-9]+ accepting
    S_OP_DONE,  // 6 any operator /punctuator that cannot be extended
    // {} () ... -> <= >= .* ./ = * /
    // accepting resolved by lookup operator ()
    S_MINUS,    // 7 - accepting, can extend  to ->
    S_REL,      // 8 < or > accepting, but may extend to  <= or >=
    S_DOT,      // 9 . not accepting, waits for * / or .
    S_DOT_DOT,  // 10 .. not accepting, waits for . to form ...
    S_STR_BODY, // 11 " followed by anything but " or \n, not accepting,
    S_STR_END,  // 12 closing " seen, accepting"
    S_WS,       // 13 run of whitespaces  accepting but produces no token
    NUM_STATES  // sentinel=14 , sizes the table's rows
};

enum Action
{
    A_NONE,   // not an accepting state, go back to last accepting state
    A_WORD,   // lookupKeyword(lexeme), falls back to IDENTIFIER
    A_INT,    // CONSTANTS_INT_LITERAL
    A_FLOAT,  // CONSTANTS_FLOAT_LITERAL
    A_OP,     // lookupOperator(lexeme)
    A_STRING, // CONSTANTS_STRING_LITERAL
    A_SKIP    // whitespace: discard, scan again
};

CharClass charClassOf(unsigned char c);

extern const State TRANSITION[NUM_STATES][NUM_CLASSES];
extern const Action ACTION[NUM_STATES];
extern const char *STATE_NAMES[NUM_STATES];
extern const char* CLASS_NAMES[NUM_CLASSES];
