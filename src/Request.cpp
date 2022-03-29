#ifndef __$__REQUEST__CPP__
#define __$__REQUEST__CPP__ 1234
#include<http_rock>
using namespace http_rock;
Request::Request()
{
this->method="";
this->resource="";
this->rowData="";
this->forwardString="";
}
void Request::setMethod(string method)
{
this->method=method;
}
string Request::getMethod()
{
return this->method;
}
void Request::setForwardString(string forwardString)
{
this->forwardString=forwardString;
}
string Request::getForwardString()
{
return this->forwardString;
}
void Request::setResource(string resource)
{
this->resource=resource;
}
string Request::getResource()
{
return this->resource;
}
void Request::setRowData(string rowData)
{
this->rowData=rowData;
}
string Request::getRowData()
{
return this->rowData;
}
void Request::setIsClientSideTechnologyResource(char isClientSideTechnologyResource)
{
this->isClientSideTechnologyResource=isClientSideTechnologyResource;
}
char Request::getIsClientSideTechnologyResource()
{
return this->isClientSideTechnologyResource;
}
void Request::forward(string forwardString)
{
this->forwardString=forwardString;
if(forwardString[0]=='/') this->forwardString=this->forwardString.substr(1);
}
void Request::setQueryStringDataMap(map<string,string> *queryStringDataMap)
{
this->queryStringDataMap=queryStringDataMap;
}
string Request::getParam(string key)
{
if(key.length()==0) return string("");
map<string,string>::iterator iter=this->queryStringDataMap->find(key);
if(iter==this->queryStringDataMap->end()) return string("");
return string(iter->second);
}
void Request::setAttr(string key,string value)
{
if(key.length()==0 || value.length()==0) return;
this->requestScopeMap.insert(pair<string,string>(key,value));
}
string Request::getAttr(string key)
{
if(key.length()==0) return string("");
map<string,string>::iterator iter=this->requestScopeMap.find(key);
if(iter==this->requestScopeMap.end()) return string("");
return string(iter->second);
}
Request::~Request()
{
if(this->queryStringDataMap) delete this->queryStringDataMap;
}
#endif