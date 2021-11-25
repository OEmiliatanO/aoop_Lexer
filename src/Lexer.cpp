#include "IOException.h"
#include "Lexer.h"
#include "Num.h"
#include "Real.h"
#include "Tag.h"
#include "Token.h"
#include "Type.h"
#include "Word.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <string>

using std::ios;
using std::ifstream;
using std::cout;
using std::endl;
using std::cin;
using std::string;

/* instance */
static const Word AND("&&", (int)Tag::AND);
static const Word OR("||", (int)Tag::OR);
static const Word EQ("==", (int)Tag::EQ);
static const Word NE("!=", (int)Tag::NE);
static const Word LE("<=", (int)Tag::LE);
static const Word GE(">=", (int)Tag::GE);
static const Word MINUS("minus", (int)Tag::MINUS);
static const Word TRUE("true", (int)Tag::TRUE);
static const Word FALSE("flas", (int)Tag::FALSE);
static const Word TEMP("t", (int)Tag::TEMP);

static const Word IF("if", (int)Tag::IF);
static const Word ELSE("else", (int)Tag::ELSE);
static const Word WHILE("while", (int)Tag::WHILE);
static const Word DO("do", (int)Tag::DO);
static const Word BREAK("break", (int)Tag::BREAK);

static const Type INT("int", (int)Tag::BASIC, 4);
static const Type FLOAT("float", (int)Tag::BASIC, 8);
static const Type CHAR("char", (int)Tag::BASIC, 1);
static const Type BOOL("bool", (int)Tag::BASIC, 1);

/* Type.h: operator==, numeric, max */
bool Type::operator==(const Type &p) const
{
    return this->lexeme == p.lexeme && this->tag == p.tag && this->width == p.width;
}

bool Type::numeric(const Type &p)
{
    if (p == CHAR || p == INT || p == FLOAT)
        return true;
    return false;
}

Type Type::Max(const Type &p1, const Type &p2)
{
    if (!numeric(p1) || !numeric(p2))
        return Type(" ", 0, 0);
    else if (p1 == FLOAT || p2 == FLOAT)
        return FLOAT;
    else if (p1 == INT || p2 == INT)
        return INT;
    else
        return CHAR;
}

/* Lexer.h: readch(), readch(char), scan */
Lexer::Lexer(const char fileName[]): line(1), peek(' '), file(fileName, ios::in)
{
    reserve(IF);
    reserve(ELSE);
    reserve(WHILE);
    reserve(DO);
    reserve(BREAK);
    reserve(TRUE);
    reserve(FALSE);
    reserve(INT);
    reserve(FLOAT);
    reserve(CHAR);
    reserve(BOOL);
}

void Lexer::readch()
{
    char ch;
    if (file.get(ch))
        peek = ch;
    else throw IOException("EOF");
}

bool Lexer::readch(const char &ch)
{
    readch();
    if (peek == ch) { peek = ' '; return true; }
    return false;
}

Token Lexer::scan()
{
    for ( ; ; readch())
    {
        if (peek == ' ' || peek == '\t') continue;
        else if (peek == '\n') ++line;
        else break;
    }

    if (file.peek() == EOF)
    {
        readch();
        return Token(' ');
    }
    else cout << "Token: " << std::setw(10) << std::setiosflags(std::ios::left);

    // symbol
    constexpr char symbol[6][3] = {"&&", "||", "==", "!=", "<=", ">="};
    const Word symbolWord[6] = {AND, OR, EQ, NE, LE, GE};
    
    for (int i = 0; i < 6; ++i)
    {
        if (peek == symbol[i][0])
            if (readch(symbol[i][1]))
            {
                cout << symbol[i];
                return symbolWord[i];
            }
            else
            {
                cout << symbol[i][0];
                return Token(symbol[i][0]);
            }
    }

    // digital
    if (isdigit(peek))
    {
        int res = 0;
        do
        {
            res *= 10;
            res += peek - '0';
            readch();
        }while(isdigit(peek));

        if (peek != '.') { cout << res; return Num(res); }

        double resd = res;
        double _t = 10;
        while(true)
        {
            readch();
            if (!isdigit(peek)) break;
            resd += (peek - '0') / _t;
            _t *= 10;
        }

        cout << resd;
        return Real(resd);
    }

    // letter
    if (isalpha(peek))
    {
        string buff;
        do
        {
            buff += peek;
            readch();
        }while(isalpha(peek));

        auto it = words.find(buff);
        if (it != words.end())
        {
            cout << it->second.lexeme;
            return it->second;
        }

        Word w(buff, (int)Tag::ID);
        reserve(w);
        cout << buff;
        return w;
    }

    Token tk(peek);
    cout << peek;
    peek = ' ';
    return tk;
}