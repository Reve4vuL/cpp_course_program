#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <io.h>

#include "schedule.h"
#include "week.h"
#include "calender.h"
using namespace std;

enum colour {black,blue,green,lake_blue,red,purple,yellow,white,grey,baby_blue};
const string path = "F:\\文档\\面向对象\\实训\\2\\C++test\\id\\";

void clear_file(string filename);
void move(int x,int y, int forecolour,int backcolour);
void entranceshow();
int CountLines(string filename);//filename是带path的
int search(std::string name);
int createid();
void entrance();
void login();
void operation(string filename);
void sort_sch_in(schedule *sch,int n);
void sort_sch_out(string filename);
void createsch(string filename);
void showallsch(string filename);
void editsch(string filename);
void viewsch(string filename);
void zhanshi(schedule *sch,schedule *nsch,int year,int month,int day,int n);
void sortsch(schedule *sch,schedule *nsch,string n,int i,int nn);
void shuzhoushow(string filename);

struct cd {
	int aa;
	int pai;
};
int main() {
	system("COLOR 78");
	cout<<"-------------------------------------------------欢迎使用日程管理系统！-------------------------------------------------\n";
	entrance();
	cout<<"-------------------------------------------------欢迎再次使用,程序退出--------------------------------------------------\n";
	return 0;
}
void shuzhoushow(string filename) {
	fstream file;
	file.open(filename);
	int n = CountLines(filename);
	schedule *sch = new schedule[n];
	for(int i = 0; i<n; i++)file>>sch[i];
	cout<<"请输入输出模式"<<endl;
	cout<<"1.显示以当前时间为中心前后分别显示三个日程；"<<endl;
	cout<<"2.显示今日以后的日程"<<endl;
	cout<<"3.显示今日之前的日程"<<endl;
	cout<<"其他任意键退出"<<endl;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	int year = sys.wYear;
	int month = sys.wMonth;
	int day = sys.wDay;
	cd p[n];
	int a,b,c;
	int i,j=0;
	int sum = 0;
	for(i = 0; i<n; i++) {
		if(sch[i].time.year>=2000&&sch[i].time.year<=2100) {
			a = (sch[i].time.year - year)*365;
			b = (sch[i].time.month - month)*31;
			c = sch[i].time.day - day;
			p[sum].aa = a+b+c;
			p[sum].pai = i;
			sum++;
		}
	}
	int min=10000;
	int flag;
	cd huan;
//	for(i=0;i<sum;i++){
//		sch[p[i].pai].show();
//		cout<<"p["<<i<<"].aa = "<<p[i].aa<<endl;
//		cout<<"p["<<i<<"].pai = "<<p[i].pai<<endl;
//	}
	week w1,w2;
	for(i=0; p[i].aa<=0; i++);
	w1.input(year,month,day);
	cout<<"请输入你要玩的模式:" <<endl;
	int choose;
	cin>>choose;
	while(1) {
		if(choose == 1) {
			if(i>=3) {
				w2.input(sch[p[i-3].pai].time.year,sch[p[i-3].pai].time.month,sch[p[i-3].pai].time.day);
				cout<<"(-)1:"<<"过去已经"<< setw(4)<<getdays_count(w2,w1)<<"天:";
				sch[p[i-3].pai].show();
			} else {
				cout<<"(-)1:"<<"空"<<endl;
			}
			if(i>=2) {
				w2.input(sch[p[i-2].pai].time.year,sch[p[i-2].pai].time.month,sch[p[i-2].pai].time.day);
				cout<<"(-)2:"<<"过去已经"<< setw(4)<<getdays_count(w2,w1)<<"天:";
				sch[p[i-2].pai].show();
			} else {
				cout<<"(-)2:"<<"空"<<endl;
			}
			if(i>=1) {
				w2.input(sch[p[i-1].pai].time.year,sch[p[i-1].pai].time.month,sch[p[i-1].pai].time.day);
				cout<<"(-)3:"<<"过去已经"<< setw(4)<<getdays_count(w2,w1)<<"天:";
				sch[p[i-1].pai].show();
			} else {
				cout<<"(-)3:"<<"空"<<endl;
			}

			cout<<"--------现在时间为"<<year<<"."<<month<<"."<<day<<"--------"<<endl;
			if(sum-i>=1) {
				w2.input(sch[p[i].pai].time.year,sch[p[i].pai].time.month,sch[p[i].pai].time.day);
				cout<<"(+)1:"<<"距今还有"<< setw(4)<<getdays_count(w1,w2)<<"天:";
				sch[p[i].pai].show();
			} else {
				cout<<"(+)1:"<<"空"<<endl;
			}
			if(sum-i>=2) {
				w2.input(sch[p[i+1].pai].time.year,sch[p[i+1].pai].time.month,sch[p[i+1].pai].time.day);
				cout<<"(+)2:"<<"距今还有"<< setw(4)<<getdays_count(w1,w2)<<"天:";
				sch[p[i+1].pai].show();
			} else {
				cout<<"(+)2:"<<"空"<<endl;
			}
			if(sum-i>=3) {
				w2.input(sch[p[i+2].pai].time.year,sch[p[i+2].pai].time.month,sch[p[i+2].pai].time.day);
				cout<<"(+)3:"<<"距今还有"<< setw(4)<<getdays_count(w1,w2)<<"天:";
				sch[p[i+2].pai].show();
			} else {
				cout<<"(+)3:"<<"空"<<endl;
			}
		} else if(choose == 2) {
			int num;
			cout<<"请输入要查看的今日之后的日程个数："<<endl;
			cin >> num;
			for(j = 0; j<num; j++) {
				if(sum - i>=j+1) {
					w2.input(sch[p[i+j].pai].time.year,sch[p[i+j].pai].time.month,sch[p[i+j].pai].time.day);
					cout<<"(+)"<<j+1<<":"<<"距今还有"<< setw(4)<<getdays_count(w1,w2)<<"天:";
					sch[p[i+j].pai].show();
				} else {
					cout<<"(+)"<<j+1<<":"<<"空"<<endl;
				}
			}
		} else if(choose == 3) {
			int num;
			cout<<"请输入要查看的今日之前的日程个数："<<endl;
			cin>>num;
			for(j=0; j<num; j++) {
				if(i>=j+1) {
					w2.input(sch[p[i-j-1].pai].time.year,sch[p[i-j-1].pai].time.month,sch[p[i-j-1].pai].time.day);
					cout<<"(-)"<<j+1<<":"<<"过去已经"<< setw(4)<<getdays_count(w2,w1)<<"天:";
					sch[p[i-j-1].pai].show();
				} else {
					cout<<"(-)"<<j+1<<":"<<"空"<<endl;
				}
			}
		} else {
			break;
		}
		cout<<"请输入你要玩的模式:" <<endl;
		cin>>choose;
	}
	cout<<"按任意键退出！"<<endl;
	getchar();
	getchar();
}
//void entrance() {
//	entranceshow();
//	cout<<endl;
//	cout<<setw(50)<<"仅查看日历->1"<<'\n'<<setw(50)<<"注册或登录帐户->2"<<'\n';
//	int tmp;
//	cin>>tmp;
//	if(tmp == 1) {
//		system("cls");
//		//朱佳雯
//	} else if(tmp == 2) {
//		system("cls");
//		login();
//	}
//}
void entrance() {
	entranceshow();
	cout<<endl;
	cout<<setw(50)<<"仅查看日历->1"<<'\n'<<setw(50)<<"注册或登录帐户->2"<<'\n'<<setw(50)<<"退出->-1"<<endl;
	int tmp;
	cin>>tmp;
	while(1) {
		if(tmp==1||tmp==2) {
			if(tmp == 1) {
				system("cls");
				cout<<"请输入模式：1代表查看某年日历，2代表查看某年某月日历"<<endl;
				int x;
				cin>>x;
				while(1){
					if(x!=1&&x!=2){
					cout<<"数据有误，请重新输入！！！"<<endl;
					cin>>x;
					}
					else break;
				}
				showc(x);
				system("cls");
				entrance();
			} else if(tmp == 2) {
				system("cls");
				login();
			}
			cout<<"再玩一会吧(*≧з)(ε≦*)"<<endl;
			cout<<"别那么狠心输入-1嘛((●-з)(ε-●))"<<endl;
		} else if(tmp!=-1) {
			cout<<"别玩我(?`~′?)"<<endl;
			cout<<"劳驾在输入一遍(*'ε`*)" <<endl;
		} else if(tmp==-1) {
			break;
		}
		cin>>tmp;
	}
}
void login() {
	system("cls");
	string tmp;
	cout<<"请输入你在本计算机上的id:\n";
	cin>>tmp;
	if(search(tmp+".txt")) {
		cout<<"请输入密码：\n";
		string tmp1,tmp2;
		cin>>tmp1;
		fstream file;
		file.open(path+tmp+"code.txt");
		if(file.fail())
			cout<<"fail to code.........\n";
		file>>tmp2;
		if(tmp1 == tmp2)
			cout<<"登陆成功!\n";
		else {
			cout<<"密码有误，请重新登录！\n";
			getchar();
			getchar();
			login();
		}
		file.close();
		operation(path+tmp+".txt");
	} else {
		cout<<"在本地计算机上未找到你的帐户！\n是否创建？\n创建->1\n退出->2\n";
		int tmp1;
		cin>>tmp1;
		if(tmp1 == 1) {
			if(createid() == 1) {
				login();
			} else {
				entrance();
			}
		} else if(tmp1 == 2) {
			return;
		}
	}
}
void operation(string filename) {
	system("cls");
	cout<<"欢迎你！\n";
	cout<<"-------------------------------------------------查看日历->1-------------------------------------------------\n"
	    <<"-------------------------------------------------创建日程->2-------------------------------------------------\n"
	    <<"-------------------------------------------------编辑日程->3-------------------------------------------------\n"
	    <<"-------------------------------------------------查看日程->4-------------------------------------------------\n"
	    <<"-------------------------------------------------看时间表->5-------------------------------------------------\n"
	    <<"-------------------------------------------------修改密码->6-------------------------------------------------\n"
	    <<"------请输入操作代号（-1退出程序）-------\n";
	int tmp1;
	cin>>tmp1;
	schedule tmp2;
	if(tmp1 == -1) {
		system("cls");
		//退出
//		file.close();
		return;
	} else if(tmp1 == 1) {
		system("cls");
		cout<<"请输入模式：1代表查看某年日历，2代表查看某年某月日历"<<endl;
		int x;
		cin>>x;
		while(1){
			if(x!=1&&x!=2){
			cout<<"数据有误，请重新输入！！！"<<endl;
			cin>>x;
			}
			else break;
		}
		showc(x);
		system("cls");
		operation(filename);
		return;
	} else if(tmp1 == 2) {
		//创建日程
		createsch(filename);
		operation(filename);
		return;
	} else if(tmp1 == 3) {
		//编辑日程
		editsch(filename);
		operation(filename);
		return;
	} else if(tmp1 == 4) {
		//查看日程
		viewsch(filename);
		operation(filename);
		return;
	} else if(tmp1 == 5) {
		//看时间表
		shuzhoushow(filename);
		operation(filename);
	} else if(tmp1 == 6) {
		//修改密码
		cout<<"请输入旧的密码\n";
		string tmp1,tmp2,tmp3,tmp4;
		cin>>tmp1;
		int n = filename.find(".txt");
		tmp2 = filename.substr(0,n);
		tmp2 = tmp2 + "code.txt";
		fstream tmpfile;
		tmpfile.open(tmp2);
		tmpfile>>tmp3;
		if(tmpfile.fail())
			cout<<"error1\n";
		if(tmp3 == tmp1) {
			system("cls");
			cout<<"请输入新的密码\n";
			cin>>tmp4;
			if(tmpfile.fail()) {
				cout<<"error2\n";
			}
			tmpfile.seekp(0,ios::beg);
			tmpfile<<tmp4<<'\n';
			tmpfile.close();
			if(tmpfile.fail())
				cout<<"error\n";
			cout<<"密码修改成功，请重新登录!\n";
			getchar();
			getchar();
			login();
		}
	} else {
		operation(filename);
	}
}
//int CountLines(string filename) {
//	ifstream ReadFile;
//	int n=0;
//	string tmp;
//	ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件
//	if(ReadFile.fail()) { //文件打开失败:返回0
//		return 0;
//	} else { //文件存在
//		while(getline(ReadFile,tmp,'\n')) {
//			n++;
//		}
//		ReadFile.close();
//		return n;
//	}
//}
int search(std::string name) {
	//目标文件夹路径
	std::string inPath = path+"*";//遍历文件夹下的所有.txt文件
	//用于查找的句柄
	long handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(inPath.c_str(),&fileinfo);
	if(handle == -1)
		return 0;
	do {
		//找到的文件的文件名
		if(name == fileinfo.name)
			return 1;
	} while (!_findnext(handle,&fileinfo));
	_findclose(handle);
	return 0;
}
int createid() {
	string tmp,code,tmp1,tmp2;
	ofstream file1,file2;
	cout<<"请输入用户名：\n";
	cin>>tmp;
	cout<<"请输入密码：\n";
	cin>>code;
	tmp1 = path+tmp+".txt";
	tmp2 = path+tmp+"code.txt";
	file1.open(tmp1,ios::out);
	file2.open(tmp2,ios::out);
	file2<<code;
	file2.close();
	if(file1.fail()||file2.fail()) {
		cout<<"注册失败，请重试！\n";
		return 0;
	} else {
		cout<<"注册成功，请重新登录！";
	}
	return 1;
}
void sort_sch_in(schedule *sch,int n) {
	schedule tmp;
	for(int i = n-1; i>=0; i--)
		for(int j = 0; j<i; j++)
			if(sch[j]>sch[j+1]) {
				tmp = sch[j];
				sch[j] = sch[j+1];
				sch[j+1] = tmp;
			}
}
void createsch(string filename) {
	system("cls");
	cout<<"日程创建中...\n---------------（请按提示输入）---------------\n";
	//实现>>、<<运算符重载
	schedule tmp;
	tmp.input();
	tmp.save(filename);
	//日程排序
	sort_sch_out(filename);
	cout<<"日程创建成功,请按任意键继续\n";
	getchar();
	getchar();
}
void sort_sch_out(string filename) {
	fstream file;
	file.open(filename);
	if(file.fail())
		cout<<"fail to open\n";
	schedule *sch;
	schedule tmp;
	int n = CountLines(filename);
	sch = new schedule[n];
	for(int i = 0; i<n; i++)
		file>>sch[i];
	for(int i = n-1; i>=0; i--)
		for(int j = 0; j<i; j++) {
			if(sch[j]>sch[j+1]) {
				tmp = sch[j];
				sch[j] = sch[j+1];
				sch[j+1] = tmp;
			}
		}
	file.seekp(0,ios::beg);
	for(int i = 0; i<n; i++)
		file<<sch[i];
	delete[] sch;
	file.close();
	return;
}
void showallsch(string filename) {
	fstream file;
	file.open(filename);
	if(file.fail()) {
		cout<<"fail to open\n";
		return ;
	}
	schedule *sch;
	int n = CountLines(filename);
	sch = new schedule[n];
	for(int i = 0; i<n; i++)
		file>>sch[i];
	for(int i = 0; i<n; i++) {
		cout<<"第"<<setw(4)<<i<<"个日程：";
		sch[i].show();
	}
	delete[] sch;
	file.close();
}
//void editsch(string filename) {
////编辑日程
//	//初始化
//	fstream file;
//	file.open(filename);
//	int n = CountLines(filename);
//	schedule *sch = new schedule[n];
//	int tmp;
//	for(int i = 0; i<n; i++)
//		file>>sch[i];
//	//正式编辑
//
//	cout<<"你一共有"<<n<<"个日程，你要编辑哪个日程，选择你要编辑的编号！\n";
//	showallsch(filename);
//	cin>>tmp;
//	cout<<"你要删除他吗？\n"<<setw(15)<<"是----->1\n"<<setw(15)<<"否----->2\n";
//	int tmp0;
//	cin>>tmp0;
//	if(tmp0 == 1) {
//		for(int i = tmp; i<n-1; i++)
//			sch[i] = sch[i+1];
//		n--;
//		cout<<"删除成功,按任意键继续！\n";
//	} else if(tmp0 == 2) {
//		sch[tmp].edit();
//		sort_sch_in(sch,n);
//	} else {
//		return;
//	}
////	file.seekp(0,ios::beg);
//	file.close();
//	if(file.fail())
//		cout<<"fail to close\n";
//	clear_file(filename);
//	for(int i = 0; i<n; i++)
//		sch[i].save(filename);
//	//收尾
//	delete[] sch;
//	file.close();
//}
void editsch(string filename) {
//编辑日程
	//初始化
	fstream file;
	file.open(filename);
	int n = CountLines(filename);
	schedule *sch = new schedule[n];
	int tmp;
	for(int i = 0; i<n; i++)
		file>>sch[i];
	//正式编辑

	cout<<"你一共有"<<n<<"个日程，你要编辑哪个日程，选择你要编辑的编号！\n";
	showallsch(filename);
	cin>>tmp;
	cout<<"你要删除他吗？\n"<<setw(15)<<"是----->1\n"<<setw(15)<<"否----->2\n";
	int tmp0;
	cin>>tmp0;
	if(tmp0 == 1) {
		for(int i = tmp; i<n-1; i++)
			sch[i] = sch[i+1];
		n--;
		cout<<"删除成功,按任意键继续！\n";
	} else if(tmp0 == 2) {
		sch[tmp].edit();
		sort_sch_in(sch,n);
	} else {
		return;
	}
//	file.seekp(0,ios::beg);
//	file.close();
	if(file.fail())
		cout<<"fail to close\n";
	clear_file(filename);
	for(int i = 0; i<n; i++)
		sch[i].save(filename);
	//收尾
	delete[] sch;
	file.close();
}
void move(int x,int y, int forecolour=grey ,int backcolour = grey) {     //forecolour 是设置字体颜色，backcolour是设置背景颜色
	HANDLE handle;    //获取句柄
	COORD coord;   //获取坐标轴结构体
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获取小黑框的句柄
	SetConsoleCursorPosition(handle, coord);   //移动光标到x，y处
	SetConsoleTextAttribute(handle, forecolour + backcolour * 0x10);//改变当前光标的背景和字体颜色
}
void entranceshow() {
	int i;
	for(i=1; i<10; i++) {
		move(i-1,i-1,black,black);//清除掉上一个色块
		cout<<"  ";
		move(i,i,i,grey);
		cout<<"  ";        //空格等价于输出小方块
		Sleep(50);     //中间暂停100毫秒
	}
	move(i,i,black,white);
	return;
}
void viewsch(string filename) {
	fstream file;
	file.open(filename);
	int n = CountLines(filename);
	schedule *sch = new schedule[n];
	schedule *nsch = new schedule[n];
	for(int i = 0; i<n; i++)file>>sch[i];
	cout<<"请输入查看模式：\n注：1表示查看你的全部日程 \n    2表示输入日期限定范围查看日程\n    3表示搜索\n    4输入一个日期，显示该日期所在周的所有日程\n    -1表示退出此模式"<<endl;
	int x,i;
	cin>>x;
	while(x!=-1) {
		switch(x) {
			case 1: {
				for(i = 0; i<n; i++) {
					sch[i].show();
					nsch[i]=sch[i];
				}
				break;
			}
			case 2: {
				cout<<"请输入你要查看的日期范围："<<endl;
				cout<<"格式如下，年份+空格+月份+空格+日期"<<endl;
				cout<<"如果月份为-1，则显示此一整年的日程，如果日期为-1，则显示此一整月的日程"<<endl;
				int year,month,day;
				cin>>year>>month>>day;
				zhanshi(sch,nsch,year,month,day,n);
				break;
			}
			case 3: {
				cout<<"请选择搜索模式：1表示按照日程标题搜索，2表示按照地点搜索）";
				int i;
				string a;
				while(1) {
					cin>>i;
					if(i==1||i==2) {
						cout<<"请输入搜索信息：";
						cin>>a;
						sortsch(sch,nsch,a,i,n);
						break;
					}
					cout<<"输入数据有误请重新输入！！！"<<endl;
				}
				break;
			}
			case 4: {
				cout<<"注意！！！——此功能仅限于21世纪的日程查询！！！——"<<endl;
				cout<<"请输入你要查看的日期："<<endl;
				cout<<"格式如下，年份+空格+月份+空格+日期"<<endl;
				int year,month,day;
				int count=0;
				cin>>year>>month>>day;
				week a(year,month,day);
				week b;
				int judge=0;
				for(int i=0; i<n; i++) {
					if(sch[i].time.year>=2000&&sch[i].time.year<=2100) {
						b.input(sch[i].time.year,sch[i].time.month,sch[i].time.day);
						judge=1;
					}
					if(judge)if(a.getweek_count()==b.getweek_count()) {
							sch[i].show();
							nsch[count]=sch[i];
							count++;
						}
					judge = 0;
				}
				if(count==0) {
					cout<<"您没有本周的日程！！！"<<endl;
				}
				break;
			}
		}
		cout<<"请输入查看模式：\n注：1表示查看你的全部日程 \n    2表示输入日期限定范围查看日程\n    3表示搜索\n    4输入一个日期，显示该日期所在周的所有日程\n    -1表示退出此模式"<<endl;
		cin>>x;
	}

}
void zhanshi(schedule *sch,schedule *nsch,int year,int month,int day,int n) {
	int count=0;
	if(month!=-1&&day!=-1) {
		for(int i=0; i<n; i++) {
			if(sch[i].time.year==year&&sch[i].time.month==month&&sch[i].time.day==day) {
				sch[i].show();
				nsch[count]=sch[i];
				count++;
			}
		}
	} else if(month==-1) {
		for(int i=0; i<n; i++) {
			if(sch[i].time.year==year) {
				sch[i].show();
				nsch[count]=sch[i];
				count++;
			}
		}
	} else if(month!=-1&&day==-1) {
		for(int i = 0; i<n; i++) {
			if(sch[i].time.year==year&&sch[i].time.month==month) {
				sch[i].show();
				nsch[count]=sch[i];
				count++;
			}
		}
	}
	if(!count) {
		cout<<"您在这段时间内没有日程！"<<endl;
	}
}
//void zhanshi(schedule *sch,schedule *nsch,int year,int month,int day,int n) {
//	int count=0;
//	if(month!=-1&&day!=-1) {
//		for(int i=0; i<n; i++) {
//			if(sch[i].time.year==year&&sch[i].time.month==month&&sch[i].time.day==day) {
//				sch[i].show();
//				nsch[count]=sch[i];
//				count++;
//			}
//		}
//	} else if(month==-1) {
//		for(int i=0; i<n; i++) {
//			if(sch[i].time.year==year) {
//				sch[i].show();
//				nsch[count]=sch[i];
//				count++;
//			}
//		}
//	} else if(month!=-1&&day==-1) {
//		for(int i = 0; i<n; i++) {
//			if(sch[i].time.year==year&&sch[i].time.month==month) {
//				sch[i].show();
//				nsch[count]=sch[i];
//				count++;
//			}
//		}
//	}
//	if(!count) {
//		cout<<"您在这段时间内没有日程！"<<endl;
//	}
//}
void sortsch(schedule *sch,schedule *nsch,string n,int i,int nn) {
	int j;
	int count=0;
	switch(i) {
		case 1: {
			for(j=0; j<nn; j++) {
				if(sch[j].getplace()==n) {
					sch[j].show();
					nsch[count]=sch[j];
					count++;
				}
			}
			break;
		}
		case 2: {
			for(j=0; j<nn; j++) {
				if(sch[j].gettitle()==n) {
					sch[j].show();
					nsch[count]=sch[j];
					count++;
				}
			}
			break;
		}
	}
	if(count==0)cout<<"搜索无结果！！！"<<endl;
}
void clear_file(string filename) {
	fstream fout;
	fout.open(filename,ios::out);
	if(fout.fail())
		cout<<"fail to open\n";
	fout.close();
}
int CountLines(string filename) {
	ifstream ReadFile;
	int n=0;
	string tmp;
	ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件
	if(ReadFile.fail()) { //文件打开失败:返回0
		return 0;
	} else { //文件存在
		while(getline(ReadFile,tmp,'\n')) {
			n++;
		}
		ReadFile.close();
		return n;
	}
}
