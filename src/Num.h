#ifndef __NUM_H__
#define __NUM_H__

#include "Token.h"
#include "Tag.h"

class Num : public Token
{
public:
    const int value;
    Num(const int &v): Token((int)Tag::NUM), value(v) {}
    int toString() { return value; }
};

#endif