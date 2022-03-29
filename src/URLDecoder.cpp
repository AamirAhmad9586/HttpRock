#ifndef __$__URLENCODER__CPP__
#define __$__URLENCODER__CPP__ 1234
#include<iostream>
#include<http_rock>
using namespace http_rock;
#include<tm_utility>
using namespace tm_utility;
using namespace std;
URLDecoder::URLDecoder(){}
string URLDecoder::decode(string str)
{
string decodedStr="";
char g;
for(int i=0;i<str.length();)
{
g=str[i];
if(g=='%')
{
string cc=str.substr(i,3);
if(cc=="%24") decodedStr+='$';
else if(cc=="%28") decodedStr+='(';
else if(cc=="%29") decodedStr+=')';
else if(cc=="%26") decodedStr+='&';
else if(cc=="%2B") decodedStr+='+';
else if(cc=="%2C") decodedStr+=',';
else if(cc=="%2F") decodedStr+='/';
else if(cc=="%3A") decodedStr+=':';
else if(cc=="%3B") decodedStr+=';';
else if(cc=="%3D") decodedStr+='=';
else if(cc=="%3F") decodedStr+='?';
else if(cc=="%40") decodedStr+='@';
else if(cc=="%23") decodedStr+='#';
else if(cc=="%25") decodedStr+='%';
else if(cc=="%7B") decodedStr+='{';
else if(cc=="%7D") decodedStr+='}';
else if(cc=="%7C") decodedStr+='|';
else if(cc=="%5C") decodedStr+='\\';
else if(cc=="%5E") decodedStr+='^';
else if(cc=="%5B") decodedStr+='[';
else if(cc=="%5D") decodedStr+=']';
else if(cc=="%60") decodedStr+='`';
else if(cc=="%21") decodedStr+='!';
else
{
decodedStr+=g;
i++;
continue;
}
i+=3;
}
else
{
if(g=='+') decodedStr+=' ';
else decodedStr+=g;
i++;
}
}
return decodedStr;
}
#endif