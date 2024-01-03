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

using namespace std;
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

void entrance() {
	entranceshow();
	cout<<endl;
	cout<<setw(50)<<"仅查看日历->1"<<'\n'<<setw(50)<<"注册或登录帐户->2"<<'\n';
	int tmp;
	cin>>tmp;
	if(tmp == 1) {
		system("cls");
		//朱佳雯
	} else if(tmp == 2) {
		system("cls");
		login();
	}
}
void login() {
	string tmp;
	cout<<"请输入你在本计算机上的id:\n";
	cin>>tmp;
	tmp = tmp;
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
	cout<<"---------------------------------------------------查看日历->1---------------------------------------------------\n"
	    <<"---------------------------------------------------创建日程->2---------------------------------------------------\n"
	    <<"---------------------------------------------------编辑日程->3---------------------------------------------------\n"
	    <<"---------------------------------------------------查看日程->4---------------------------------------------------\n"
	    <<"-------------------------------------------请输入操作代号（-1退出程序）------------------------------------------\n";
	int tmp1;
	cin>>tmp1;
	schedule tmp2;
	if(tmp1 == -1) {
		system("cls");
		//退出
//		file.close();
		return;
	} else if(tmp1 == 1) {
		//查看日历
		system("cls");
		//朱佳雯
//		file.close();
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
	}
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
	file2<<tmp2;
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
	file.close();
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
void sortsch(schedule *sch,schedule *nsch,string n,int i,int nn) {
	int j;
	int count=0;
	switch(i) {
		case 1: {
			for(j=0; j<nn; j++) {
				if(sch[j].getplace()==n) {
					sch[j].show();
					nsch[count]=sch[i];
					count++;
				}
			}
			break;
		}
		case 2: {
			for(j=0; j<nn; j++) {
				if(sch[j].gettitle()==n) {
					sch[j].show();
					nsch[count]=sch[i];
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
