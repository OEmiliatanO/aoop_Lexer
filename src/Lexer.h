#ifndef __LEXER_H__
#define __LEXER_H__

#include <map>
#include <fstream>
#include <utility>
#include "Word.h"

using std::map;
using std::ifstream;
using std::pair;

class Lexer
{
public:
    Lexer(const char fileName[]);

    int line;
    
    void reserve(const Word &w) { words.emplace(pair<string, Word>(w.lexeme, w)); }

    void readch(); // delay implementation
    bool readch(const char &ch); // delay implementation
    Token scan(); // delay implementation

private:
    char peek;
    map<string, Word> words;
    ifstream file;
};

#endif