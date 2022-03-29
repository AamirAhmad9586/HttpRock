#ifndef __$__TMDATE__CPP__
#define __$__TMDATE__CPP__ 1234
#include<tm_utility>
#include<iostream>
#include<string.h>
#include<http_rock>
#include<time.h>
using namespace std;
using namespace tm_utility;
using namespace http_rock;
TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
this->dayOfMonth=now->tm_mday;
this->month=now->tm_mon+1;
this->year=now->tm_year+1900;
this->toDayNumber();
}
TMDate::TMDate(const TMDate &other)
{
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
this->dayNumber=other.dayNumber;
}
TMDate & TMDate::operator=(const TMDate &other)
{
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
this->dayNumber=other.dayNumber;
return *this;
}
int TMDate::getDayOfMonth()
{
return this->dayOfMonth;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::getYear()
{
return this->year;
}
int TMDate::isLeapYear(int year)
{
if(year%400==0) return 1;
else if(year%100==0) return 0;
else if(year%4==0) return 1;
else return 0;
}
TMDate::TMDate(const char *dateString)
{
int isValid,d,m,y;
this->isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}
}
void TMDate::fromDayNumber()
{
if(this->dayNumber==0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
return;
}
int x=this->dayNumber;
int d,m,y;
int dayInMonth;
int dayInYear;
y=1901;
while(2)
{
if(this->isLeapYear(y)) dayInYear=366;
else dayInYear=365;
if(x<=dayInYear) break;
x=x-dayInYear;
y++;
}
int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(this->isLeapYear(y)) months[1]=29;
m=0;
while(2)
{
dayInMonth=months[m];
if(x<=dayInMonth) break;
x=x-months[m];
m++;
}
m++;
d=x;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}
int TMDate::getDayOfWeek()
{
if(this->dayNumber==0) return 0;
int leftDays=this->dayNumber%7;
leftDays=leftDays+2;                       //1-Sun,2-Mon,3-Wed...... and "in 01/01/1901 day is Tue" means 1-Tue
if(leftDays>7) leftDays%=7;
return leftDays;
}
void TMDate::getDayOfWeekString(char *dayOfWeekString)
{
if(this->dayNumber==0)
{
*dayOfWeekString='\0';
return;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekString,"Sunday");
if(dow==2) strcpy(dayOfWeekString,"Monday");
if(dow==3) strcpy(dayOfWeekString,"Tuesday");
if(dow==4) strcpy(dayOfWeekString,"Wednesday");
if(dow==5) strcpy(dayOfWeekString,"Thursday");
if(dow==6) strcpy(dayOfWeekString,"Friday");
if(dow==7) strcpy(dayOfWeekString,"Suterday");
}
void TMDate::getDayOfWeekShortString(char *dayOfWeekShortString)
{
if(this->dayNumber==0)
{
*dayOfWeekShortString='\0';
return;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekShortString,"Sun");
if(dow==2) strcpy(dayOfWeekShortString,"Mon");
if(dow==3) strcpy(dayOfWeekShortString,"Tue");
if(dow==4) strcpy(dayOfWeekShortString,"Wed");
if(dow==5) strcpy(dayOfWeekShortString,"Thu");
if(dow==6) strcpy(dayOfWeekShortString,"Fri");
if(dow==7) strcpy(dayOfWeekShortString,"Sut");
}
void TMDate::getMonthString(char *monthString)
{
if(this->dayNumber==0)
{
monthString[0]='\0';
return;
}
if(this->month==1) strcpy(monthString,"January");
if(this->month==2) strcpy(monthString,"Fabruary");
if(this->month==3) strcpy(monthString,"March");
if(this->month==4) strcpy(monthString,"April");
if(this->month==5) strcpy(monthString,"May");
if(this->month==6) strcpy(monthString,"June");
if(this->month==7) strcpy(monthString,"July");
if(this->month==8) strcpy(monthString,"Augest");
if(this->month==9) strcpy(monthString,"September");
if(this->month==10) strcpy(monthString,"Octuber");
if(this->month==11) strcpy(monthString,"November");
if(this->month==12) strcpy(monthString,"December");
}
void TMDate::getMonthShortString(char *monthShortString)
{
if(this->dayNumber==0)
{
monthShortString[0]='\0';
return;
}
if(this->month==1) strcpy(monthShortString,"Jan");
if(this->month==2) strcpy(monthShortString,"Fab");
if(this->month==3) strcpy(monthShortString,"Mar");
if(this->month==4) strcpy(monthShortString,"Apr");
if(this->month==5) strcpy(monthShortString,"May");
if(this->month==6) strcpy(monthShortString,"Jun");
if(this->month==7) strcpy(monthShortString,"Jul");
if(this->month==8) strcpy(monthShortString,"Aug");
if(this->month==9) strcpy(monthShortString,"Sep");
if(this->month==10) strcpy(monthShortString,"Oct");
if(this->month==11) strcpy(monthShortString,"Nov");
if(this->month==12) strcpy(monthShortString,"Dec");
}
TMDate & TMDate::operator=(string dateString)
{
*this=dateString.c_str();
return *this;
}
TMDate & TMDate::operator=(const char *dateString)
{
int isValid,d,m,y;
this->isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}
return *this;
}
void TMDate::toDayNumber()
{
int x=0;
int year=1901;
while(year<this->year)
{
if(isLeapYear(year)) x=x+366;
else x=x+365;
year++;
}
int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(this->year)) months[1]=29;
int ep=this->month-2;
for(int i=0;i<=ep;i++) x=x+months[i];
x=x+this->dayOfMonth;
this->dayNumber=x;
}
void TMDate::operator-=(int days)
{
if(this->dayNumber==0) return;
this->dayNumber-=days;
this->fromDayNumber();
}
void TMDate::operator+=(int days)
{
if(this->dayNumber==0) return;
this->dayNumber+=days;
this->fromDayNumber();
}
void TMDate::isValidDate(const char *dateString,int *isValid,int *d,int *m,int  *y)
{
int dd,mm,yy;
int separatorIndex1,separatorIndex2;
char sep,t,i;
int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
*isValid=0;
if(dateString==NULL) return;
int length=strlen(dateString);
if(length<8 || length>10) return;
if(!(dateString[1]=='/' || dateString[2]=='/' || dateString[1]=='-' || dateString[2]=='-')) return;
if(dateString[1]=='/' || dateString[1]=='-') separatorIndex1=1;
else separatorIndex1=2;
sep=dateString[separatorIndex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(separatorIndex1==2 && (dateString[1]<48 || dateString[1]>57)) return;
dd=dateString[0]-48;
if(separatorIndex1==2) dd=dd*10+dateString[1]-48;
if(dd==0) return;
i=separatorIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep)) return;
if(dateString[i+1]==sep) separatorIndex2=i+1;
else separatorIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return;
if(separatorIndex2==(i+2) && (dateString[i+1]<48 || dateString[i+1]>57)) return;
mm=dateString[i]-48;
if(separatorIndex2==i+2) mm=mm*10+(dateString[i+1]-48);
if(mm<1 || mm>12) return;
yy=0;
for(t=0,i=separatorIndex2+1;t<=3;t++,i++)
{
if(dateString[i]<48 || dateString[i]>57) return;
yy=yy*10+(dateString[i]-48);
}
if(yy<1901) return;
if(isLeapYear(yy)) months[1]=29;
if(dd<1 || dd>months[mm-1]) return;
*d=dd;
*m=mm;
*y=yy;
*isValid=1;
}
TMDate TMDate::operator+(int days)
{
if(this->dayNumber==0) return TMDate("00/00/0000");
TMDate temp;
temp.dayNumber=this->dayNumber+days;
if(temp.dayNumber<0) temp.dayNumber=0;
temp.fromDayNumber();
return temp;
}
TMDate TMDate::operator-(int days)
{
if(this->dayNumber==0) return TMDate("00/00/0000");
TMDate temp;
temp.dayNumber=this->dayNumber-days;
if(temp.dayNumber<0) temp.dayNumber=0;
temp.fromDayNumber();
return temp;
}
int TMDate::operator<(const TMDate &other)
{
return this->dayNumber<other.dayNumber;
}
int TMDate::operator>(const TMDate &other)
{
return this->dayNumber>other.dayNumber;
}
int TMDate::operator<=(const TMDate &other)
{
return this->dayNumber<=other.dayNumber;
}
int TMDate::operator>=(const TMDate &other)
{
return this->dayNumber>=other.dayNumber;
}
int TMDate::operator==(const TMDate &other)
{
return this->dayNumber==other.dayNumber;
}
int TMDate::operator!=(const TMDate &other)
{
return this->dayNumber!=other.dayNumber;
}
TMDate::~TMDate()
{
// do nothing
}
ostream & operator<<(ostream &out,TMDate &other)
{
out<<other.getDayOfMonth()<<"/"<<other.getMonth()<<"/"<<other.getYear();
return out;
}
#endif