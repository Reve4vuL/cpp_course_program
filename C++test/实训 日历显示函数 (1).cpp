#include <iostream>
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
				cout << "    " << d;
			} else
				cout << "    " << d;
			if ((firstday + d - 1) % 7 == 6)
				cout << endl;
		}
		firstday = (firstday + month[m]) % 7;
		cout << endl;
	}
}

//int showmonth(int y, int m) {//��ʾ����
//
//}

int show(int k) { //��ʾ����ʱ����Ҫ���������ꣻ��ʾ����ʱ����Ҫ��������������
	int y, m;
	cin >> k;
	switch (k) {
		case 1:
			cout << "����������鿴����ݣ�";
			cin >> y;
			showyear(y);
			break;
		case 2:
			cout << "����������鿴����ݣ�";
			cin >> y;
			cout << "����������鿴���·ݣ�";
			cin >> m;
			showmonth(y, m);
			break;
	}

}

int main() {
	int k;
	show(k);
	return 0;
}
