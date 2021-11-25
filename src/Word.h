#ifndef __WORD_H__
#define __WORD_H__

#include <string>
#include "Token.h"

using std::string;

class Word : public Token
{
public:
    string lexeme;
    Word(const string &s, const int &tag) : Token(tag), lexeme(s) {}
    string toString() { return lexeme; }
};

#endif