#ifndef __REAL_H__
#define __REAL_H__

#include "Token.h"
#include "Tag.h"

class Real : public Token
{
public:
    const double value;
    Real(const double &v) : Token((int)Tag::REAL), value(v) {}
    double toString() { return value; }
};

#endif