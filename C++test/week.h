#include<iostream>
using namespace std;
class week{
	int year;
	int month;
	int day;
	public:
		void input(int y,int m,int d){
			year=y;
			month=m;
			day=d;
		}
		week()=default;
		week(int year,int month,int day):year(year),month(month),day(day){
		}
		int getweek_count(); 
		friend int getdays_count(week &a,week &b);
};
int getdays_count(week &a,week &b){
	int year1 = a.year;
	int month1 = a.month;
	int day1 = a.day;
	int judge = year1%400==0||year1%100!=0&&year1%4==0;
	int count = 0;
	if(year1==b.year&&month1==b.month&&day1==b.day)return 0;
	do{
		day1++;
		switch(month1){
			case 1:case 3:case 5:case 7:case 8:case 10:case 12:{
				if(day1>31){
					day1=1;
					month1++;
				}
				break;
			}
			case 2:{
				if(judge){
					if(day1>29){
						day1=1;
						month1++;
					}
				}
				else {
					if(day1>28){
						day1=1;
						month1++;
					}
				}
				break;
			}
			case 4:case 6:case 9:case 11:{
				if(day1>30){
					day1=1;
					month1++;
				}
				break;
			}
			default:{
				break;
			}
		}
		if(month1>12){
			month1=1;
			year1++;
		}
		count++;
		judge = year1%400==0||year1%100!=0&&year1%4==0;
	}while(year1!=b.year||month1!=b.month||day1!=b.day);
	return count;
}
int week::getweek_count(){
	int year1 = 2000;
	int month1 = 1;
	int day1 = 2;
	int judge = year1%400==0||year1%100!=0&&year1%4==0;
	int week_count = 1;
	int count = 1;
	do{
		day1++;
		switch(month1){
			case 1:case 3:case 5:case 7:case 8:case 10:case 12:{
				if(day1>31){
					day1=1;
					month1++;
				}
				break;
			}
			case 2:{
				if(judge){
					if(day1>29){
						day1=1;
						month1++;
					}
				}
				else {
					if(day1>28){
						day1=1;
						month1++;
					}
				}
				break;
			}
			case 4:case 6:case 9:case 11:{
				if(day1>30){
					day1=1;
					month1++;
				}
				break;
			}
			default:{
				break;
			}
		}
		if(month1>12){
			month1=1;
			year1++;
		}

		if(count==7){
			count=0;
			week_count++;
		}
		count++;
		judge = year1%400==0||year1%100!=0&&year1%4==0;
	}while(year1!=year||month1!=month||day1!=day);
	return week_count;
}
