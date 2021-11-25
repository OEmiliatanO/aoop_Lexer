#ifndef __IOEXCEPTION_H__
#define __IOEXCEPTION_H__

#include <exception>
#include <string>

using std::exception;
using std::string;

class IOException : public exception
{
public:
    IOException(const string &m): message(m) {}
    const char* what() const noexcept override { return message.c_str(); }
private:
    string message;
};

#endif