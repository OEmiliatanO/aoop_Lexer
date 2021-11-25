#ifndef __TOKEN_H__
#define __TOKEN_H__

class Token
{
public:
    const int tag;
    Token(const int t): tag(t) {}
    char toString() { return (char)tag; }
};

#endif