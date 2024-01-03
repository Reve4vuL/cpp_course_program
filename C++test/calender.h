#include <iostream>
#include <iomanip>
using namespace std;

int leapyear(int y) { //判断是否是闰年
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		return 1;
	else
		return 0;
}

int yfirstday(int y) { //计算某年的一号是星期几
	int d = (y - 1) * 365 + (y - 1) / 4 - (y - 100) / 100 + (y - 1) / 400;
	return d % 7;
}

//int mfirstday(int y, int m) { //计算某年某月的一号是星期几
//	int d
//}

void printweektitle() {
	for (int i = 0; i < 7; i++) {
		switch (i) {
			case 0 :
				cout << "  Sun  ";
				break;
			case 1 :
				cout << "Mon  ";
				break;
			case 2 :
				cout << "Tue  ";
				break;
			case 3 :
				cout << "Wed  ";
				break;
			case 4 :
				cout << "Thu  ";
				break;
			case 5 :
				cout << "Fri  ";
				break;
			case 6 :
				cout << "Sat  ";
				break;
			default :
				break;
		}
	}
	cout << endl;
}

void printmontitle(int m) {
	switch (m) {
		case 0 :
			cout << "Jan" << endl;
			break;
		case 1 :
			cout << "Feb" << endl;
			break;
		case 2 :
			cout << "Mar" << endl;
			break;
		case 3 :
			cout << "Apr" << endl;
			break;
		case 4 :
			cout << "May" << endl;
			break;
		case 5 :
			cout << "Jun" << endl;
			break;
		case 6 :
			cout << "Jul" << endl;
			break;
		case 7 :
			cout << "Aug" << endl;
			break;
		case 8 :
			cout << "Sep" << endl;
			break;
		case 9 :
			cout << "Oct" << endl;
			break;
		case 10 :
			cout << "Nov" << endl;
			break;
		case 11 :
			cout << "Dec" << endl;
			break;
		default :
			break;
	}
}

int showyear(int y) {//显示年历
	while(y>10000){
		cout<<"输入年份过大！！！"<<endl;
		cout<<"按任意键继续！！！"<<endl;
		getchar();
		getchar();
		system("cls");
		cout<<"请重新输入年份！！！"<<endl;
		cin>>y;
		showyear(y);
	}
	int m, d, i;
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (leapyear(y))
		month[1] = 29;
	int firstday = yfirstday(y); //某年的一号是星期几
	cout << "今年是" << y << "年" << endl;
	cout << "===================" << endl;
	for (m = 0; m < 12; m++) {
		printmontitle(m);
		printweektitle();
		for (d = 1; d <= month[m]; d++) {
			if (d == 1) {
				for (i = 0; i < firstday; i++)
					cout << "     ";
				cout <<setw(5)<< d;
			} else
				cout <<setw(5)<< d;
			if ((firstday + d - 1) % 7 == 6)
				cout << endl;
		}
		firstday = (firstday + month[m]) % 7;
		cout << endl;
	}
}

int showmonth(int y, int mm) {//显示月历

	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int firstday = yfirstday(y); //某年的一号是星期几
	for (int m = 0; m < 12; m++) {
		if(m == mm-1)printmontitle(m);
		if(m == mm-1)printweektitle();
		for (int d = 1; d <= month[m]; d++) {
			if (d == 1) {
				for (int i = 0; i < firstday; i++)
					if(m == mm-1)cout << "     ";
				if(m == mm-1)cout << setw(5)<< d;
			} else
				if(m == mm-1)cout <<setw(5) << d;
			if ((firstday + d - 1) % 7 == 6)
				if(m == mm-1)cout << endl;
		}
		firstday = (firstday + month[m]) % 7;
		if(m == mm-1)cout << endl;
	}
}

int showc(int k) { //显示年历时，需要输入是哪年；显示月历时，需要输入是哪年哪月
	int y, m;
	switch (k) {
		case 1:
			cout << "请输入您想查看的年份：";
			cin >> y;
			showyear(y);
			break;
		case 2:
			cout << "请输入您想查看的年份：";
			cin >> y;
			while(y>10000){
					cout<<"输入年份过大！！！"<<endl;
					system("cls");
					cout<<"请重新输入年份！！！"<<endl;
					cin>>y;
				}
			cout << "请输入您想查看的月份："; 
			cin >> m;
			while(m<1||m>12){
				cout<<"输入数据有误！！！"<<endl;
				system("cls");
				cout<<"请重新输入月份！！！"<<endl;
				cin>>m;
			}
			showmonth(y, m);
			break;
	}
	cout<<"请输入任意键继续！！！"<<endl;
	getchar();
	getchar();
}

