#ifndef __$__MYUTILITY__CPP
#define __$__MYUTILITY__CPP 1234
#include<tm_utility>
#include<iostream>
using namespace std;
using namespace tm_utility;
string tm_utility::getContentType(string resource)
{
string extension;
string contentType;
extension=getExtension(resource);
if(extension.length()==0) return "";
extension=toLowerCase(extension);
if(extension==string("html")) contentType=string("text/html");
else if(extension==string("htm")) contentType=string("text/html");
else if(extension==string("css")) contentType=string("text/css");
else if(extension==string("js")) contentType=string("text/javascript");
else if(extension==string("png")) contentType=string("image/png");
else if(extension==string("jpeg")) contentType=string("image/jpeg");
else if(extension==string("jpg")) contentType=string("image/jpeg");
else if(extension==string("ico")) contentType=string("image/x-icon");
else if(extension==string("aac")) contentType=string("audio/aac");
else if(extension==string("abw")) contentType=string("application/x-abiword");
else if(extension==string("arc")) contentType=string("application/x-freearc");
else if(extension==string("avi")) contentType=string("video/x-msvideo");
else if(extension==string("azw")) contentType=string("application/vnd.amazon.ebook");
else if(extension==string("bin")) contentType=string("application/actet-stream");
else if(extension==string("bmp")) contentType=string("image/bmp");
else if(extension==string("bz")) contentType=string("application/x-bzip");
else if(extension==string("bz2")) contentType=string("application/x-bzip2");
else if(extension==string("cda")) contentType=string("application/x-cdf");
else if(extension==string("csh")) contentType=string("application/x-csh");
else if(extension==string("csv")) contentType=string("test/csv");
else if(extension==string("doc")) contentType=string("application/msword");
else if(extension==string("docx")) contentType=string("application/vnd.openxmlformats-officedocument.wordprocessingml.document");
else if(extension==string("eot")) contentType=string("application/vnd.ms-fontobject");
else if(extension==string("epub")) contentType=string("application/epub+zip");
else if(extension==string("gz")) contentType=string("application/gzip");
else if(extension==string("gif")) contentType=string("image/gif");
else if(extension==string("ics")) contentType=string("text/calendar");
else if(extension==string("jar")) contentType=string("application/java-archive");
else if(extension==string("json")) contentType=string("application/json");
else if(extension==string("jsonld")) contentType=string("application/ld+json");
else if(extension==string("mid")) contentType=string("audio/midi");
else if(extension==string("midi")) contentType=string("audio/x-midi");
else if(extension==string("mjs")) contentType=string("text/javascript");
else if(extension==string("mp3")) contentType=string("audio/mpeg");
else if(extension==string("mp4")) contentType=string("video/mp4");
else if(extension==string("mpeg")) contentType=string("video/mpeg");
else if(extension==string("mpkg")) contentType=string("application/vnd.apple.installer+xml");
else if(extension==string("odp")) contentType=string("application/vnd.oasis.opendocument.presentation");
else if(extension==string("ods")) contentType=string("application/vnd.oasis.opendocument.spreadsheet");
else if(extension==string("odt")) contentType=string("application/vnd.oasis.opendocument.text");
else if(extension==string("oga")) contentType=string("audio/ogg");
else if(extension==string("ogv")) contentType=string("video/ogg");
else if(extension==string("ogx")) contentType=string("application/ogg");
else if(extension==string("opus")) contentType=string("audio/opus");
else if(extension==string("otf")) contentType=string("font/otf");
else if(extension==string("oga")) contentType=string("application/pdf");
else if(extension==string("php")) contentType=string("application/php");
else if(extension==string("ppt")) contentType=string("application/vnd.ms-powerpoint");
else if(extension==string("pptx")) contentType=string("application/vnd.openxmlformats-officedocument.presentationml.presentation");
else if(extension==string("rar")) contentType=string("application/vnd.rar");
else if(extension==string("rtf")) contentType=string("application/rtf");
else if(extension==string("sh")) contentType=string("application/x-sh");
else if(extension==string("svg")) contentType=string("image/svg+xml");
else if(extension==string("swf")) contentType=string("application/x-shockwave-flash");
else if(extension==string("tar")) contentType=string("application/x-tar");
else if(extension==string("tif")) contentType=string("image/tiff");
else if(extension==string("tiff")) contentType=string("image/tiff");
else if(extension==string("ts")) contentType=string("video/mp2t");
else if(extension==string("ttf")) contentType=string("font/ttf");
else if(extension==string("txt")) contentType=string("text/plain");
else if(extension==string("vsd")) contentType=string("application/vnd.visio");
else if(extension==string("wav")) contentType=string("audio/wav");
else if(extension==string("weba")) contentType=string("audio/webm");
else if(extension==string("webm")) contentType=string("video/webm");
else if(extension==string("webp")) contentType=string("image/webp");
else if(extension==string("woff")) contentType=string("font/woff");
else if(extension==string("woff2")) contentType=string("font/woff2");
else if(extension==string("xhtml")) contentType=string("application/xhtml+xml");
else if(extension==string("xls")) contentType=string("application/vnd.ms-excel");
else if(extension==string("xlsx")) contentType=string("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
else if(extension==string("xml")) contentType=string("application/xml");
else if(extension==string("xul")) contentType=string("application/vnd.mozilla.xul+xml");
else if(extension==string("zip")) contentType=string("application/zip");
else if(extension==string("3gp")) contentType=string("video/3gpp");
else if(extension==string("3g2")) contentType=string("video/3gpp2");
else if(extension==string("7z")) contentType=string("application/x-7z-compressed");
return contentType;
}
string tm_utility::getExtension(string resource)
{
if(resource.length()==0) return string("");
int index=resource.rfind('.');
if(index<=0 || index==(resource.length()-1)) return string("");
return resource.substr(index+1);
}
string tm_utility::toLowerCase(string str)
{
string result=str;
for(int i=0;i<result.length();i++) if(result[i]>=65 && result[i]<=90) result[i]=result[i]+32;
return result;
}
char tm_utility::isClientSideResource(string resource)
{
if(resource.length()==0) return 'Y';     // serve 'index.html' or 'index.htm'
int index=resource.find('.');
if(index==-1 || index==(resource.length()-1) || index==0) return 'N';
return 'Y';
}
#endif