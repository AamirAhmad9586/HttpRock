#ifndef __$__URLENCODER__CPP__
#define __$__URLENCODER__CPP__ 1234
#include<iostream>
#include<http_rock>
using namespace http_rock;
#include<tm_utility>
using namespace tm_utility;
using namespace std;
URLEncoder::URLEncoder(){}
string URLEncoder::encode(string str)
{
string encodedStr="";
char g;
for(int i=0;i<str.length();i++)
{
g=str[i];
if(g=='$') encodedStr+="%24";
else if(g=='(') encodedStr+="%28";
else if(g==')') encodedStr+="%29";
else if(g=='&') encodedStr+="%26";
else if(g=='+') encodedStr+="%2B";
else if(g==',') encodedStr+="%2C";
else if(g=='/') encodedStr+="%2F";
else if(g==':') encodedStr+="%3A";
else if(g==';') encodedStr+="%3B";
else if(g=='=') encodedStr+="%3D";
else if(g=='?') encodedStr+="%3F";
else if(g=='@') encodedStr+="%40";
else if(g==' ') encodedStr+='+';
else if(g=='#') encodedStr+="%23";
else if(g=='%') encodedStr+="%25";
else if(g=='{') encodedStr+="%7B";
else if(g=='}') encodedStr+="%7D";
else if(g=='|') encodedStr+="%7C";
else if(g=='\\') encodedStr+="%5C";
else if(g=='^') encodedStr+="%5E";
else if(g=='[') encodedStr+="%5B";
else if(g==']') encodedStr+="%5D";
else if(g=='`') encodedStr+="%60";
else if(g=='!') encodedStr+="%21";
else encodedStr+=g;
}
return encodedStr;
}
#endif