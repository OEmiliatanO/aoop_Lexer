#ifndef __TYPE_H__
#define __TYPE_H__

#include "Word.h"

class Type : public Word
{
public:
    int width;
    Type(const string &s, const int &tag, const int &w = 0) : Word(s, tag), width(w){}
    static bool numeric(const Type &p); // implementation delay
    static Type Max(const Type &p1, const Type &p2); // implementation delay
    bool operator==(const Type &p) const; // implementation delay
};

#endif