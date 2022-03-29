#ifndef __$__HTTP_ROCK__CPP__
#define __$__HTTP_ROCK__CPP__ 1234
#include<http_rock>
#include<tm_utility>
#include<iostream>
#include<forward_list>
#include<threadmanager>
using namespace std;
using namespace http_rock;
using namespace tm_utility;
HttpRock::HttpRock()
{
this->portNumber=0;
this->staticFileFolderPath="";
this->requestString="";
this->closeServerSocket=false;
}
void HttpRock::useStatic(string staticFileFolderPath)
{
this->staticFileFolderPath=staticFileFolderPath;
this->callBack=NULL;
}
void HttpRock::get(string url,void (*functionAddress)(Request &,Response &))
{
if(url.length()==0 || functionAddress==NULL) return;
if(url.at(0)=='/') url=url.substr(1);
this->getTypeRequestMapping.insert(pair<string,void (*)(Request &,Response &)>(url,functionAddress));
}
void HttpRock::post(string url,void (*functionAddress)(Request &,Response &))
{
if(url.length()==0 || functionAddress==NULL) return;
if(url.at(0)=='/') url=url.substr(1);
this->postTypeRequestMapping.insert(pair<string,void (*)(Request &,Response &)>(url,functionAddress));
}
void HttpRock::initialize(Error &error)
{
this->ver=MAKEWORD(1,1);
WSAStartup(ver,&(this->wsaData));
this->serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(this->serverSocketDescriptor<0)
{
error.setError("Unable to create Socket.");
callBack(error);
return;
}
this->serverSocketInformation.sin_family=AF_INET;
this->serverSocketInformation.sin_port=htons(this->portNumber);
this->serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
int successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
error.setError(string("Unable to bind socket on port : ")+to_string(this->portNumber));
this->callBack(error);
return;
}
FILE *file=fopen("conf\\config.conf","r");
if(file!=NULL)
{
int equalIndex;
string line="",key,value;
char g;
while(2)
{
g=fgetc(file);
if(feof(file)) break;
if(g=='\n')
{
equalIndex=line.find('=');
if(equalIndex!=-1)
{
key=line.substr(0,equalIndex);
value=line.substr(equalIndex+1);
this->configurationMap.insert(pair<string,string>(key,value));
}
line="";
}
else
{
line+=g;
}
}
equalIndex=line.find('=');
if(equalIndex!=-1)
{
key=line.substr(0,equalIndex);
value=line.substr(equalIndex+1);
this->configurationMap.insert(pair<string,string>(key,value));
}
} // file!=NULL ends
}
void HttpRock::listen(int portNumber,void (*callBack)(Error &))
{
Error error;
this->portNumber=portNumber;
this->callBack=callBack;
this->initialize(error);
::listen(this->serverSocketDescriptor,10);
this->accept(&error);
}
void HttpRock::accept(Error *error)
{
int len=sizeof(this->clientSocketInformation);
int clientSocketDescriptor;
this->callBack(*error);
clientSocketDescriptor=::accept(this->serverSocketDescriptor,(struct sockaddr *)&(this->clientSocketInformation),&len);
if(clientSocketDescriptor<0)
{
error->setError("Unable to connect with client on port : "+to_string(this->portNumber));
this->callBack(*error);
return;
}
char requestBuffer[8192];
int bytesExtracted;
bytesExtracted=::recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
requestBuffer[bytesExtracted]='\0';
this->requestString=string(requestBuffer);
ThreadManager<void (*)(HttpRock*,int),HttpRock*,int> threadManager([](HttpRock *httpRock,int clientSocketDescriptor){
httpRock->requestProcessor(clientSocketDescriptor);
},this,clientSocketDescriptor);
threadManager.start();
}
Request* HttpRock::parseRequest(string requestString)
{
Request *request=new Request();
map<string,string> *queryStringDataMap=new map<string,string>;
request->setQueryStringDataMap(queryStringDataMap);
string key,value,piece,queryString;
string rowData;
char resource[1000];
char method[100];
int dataCount=0;
int startPoint,endPoint;
int lastAmpersendPosition;
int i,j;
for(i=0;requestString[i]!=' ';i++) method[i]=requestString[i];
method[i]='\0';
i+=2;
if(strcmp(method,"GET")==0)
{
for(j=0;requestString[i]!=' ' && requestString[i]!='?';i++,j++) resource[j]=requestString[i];
resource[j]='\0';
if(requestString[i]=='?' && requestString[i+1]!=' ')
{
i++;
for(j=i;requestString[j]!=' ';j++);
queryString=requestString.substr(i,(j-i));
cout<<"Query String : ("<<queryString<<")   : "<<queryString.length()<<endl;
if(queryString.length()!=0)
{
lastAmpersendPosition=queryString.find("&");
for(dataCount=1;lastAmpersendPosition!=-1;dataCount++) lastAmpersendPosition=queryString.find("&",lastAmpersendPosition+1);
endPoint=queryString.find("&");
startPoint=0;
while(endPoint!=-1)
{
piece=queryString.substr(startPoint,(endPoint-startPoint));
piece=URLDecoder::decode(piece);
key=piece.substr(0,piece.find("="));
value=piece.substr(piece.find("=")+1);
queryStringDataMap->insert(pair<string,string>(key,value));
startPoint=endPoint+1;
endPoint=queryString.find("&",startPoint);
}
piece=queryString.substr(startPoint);
piece=URLDecoder::decode(piece);
key=piece.substr(0,piece.find("="));
value=piece.substr(piece.find("=")+1);
queryStringDataMap->insert(pair<string,string>(key,value));
}
}
} // strcmp(method,"GET")==0 ends
else if(strcmp(method,"POST")==0)
{
for(j=0;requestString[i]!=' ';i++,j++) resource[j]=requestString[i];
resource[j]='\0';
if(requestString.find("Content-Type: application/json")!=-1)
{
// JSON row data parse section starts here
rowData=requestString.substr(requestString.rfind("\n")+1);
request->setRowData(rowData);
}
else
{
// for POST Query String Data
queryString=requestString.substr(requestString.rfind('\n')+1);
if(queryString.length()!=0)
{
lastAmpersendPosition=queryString.find("&");
for(dataCount=1;lastAmpersendPosition!=-1;dataCount++) lastAmpersendPosition=queryString.find("&",lastAmpersendPosition+1);
endPoint=queryString.find("&");
startPoint=0;
while(endPoint!=-1)
{
piece=queryString.substr(startPoint,(endPoint-startPoint));
piece=URLDecoder::decode(piece);
key=piece.substr(0,piece.find("="));
value=piece.substr(piece.find("=")+1);
queryStringDataMap->insert(pair<string,string>(key,value));
startPoint=endPoint+1;
endPoint=queryString.find("&",startPoint);
}
piece=queryString.substr(startPoint);
piece=URLDecoder::decode(piece);
key=piece.substr(0,piece.find("="));
value=piece.substr(piece.find("=")+1);
queryStringDataMap->insert(pair<string,string>(key,value));
}
}
} // strcmp(method,"POST")==0 ends
request->setMethod(string(method));
if(resource[0]=='\0') request->setIsClientSideTechnologyResource('Y');
else
{
request->setResource(string(resource));
request->setIsClientSideTechnologyResource(isClientSideResource(string(resource)));
}
return request;
}
void HttpRock::requestProcessor(int clientSocketDescriptor)
{
char responseBuffer[1024],header[1024];
cout<<"Request Arrived."<<endl;
cout<<this->requestString<<endl;
Request *request=this->parseRequest(this->requestString);
cout<<"Method : "<<request->getMethod()<<endl;
cout<<"Resource : "<<request->getResource()<<endl;
cout<<"Row Data : "<<request->getRowData()<<endl;
cout<<"Client Side Technology : "<<request->getIsClientSideTechnologyResource()<<endl;
cout<<"--------------------------------------------"<<endl;
Response response(clientSocketDescriptor);
FILE *file=NULL;
int fileLength;
int howMany;
int bytesSend;
// done done
while(2)
{
if(request->getIsClientSideTechnologyResource()=='Y')
{
FILE *file=NULL;
long howMany;
long bytesSend;
long fileLength;
if(request->getResource().length()==0)
{
map<string,string>::iterator it=this->configurationMap.find("homepage");
int homeFlag=0;
if(it!=configurationMap.end())
{
file=fopen(string(this->staticFileFolderPath+string("//")+it->second).c_str(),"rb");
if(file!=NULL) homeFlag=1;
}
if(homeFlag)
{
fseek(file,0,2);
fileLength=ftell(file);
fseek(file,0,0);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nconnection: close\n\n",fileLength);
send(clientSocketDescriptor,header,strlen(header),0);
printf("Header Send Successfully.\n");
howMany=1024;
bytesSend=0;
while(bytesSend<fileLength)
{
if((fileLength-bytesSend)<howMany) howMany=fileLength-bytesSend;
fread(responseBuffer,howMany,1,file);
send(clientSocketDescriptor,responseBuffer,howMany,0);
bytesSend+=howMany;
} // while loop ends
}
else
{
file=fopen(string(this->staticFileFolderPath+string("/")+string("index.html")).c_str(),"rb");
if(file==NULL)
{
file=fopen(string(this->staticFileFolderPath+string("/")+string("index.htm")).c_str(),"rb");
if(file==NULL)
{
// send 404 message by called send404() function
this->send404(clientSocketDescriptor);
}
else
{
// serve "index.htm"
fseek(file,0,2);
fileLength=ftell(file);
fseek(file,0,0);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nconnection: close\n\n",fileLength);
send(clientSocketDescriptor,header,strlen(header),0);
printf("Header Send Successfully.\n");
howMany=1024;
bytesSend=0;
while(bytesSend<fileLength)
{
if((fileLength-bytesSend)<howMany) howMany=fileLength-bytesSend;
fread(responseBuffer,howMany,1,file);
send(clientSocketDescriptor,responseBuffer,howMany,0);
bytesSend+=howMany;
} // while loop ends
}
}
else
{
// serve "index.html"
fseek(file,0,2);
fileLength=ftell(file);
fseek(file,0,0);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nconnection: close\n\n",fileLength);
send(clientSocketDescriptor,header,strlen(header),0);
printf("Header Send Successfully.\n");
howMany=1024;
bytesSend=0;
while(bytesSend<fileLength)
{
if((fileLength-bytesSend)<howMany) howMany=fileLength-bytesSend;
fread(responseBuffer,howMany,1,file);
send(clientSocketDescriptor,responseBuffer,howMany,0);
bytesSend+=howMany;
} // while loop ends
}
}
} // request->getResource().length()==0 ends
else
{
if(getExtension(request->getResource())==string("tpl"))
{
map<string,void (*)(Request &,Response &)>::iterator iter=this->getTypeRequestMapping.find(request->getResource());
if(iter==this->getTypeRequestMapping.end())
{
// send 404 error message by calling send404() function
send404(clientSocketDescriptor);
}
else
{
Response response(clientSocketDescriptor);
iter->second(*request,response);
// some login to forward request
}
}
else
{
file=fopen(string(this->staticFileFolderPath+string("/")+request->getResource()).c_str(),"rb");
if(file==NULL)
{
// send 404 error message by called send404() function
send404(clientSocketDescriptor);
}
else
{
fseek(file,0,2);
fileLength=ftell(file);
fseek(file,0,0);
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nconnection: close\n\n",getContentType(request->getResource()).c_str(),fileLength);
send(clientSocketDescriptor,header,strlen(header),0);
printf("Header Send Successfully.\n");
howMany=1024;
bytesSend=0;
while(bytesSend<fileLength)
{
if((fileLength-bytesSend)<howMany) howMany=fileLength-bytesSend;
fread(responseBuffer,howMany,1,file);
send(clientSocketDescriptor,responseBuffer,howMany,0);
bytesSend+=howMany;
} // while loop ends
} // tpl wala else ends
} // send as per Client Side Resource name wala else ends
} // request->getResource().length()==0 else ends
if(file) fclose(file);
} // request->getIsClientSideTechnologyResource()=='Y' ends
else
{
// this section is for Server Side Technology Resource
Response response(clientSocketDescriptor);
int found=0;
map<string,void (*)(Request &,Response &)>::iterator iter;
if(request->getMethod()==string("GET"))
{
iter=this->getTypeRequestMapping.find(request->getResource());
if(iter!=this->getTypeRequestMapping.end()) found=1;
}
else if(request->getMethod()==string("POST"))
{
iter=this->postTypeRequestMapping.find(request->getResource());
if(iter!=this->postTypeRequestMapping.end()) found=1;
}
if(found==0)
{
// send 404 error message by called send404
send404(clientSocketDescriptor);
}
else
{
iter->second(*request,response);
if(request->getForwardString().length()>0)
{
request->setResource(request->getForwardString());
request->setForwardString("");
request->setIsClientSideTechnologyResource(isClientSideResource(request->getResource()));
continue;
}
}
} // isClientSideTechnologyResource=='Y' else ends
break;
} // inner infinite loop ends because of request.forward("_____");
closesocket(clientSocketDescriptor);
}
void HttpRock::send404(int clientSocketDescriptor)
{
string response;
char header[100];
response="<!DOCTYPE html><html lang='en'><head></head><body><center><h1 style='color:red'>404 Error Message</h1><h2>Resource Not Found</h2></center></body></html>";
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nconnection: close\n\n",response.length());
send(clientSocketDescriptor,header,strlen(header),0);
send(clientSocketDescriptor,response.c_str(),response.length(),0);
printf("404 Error Message send successfully.\n");
}
HttpRock::~HttpRock()
{
while(true)
{
if(this->closeServerSocket==true) break;
this->accept(new Error());
}
}
#endif