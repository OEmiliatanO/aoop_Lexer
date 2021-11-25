#include <iostream>
#include <string>
#include "./src/IOException.h"
#include "./src/Lexer.h"
#include "./src/Num.h"
#include "./src/Real.h"
#include "./src/Tag.h"
#include "./src/Token.h"
#include "./src/Type.h"
#include "./src/Word.h"

using namespace std;

const string TAG_TB[] = { "AND", "BASIC", "BREAK", "DO", "ELSE", "EQ", "FALSE", "GE", "ID", "IF", "INDEX", "LE", "MINUS", "NE", "NUM", "OR", "REAL", "TEMP", "TRUE", "WHILE"};

int main(int argc, const char * argv[])
{
    Lexer lexer(argv[1]);
    try
    {
        while(true)
        {
            Token t = lexer.scan();
            cout << '(';
            if (t.tag < 256)
                cout << t.toString();
            else
                cout << TAG_TB[t.tag - 256];
            cout << ')' << '\n';
        }
    }
    catch(IOException &e)
    {
        cout << e.what() << '\n';
    }

    return 0;
}