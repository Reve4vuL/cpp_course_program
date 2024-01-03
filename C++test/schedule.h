#include<iostream>
#include<iomanip>
#include<fstream>
#include<string> 
using namespace std;

class Time {
	public:
		int year;
		int month;
		int day;
		int hour;
		int minute;
		friend istream& operator>>(istream &in,Time &A) {
			in>>A.year>>A.month>>A.day>>A.hour>>A.minute;
			return in;
		}
		friend ostream& operator<<(ostream &out,Time A) {
			out<<A.year<<' '<<A.month<<' '<<A.day<<' '<<A.hour<<' '<<A.minute<<' ';
			return out;
		}
};
class Date {
	public:
		Date(int a,int b,int c,int d,int e) {
			time.year = a;
			time.month = b;
			time.day = c;
			time.hour = d;
			time.minute = e;
		}
		void showDate() {
			cout<<time.year<<'.'<<time.month<<'.'<<time.day<<' '<<time.hour<<':'<<time.minute<<endl;
		}
		Time time;
};
class schedule:public Date {
	public:
		schedule(int a = 0,int b = 0,int c = 0,int d = 0,int e = 0,string f = "NONE",string g = "NONE"):Date(a,b,c,d,e),place(f),title(g) {};
		friend istream &operator>>(istream &in,schedule &A) {
			in>>A.time.year>>A.time.month>>A.time.day>>A.time.hour>>A.time.minute>>A.title>>A.place;
			return in;
		}
		friend ostream &operator<<(ostream &out,schedule A) {
			out<<A.time.year<<' '<<A.time.month<<' '<<A.time.day<<' '<<A.time.hour<<' '<<A.time.minute<<' '<<A.title<<' '<<A.place<<'\n';
			return out;
		}
		void show() {
			cout<<time.year<<"年"<<setw(2)<<time.month<<"月"<<setw(2)<<time.day<<"日"<<' '<<setw(2)<<time.hour<<"时"<<setw(2);
			cout<<setfill('0')<<time.minute<<"分"<<setfill(' ')
			    <<setw(30)<<place<<setw(30)<<title<<endl;
		}
		string getplace() {
			return place;
		}
		string gettitle() {
			return title;
		}
		int operator==(schedule A);
		int operator>(schedule A);
		void input();
		void edit();
		void save(string name);
		void set(int,int,int);
	private:
		string place;
		string title;
};
//class party:public schedule{
//
//};
//class countdown:public schedule{
//
//};
void schedule::edit() {
	this->show();
	cout<<"请输入新的日程(日程时间、地点、标题)\n";
	cin>>this->time;
	cin>>this->place;
	cin>>this->title;
	cout<<"编辑成功\n";
	return;
}
int schedule::operator==(schedule A) {
	if(time.year == A.time.year&&time.month == A.time.month&&time.day == A.time.day)
		return 1;
	return 0;
}
int schedule::operator>(schedule A) {
	if(time.year>A.time.year)
		return 1;
	else if(time.year<A.time.year)
		return 0;
	else {
		if(time.month>A.time.month)
			return 1;
		else if(time.month<A.time.month)
			return 0;
		else {
			if(time.day>A.time.day)
				return 1;
			else if(time.day<A.time.day)
				return 0;
			else {
				if(time.hour>A.time.hour)
					return 1;
				else if(time.hour<A.time.hour)
					return 0;
				else {
					if(time.minute>A.time.minute)
						return 1;
					else
						return 0;
				}
			}
		}
	}
}
void schedule::save(string filename) {
	fstream file;
	file.open(filename);
	if(file.fail())
		cout<<"fail to open\n";
	else {
		file.seekp(0,ios::end);
		file<<this->time<<this->place<<' '<<this->title<<'\n';
	}
	file.close();
}
void schedule::set(int a,int b,int c) {
	time.year = a;
	time.month = b;
	time.day = c;
}
void schedule::input() {
	int x;
	cout<<"请输入年份："<<endl;
	cin>>this->time.year;
	cout<<"请输入月份："<<endl;
	while(1) {
		cin>>x;
		if(x>=1&&x<=12) {
			this->time.month = x;
			break;
		}
		cout<<"输入数据有误请重新输入！！！"<<endl;
	}
	cout<<"请输入日期："<<endl;
	int i = this->time.year%400==0||this->time.year%100!=0&&this->time.year%4==0;
	switch(this->time.month) {
		case (2): {
			while(1) {
				cin>>x;
				if(i) {
					if(x>=1&&x<=29) {
						this->time.day = x;
						break;
					}
					cout<<"输入数据有误请重新输入！！！"<<endl;
				} else {
					if(x>=1&&x<=28) {
						this->time.day = x;
						break;
					}
					cout<<"输入数据有误请重新输入！！！"<<endl;
				}
			}
			break;
		}
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: {
			while(1) {
				cin>>x;
				if(x>=1&&x<=31) {
					this->time.day = x;
					break;
				}
				cout<<"输入数据有误请重新输入！！！"<<endl;
			}
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11: {
			while(1) {
				cin>>x;
				if(x>=1&&x<=30) {
					this->time.day = x;
					break;
				}
				cout<<"输入数据有误请重新输入！！！"<<endl;
			}
			break;
		}
	}
	cout<<"请输入时："<<endl;
	while(1) {
		cin>>x;
		if(x>=0&&x<=23) {
			this->time.hour = x;
			break;
		}
		cout<<"输入数据有误请重新输入！！！"<<endl;
	}
	cout<<"请输入分："<<endl;
	while(1) {
		cin>>x;
		if(x>=0&&x<=59) {
			this->time.minute = x;
			break;
		}
		cout<<"输入数据有误请重新输入！！！"<<endl;
	}
	cout<<"请输入标题："<<endl;
	cin>>this->title;
	cout<<"请输入地点："<<endl;
	cin>>this->place;
	return;
}
