#ifndef __$__REQUEST__CPP__
#define __$__REQUEST__CPP__ 1234
#include<http_rock>
using namespace http_rock;
void Response::createHeader()
{
char header[51];
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:%s\n\n",this->contentType);
::send(this->clientSocketDescriptor,header,strlen(header),0);
this->headerCreated=true;
}
Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->connectionClosed=false;
this->headerCreated=false;
this->contentType="text/html"; // default value
}
void Response::setClientSocketDescriptor(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
}
void Response::setContentType(string contentType)
{
this->contentType=contentType;
}
bool Response::isClosed()
{
return this->connectionClosed==true;
}
bool Response::isHeaderCreated()
{
return this->headerCreated==true;
}
void Response::send(string str)
{
if(str.length()==0) return;
if(!this->isHeaderCreated()) this->createHeader();
::send(this->clientSocketDescriptor,str.c_str(),str.length(),0);
}
void Response::close()
{
if(this->isClosed()) return;
closesocket(this->clientSocketDescriptor);
this->connectionClosed=true;
}
Response::~Response()
{
}
#endif