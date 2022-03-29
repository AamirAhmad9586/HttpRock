#ifndef __$__ERROR__CPP__
#define __$__ERROR__CPP__ 1234
#include<http_rock>
using namespace http_rock;
Error::Error()
{
this->error="";
}
bool Error::hasError()
{
return this->error.length()!=0;
}
string Error::getError()
{
return this->error;
}
void Error::setError(string error)
{
this->error=error;
}
#endif