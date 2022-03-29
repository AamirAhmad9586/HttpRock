#include<iostream>
#include<dirent.h>
#include<forward_list>
#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<tm_utility>
#include<windows.h>
#include<signal.h>
using namespace tm_utility;
using namespace std;
struct Time
{
int hour,min,sec;
};
string getExtension(char * fileName)
{
int i;
for(i=0;fileName[i]!='\0' && fileName[i]!='.';i++);
if(fileName[i]=='\0') return string("");
return string(fileName+i+1);
}
void signalHandler(int signalCode)
{
if(signalCode==SIGINT)
{
printf("You can not press (ctr+c) while we are processing, please wait for some time...");
return;
}
}
int main()
{
signal(SIGINT,signalHandler);
string tplFileFolderName="";
FILE *file=fopen("conf/config.conf","r");
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

char s[500];
getcwd(s,500);
string currentDirectoryPath(s);
string pathToWork=currentDirectoryPath+string("\\work");
string pathToTPL=pathToWork+string("\\tpl.h");

SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]";
SetConsoleTextAttribute(hConsole,7);
cout<<" scanning for projects..."<<endl;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --------------------< ";
SetConsoleTextAttribute(hConsole,3);
cout<<currentDirectoryPath;
SetConsoleTextAttribute(hConsole,15);
cout<<" >--------------------"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"create or re-generate : ";
SetConsoleTextAttribute(hConsole,15);
cout<<pathToWork<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;

bool hasTPLFile=false;
bool printed=false;
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
if(key==string("tplFileFolderName"))
{
tplFileFolderName=value;
break;
}
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
if(key==string("tplFileFolderName")) tplFileFolderName=value;
}
fclose(file);
} // file!=NULL ends
DIR *dr=opendir(tplFileFolderName.c_str());
struct dirent *en;
forward_list<string> tplFiles;
if(dr)
{
en=readdir(dr);
while(en!=NULL)
{
if(getExtension(en->d_name)=="tpl")
{
tplFiles.push_front(string(en->d_name));
hasTPLFile=true;
}
en=readdir(dr);
}
closedir(dr);
}
forward_list<string>::iterator iter=tplFiles.begin();
FILE *file1,*file2,*file3;
string fileName,line,tmpStr,variableName,tmp,tplFileName,newFileName,newTplFileName;
char g;
int i,howMany,tc1,tc2,diff;
struct stat stbuf;
time_t ttime;
struct tm *fileNameDate,*tplFileNameDate;
string fileNameModifiedDate,tplFileNameModifiedDate;
TMDate fileNameModifiedTMDate,tplFileNameModifiedTMDate;
bool createTPLFile=false;
Time fileNameTime,tplFileNameTime;


SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"creating : ";
SetConsoleTextAttribute(hConsole,15);
cout<<"\""<<pathToTPL<<"\" ";
SetConsoleTextAttribute(hConsole,7);
cout<<"file-"<<endl;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;


dr=opendir(pathToWork.c_str());
if(dr==NULL) mkdir(pathToWork.c_str());
file3=fopen(pathToTPL.c_str(),"w");
fputs("#ifndef __$__TPL__\n",file3);
fputs("#define __$__TPL__ 1234\n",file3);
fputs("#include<http_rock>\n",file3);
fputs("using namespace http_rock;\n",file3);
while(iter!=tplFiles.end())
{
fileName=(*iter).substr(0,(*iter).find("."))+string("_TPL");
line=string("void ")+fileName+string("(Request &request,Response &response);\n");
fputs(line.c_str(),file3);
++iter;
}
fputs("void registerTPLs(HttpRock *httpRock)\n",file3);
fputs("{\n",file3);




SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"checking for updates ";
SetConsoleTextAttribute(hConsole,15);
cout<<"(default-checking) ";
SetConsoleTextAttribute(hConsole,7);
cout<<"@ ";
SetConsoleTextAttribute(hConsole,3);
cout<<"http_rock ";
SetConsoleTextAttribute(hConsole,15);
cout<<"---"<<endl;


iter=tplFiles.begin();
while(iter!=tplFiles.end())
{
fileName=(*iter).substr(0,(*iter).find("."))+string("_TPL.cpp");
tplFileName=fileName.substr(0,fileName.find("_"))+string(".tpl");
newTplFileName=tplFileFolderName+string("\\")+fileName.substr(0,fileName.find("_"))+string(".tpl");
newFileName=pathToWork+string("\\")+fileName;


line=string("httpRock->get(\"/")+tplFileName+string("\",")+fileName.substr(0,fileName.length()-4)+string(");\n");
fputs(line.c_str(),file3);
// code to check modified date/time of "tpl and _TPL.cpp" file ---
stat(newFileName.c_str(),&stbuf);
ttime=stbuf.st_mtime;
fileNameDate=localtime(&ttime);
fileNameTime.hour=fileNameDate->tm_hour;
fileNameTime.min=fileNameDate->tm_min;
fileNameTime.sec=fileNameDate->tm_sec;
fileNameModifiedDate=to_string(fileNameDate->tm_mday)+"/"+to_string(fileNameDate->tm_mon)+"/"+to_string(fileNameDate->tm_year+1900);
fileNameModifiedTMDate=fileNameModifiedDate;
stat(newTplFileName.c_str(),&stbuf);
ttime=stbuf.st_mtime;
tplFileNameDate=localtime(&ttime);
tplFileNameTime.hour=tplFileNameDate->tm_hour;
tplFileNameTime.min=tplFileNameDate->tm_min;
tplFileNameTime.sec=tplFileNameDate->tm_sec;
tplFileNameModifiedDate=to_string(tplFileNameDate->tm_mday)+"/"+to_string(tplFileNameDate->tm_mon)+"/"+to_string(tplFileNameDate->tm_year+1900);
tplFileNameModifiedTMDate=tplFileNameModifiedDate;
if(tplFileNameModifiedTMDate>fileNameModifiedTMDate) createTPLFile=true;
else
{
if(tplFileNameModifiedTMDate==fileNameModifiedTMDate)
{
tc2=0;
tc2+=fileNameTime.hour*60*60;
tc2+=fileNameTime.min*60;
tc2+=fileNameTime.sec;
tc1=0;
tc1+=tplFileNameTime.hour*60*60;
tc1+=tplFileNameTime.min*60;
tc1+=tplFileNameTime.sec;
diff=tc1-tc2;
if(diff<0) createTPLFile=false;
else if(diff==0) createTPLFile=true;
else createTPLFile=true;
}
else createTPLFile=false;
}
if(createTPLFile==true)
{
if(!printed)
{
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] ";
SetConsoleTextAttribute(hConsole,7);
cout<<"changes detected - generate (tpl to cpp) file!"<<endl;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;
printed=true;
}


SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"creating : ";
SetConsoleTextAttribute(hConsole,15);
cout<<"\""<<newFileName<<"\" ";
SetConsoleTextAttribute(hConsole,7);
cout<<"file-"<<endl;
file1=fopen(newFileName.c_str(),"w");
file2=fopen(newTplFileName.c_str(),"r");
fputs("#include<iostream>\n",file1);
fputs("#include<http_rock>\n",file1);
fputs("using namespace http_rock;\n",file1);
fputs("using namespace std;\n",file1);
line=string("void ")+fileName.substr(0,fileName.find("."))+string("(Request &request,Response &response)\n");
fputs(line.c_str(),file1);
fputs("{\nstring html=\"\";\n",file1);
line="";
while(3)
{
g=fgetc(file2);
if(feof(file2)) break;
if(g!='\n')
{
line+=g;
continue;
}
for(i=0;i<line.length();i++)
{
if(line[i]=='"')
{
line.replace(i,1,"\\\"");
i++;
}
}
int startFrom=line.find("${");
if(startFrom!=-1)
{
int endAt=line.find('}',startFrom);
if(endAt!=-1)
{
howMany=endAt-startFrom+1;
tmpStr=line.substr(startFrom,howMany);
variableName=tmpStr.substr(2,tmpStr.length()-3);
tmp="html+=\""+line.substr(0,startFrom)+"\";\n";
fputs(tmp.c_str(),file1);
tmp="html+=request.getAttr(\""+variableName+"\");\n";
fputs(tmp.c_str(),file1);
tmp="html+=\""+line.substr(endAt+1,line.length()-endAt-1)+"\";\n";
fputs(tmp.c_str(),file1);
}
}
else
{
tmp="html+=\""+line.substr(0,line.length())+"\";\n";
fputs(tmp.c_str(),file1);
}
line="";
}
tmp="html+=\""+line.substr(0,line.length())+"\";\n";
fputs(tmp.c_str(),file1);
fputs("response.send(html);\n",file1);
fputs("response.close();\n",file1);
fputs("}\n",file1);
fclose(file2);
fclose(file1);
}
++iter;
}
fputs("}\n",file3);
fputs("#endif",file3);
fclose(file3);

if(createTPLFile==false)
{
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] ";
SetConsoleTextAttribute(hConsole,7);
cout<<"All (tpl to cpp) files are apdated!"<<endl;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
}

int exitCode;
if(hasTPLFile)
{
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"create or re-generate object files-"<<endl;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] ";
SetConsoleTextAttribute(hConsole,7);
cout<<"creating object files-,please wait for a moment..."<<endl;
exitCode=system("g++ -c work\\*.cpp -I http-rock-modules\\include -L http-rock-modules\\lib -lhttp_rock");
if(exitCode!=0) return 0;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"create or re-generate library file-"<<endl;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] ";
SetConsoleTextAttribute(hConsole,7);
cout<<"creating : ";
SetConsoleTextAttribute(hConsole,15);
cout<<"\""<<pathToWork<<"\\tplFiles.lib\" ";
SetConsoleTextAttribute(hConsole,7);
cout<<"library file-"<<endl;
exitCode=system("ar rcs work\\tplFiles.lib *.o");
if(exitCode!=0) return 0;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"checking for object files ";
SetConsoleTextAttribute(hConsole,15);
cout<<"(default-cleaning) ";
SetConsoleTextAttribute(hConsole,7);
cout<<"@ ";
SetConsoleTextAttribute(hConsole,3);
cout<<"http_rock ";
SetConsoleTextAttribute(hConsole,15);
cout<<"---"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] ";
SetConsoleTextAttribute(hConsole,7);
cout<<"deleting object files from - ";
SetConsoleTextAttribute(hConsole,15);
cout<<"\""<<pathToWork<<"\""<<endl;
exitCode=system("del *.o");
if(exitCode!=0) return 0;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
}
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"checking for : ";
SetConsoleTextAttribute(hConsole,15);
cout<<"\""<<currentDirectoryPath<<"\\Main.cpp\" (default-compile) ";
SetConsoleTextAttribute(hConsole,7);
cout<<"@ ";
SetConsoleTextAttribute(hConsole,3);
cout<<"http_rock ";
SetConsoleTextAttribute(hConsole,15);
cout<<"---"<<endl;
file=fopen("Main.cpp","rb");
if(file==NULL)
{
cout<<"[";
SetConsoleTextAttribute(hConsole,4);
cout<<"ERROR";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
cout<<"\""<<currentDirectoryPath<<"\\Main.cpp\" ";
SetConsoleTextAttribute(hConsole,7);
cout<<"not found ---"<<endl;
return 0;
}
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] ";
SetConsoleTextAttribute(hConsole,7);
cout<<"compiling ";
SetConsoleTextAttribute(hConsole,15);
cout<<"\""<<currentDirectoryPath<<"\"\\Main.cpp\" ";
SetConsoleTextAttribute(hConsole,7);
cout<<"file-,please wait for a moment..."<<endl;
if(hasTPLFile) exitCode=system("g++ -static Main.cpp -o Main.exe -I http-rock-modules\\include -I work -L work -L http-rock-modules\\lib -ltplFiles -lhttp_rock -lws2_32");
else exitCode=system("g++ -static Main.cpp -o Main.exe -I http-rock-modules\\include -I work -L work -L http-rock-modules\\lib -lhttp_rock -lws2_32");
if(exitCode!=0) return 0;
SetConsoleTextAttribute(hConsole,15);
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] \"";
cout<<currentDirectoryPath<<"\\Main.exe\" ";
SetConsoleTextAttribute(hConsole,7);
cout<<"created successfully-"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] "<<string("--------------------------------------------").append(currentDirectoryPath.length(),'-')<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"]"<<endl;
cout<<"[";
SetConsoleTextAttribute(hConsole,3);
cout<<"INFO";
SetConsoleTextAttribute(hConsole,15);
cout<<"] --- ";
SetConsoleTextAttribute(hConsole,2);
cout<<"starting server..."<<endl;
SetConsoleTextAttribute(hConsole,7);
exitCode=system("Main.exe");
if(exitCode!=0) return 0;
return 0;
}