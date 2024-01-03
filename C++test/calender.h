#include <iostream>
#include <iomanip>
using namespace std;

int leapyear(int y) { //�ж��Ƿ�������
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		return 1;
	else
		return 0;
}

int yfirstday(int y) { //����ĳ���һ�������ڼ�
	int d = (y - 1) * 365 + (y - 1) / 4 - (y - 100) / 100 + (y - 1) / 400;
	return d % 7;
}

//int mfirstday(int y, int m) { //����ĳ��ĳ�µ�һ�������ڼ�
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

int showyear(int y) {//��ʾ����
	while(y>10000){
		cout<<"������ݹ��󣡣���"<<endl;
		cout<<"�����������������"<<endl;
		getchar();
		getchar();
		system("cls");
		cout<<"������������ݣ�����"<<endl;
		cin>>y;
		showyear(y);
	}
	int m, d, i;
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (leapyear(y))
		month[1] = 29;
	int firstday = yfirstday(y); //ĳ���һ�������ڼ�
	cout << "������" << y << "��" << endl;
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

int showmonth(int y, int mm) {//��ʾ����

	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int firstday = yfirstday(y); //ĳ���һ�������ڼ�
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

int showc(int k) { //��ʾ����ʱ����Ҫ���������ꣻ��ʾ����ʱ����Ҫ��������������
	int y, m;
	switch (k) {
		case 1:
			cout << "����������鿴����ݣ�";
			cin >> y;
			showyear(y);
			break;
		case 2:
			cout << "����������鿴����ݣ�";
			cin >> y;
			while(y>10000){
					cout<<"������ݹ��󣡣���"<<endl;
					system("cls");
					cout<<"������������ݣ�����"<<endl;
					cin>>y;
				}
			cout << "����������鿴���·ݣ�"; 
			cin >> m;
			while(m<1||m>12){
				cout<<"�����������󣡣���"<<endl;
				system("cls");
				cout<<"�����������·ݣ�����"<<endl;
				cin>>m;
			}
			showmonth(y, m);
			break;
	}
	cout<<"���������������������"<<endl;
	getchar();
	getchar();
}

