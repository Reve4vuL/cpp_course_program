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
const string path = "F:\\�ĵ�\\�������\\ʵѵ\\2\\C++test\\id\\";

void clear_file(string filename);
void move(int x,int y, int forecolour,int backcolour);
void entranceshow();
int CountLines(string filename);//filename�Ǵ�path��
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
	cout<<"-------------------------------------------------��ӭʹ���ճ̹���ϵͳ��-------------------------------------------------\n";
	entrance();
	cout<<"-------------------------------------------------��ӭ�ٴ�ʹ��,�����˳�--------------------------------------------------\n";
	return 0;
}
void shuzhoushow(string filename) {
	fstream file;
	file.open(filename);
	int n = CountLines(filename);
	schedule *sch = new schedule[n];
	for(int i = 0; i<n; i++)file>>sch[i];
	cout<<"���������ģʽ"<<endl;
	cout<<"1.��ʾ�Ե�ǰʱ��Ϊ����ǰ��ֱ���ʾ�����ճ̣�"<<endl;
	cout<<"2.��ʾ�����Ժ���ճ�"<<endl;
	cout<<"3.��ʾ����֮ǰ���ճ�"<<endl;
	cout<<"����������˳�"<<endl;
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
	cout<<"��������Ҫ���ģʽ:" <<endl;
	int choose;
	cin>>choose;
	while(1) {
		if(choose == 1) {
			if(i>=3) {
				w2.input(sch[p[i-3].pai].time.year,sch[p[i-3].pai].time.month,sch[p[i-3].pai].time.day);
				cout<<"(-)1:"<<"��ȥ�Ѿ�"<< setw(4)<<getdays_count(w2,w1)<<"��:";
				sch[p[i-3].pai].show();
			} else {
				cout<<"(-)1:"<<"��"<<endl;
			}
			if(i>=2) {
				w2.input(sch[p[i-2].pai].time.year,sch[p[i-2].pai].time.month,sch[p[i-2].pai].time.day);
				cout<<"(-)2:"<<"��ȥ�Ѿ�"<< setw(4)<<getdays_count(w2,w1)<<"��:";
				sch[p[i-2].pai].show();
			} else {
				cout<<"(-)2:"<<"��"<<endl;
			}
			if(i>=1) {
				w2.input(sch[p[i-1].pai].time.year,sch[p[i-1].pai].time.month,sch[p[i-1].pai].time.day);
				cout<<"(-)3:"<<"��ȥ�Ѿ�"<< setw(4)<<getdays_count(w2,w1)<<"��:";
				sch[p[i-1].pai].show();
			} else {
				cout<<"(-)3:"<<"��"<<endl;
			}

			cout<<"--------����ʱ��Ϊ"<<year<<"."<<month<<"."<<day<<"--------"<<endl;
			if(sum-i>=1) {
				w2.input(sch[p[i].pai].time.year,sch[p[i].pai].time.month,sch[p[i].pai].time.day);
				cout<<"(+)1:"<<"�����"<< setw(4)<<getdays_count(w1,w2)<<"��:";
				sch[p[i].pai].show();
			} else {
				cout<<"(+)1:"<<"��"<<endl;
			}
			if(sum-i>=2) {
				w2.input(sch[p[i+1].pai].time.year,sch[p[i+1].pai].time.month,sch[p[i+1].pai].time.day);
				cout<<"(+)2:"<<"�����"<< setw(4)<<getdays_count(w1,w2)<<"��:";
				sch[p[i+1].pai].show();
			} else {
				cout<<"(+)2:"<<"��"<<endl;
			}
			if(sum-i>=3) {
				w2.input(sch[p[i+2].pai].time.year,sch[p[i+2].pai].time.month,sch[p[i+2].pai].time.day);
				cout<<"(+)3:"<<"�����"<< setw(4)<<getdays_count(w1,w2)<<"��:";
				sch[p[i+2].pai].show();
			} else {
				cout<<"(+)3:"<<"��"<<endl;
			}
		} else if(choose == 2) {
			int num;
			cout<<"������Ҫ�鿴�Ľ���֮����ճ̸�����"<<endl;
			cin >> num;
			for(j = 0; j<num; j++) {
				if(sum - i>=j+1) {
					w2.input(sch[p[i+j].pai].time.year,sch[p[i+j].pai].time.month,sch[p[i+j].pai].time.day);
					cout<<"(+)"<<j+1<<":"<<"�����"<< setw(4)<<getdays_count(w1,w2)<<"��:";
					sch[p[i+j].pai].show();
				} else {
					cout<<"(+)"<<j+1<<":"<<"��"<<endl;
				}
			}
		} else if(choose == 3) {
			int num;
			cout<<"������Ҫ�鿴�Ľ���֮ǰ���ճ̸�����"<<endl;
			cin>>num;
			for(j=0; j<num; j++) {
				if(i>=j+1) {
					w2.input(sch[p[i-j-1].pai].time.year,sch[p[i-j-1].pai].time.month,sch[p[i-j-1].pai].time.day);
					cout<<"(-)"<<j+1<<":"<<"��ȥ�Ѿ�"<< setw(4)<<getdays_count(w2,w1)<<"��:";
					sch[p[i-j-1].pai].show();
				} else {
					cout<<"(-)"<<j+1<<":"<<"��"<<endl;
				}
			}
		} else {
			break;
		}
		cout<<"��������Ҫ���ģʽ:" <<endl;
		cin>>choose;
	}
	cout<<"��������˳���"<<endl;
	getchar();
	getchar();
}
//void entrance() {
//	entranceshow();
//	cout<<endl;
//	cout<<setw(50)<<"���鿴����->1"<<'\n'<<setw(50)<<"ע����¼�ʻ�->2"<<'\n';
//	int tmp;
//	cin>>tmp;
//	if(tmp == 1) {
//		system("cls");
//		//�����
//	} else if(tmp == 2) {
//		system("cls");
//		login();
//	}
//}
void entrance() {
	entranceshow();
	cout<<endl;
	cout<<setw(50)<<"���鿴����->1"<<'\n'<<setw(50)<<"ע����¼�ʻ�->2"<<'\n'<<setw(50)<<"�˳�->-1"<<endl;
	int tmp;
	cin>>tmp;
	while(1) {
		if(tmp==1||tmp==2) {
			if(tmp == 1) {
				system("cls");
				cout<<"������ģʽ��1����鿴ĳ��������2����鿴ĳ��ĳ������"<<endl;
				int x;
				cin>>x;
				while(1){
					if(x!=1&&x!=2){
					cout<<"�����������������룡����"<<endl;
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
			cout<<"����һ���(*�R��)(�ŨQ*)"<<endl;
			cout<<"����ô��������-1��((��-��)(��-��))"<<endl;
		} else if(tmp!=-1) {
			cout<<"������(?`~��?)"<<endl;
			cout<<"�ͼ�������һ��(*'��`*)" <<endl;
		} else if(tmp==-1) {
			break;
		}
		cin>>tmp;
	}
}
void login() {
	system("cls");
	string tmp;
	cout<<"���������ڱ�������ϵ�id:\n";
	cin>>tmp;
	if(search(tmp+".txt")) {
		cout<<"���������룺\n";
		string tmp1,tmp2;
		cin>>tmp1;
		fstream file;
		file.open(path+tmp+"code.txt");
		if(file.fail())
			cout<<"fail to code.........\n";
		file>>tmp2;
		if(tmp1 == tmp2)
			cout<<"��½�ɹ�!\n";
		else {
			cout<<"�������������µ�¼��\n";
			getchar();
			getchar();
			login();
		}
		file.close();
		operation(path+tmp+".txt");
	} else {
		cout<<"�ڱ��ؼ������δ�ҵ�����ʻ���\n�Ƿ񴴽���\n����->1\n�˳�->2\n";
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
	cout<<"��ӭ�㣡\n";
	cout<<"-------------------------------------------------�鿴����->1-------------------------------------------------\n"
	    <<"-------------------------------------------------�����ճ�->2-------------------------------------------------\n"
	    <<"-------------------------------------------------�༭�ճ�->3-------------------------------------------------\n"
	    <<"-------------------------------------------------�鿴�ճ�->4-------------------------------------------------\n"
	    <<"-------------------------------------------------��ʱ���->5-------------------------------------------------\n"
	    <<"-------------------------------------------------�޸�����->6-------------------------------------------------\n"
	    <<"------������������ţ�-1�˳�����-------\n";
	int tmp1;
	cin>>tmp1;
	schedule tmp2;
	if(tmp1 == -1) {
		system("cls");
		//�˳�
//		file.close();
		return;
	} else if(tmp1 == 1) {
		system("cls");
		cout<<"������ģʽ��1����鿴ĳ��������2����鿴ĳ��ĳ������"<<endl;
		int x;
		cin>>x;
		while(1){
			if(x!=1&&x!=2){
			cout<<"�����������������룡����"<<endl;
			cin>>x;
			}
			else break;
		}
		showc(x);
		system("cls");
		operation(filename);
		return;
	} else if(tmp1 == 2) {
		//�����ճ�
		createsch(filename);
		operation(filename);
		return;
	} else if(tmp1 == 3) {
		//�༭�ճ�
		editsch(filename);
		operation(filename);
		return;
	} else if(tmp1 == 4) {
		//�鿴�ճ�
		viewsch(filename);
		operation(filename);
		return;
	} else if(tmp1 == 5) {
		//��ʱ���
		shuzhoushow(filename);
		operation(filename);
	} else if(tmp1 == 6) {
		//�޸�����
		cout<<"������ɵ�����\n";
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
			cout<<"�������µ�����\n";
			cin>>tmp4;
			if(tmpfile.fail()) {
				cout<<"error2\n";
			}
			tmpfile.seekp(0,ios::beg);
			tmpfile<<tmp4<<'\n';
			tmpfile.close();
			if(tmpfile.fail())
				cout<<"error\n";
			cout<<"�����޸ĳɹ��������µ�¼!\n";
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
//	ReadFile.open(filename,ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
//	if(ReadFile.fail()) { //�ļ���ʧ��:����0
//		return 0;
//	} else { //�ļ�����
//		while(getline(ReadFile,tmp,'\n')) {
//			n++;
//		}
//		ReadFile.close();
//		return n;
//	}
//}
int search(std::string name) {
	//Ŀ���ļ���·��
	std::string inPath = path+"*";//�����ļ����µ�����.txt�ļ�
	//���ڲ��ҵľ��
	long handle;
	struct _finddata_t fileinfo;
	//��һ�β���
	handle = _findfirst(inPath.c_str(),&fileinfo);
	if(handle == -1)
		return 0;
	do {
		//�ҵ����ļ����ļ���
		if(name == fileinfo.name)
			return 1;
	} while (!_findnext(handle,&fileinfo));
	_findclose(handle);
	return 0;
}
int createid() {
	string tmp,code,tmp1,tmp2;
	ofstream file1,file2;
	cout<<"�������û�����\n";
	cin>>tmp;
	cout<<"���������룺\n";
	cin>>code;
	tmp1 = path+tmp+".txt";
	tmp2 = path+tmp+"code.txt";
	file1.open(tmp1,ios::out);
	file2.open(tmp2,ios::out);
	file2<<code;
	file2.close();
	if(file1.fail()||file2.fail()) {
		cout<<"ע��ʧ�ܣ������ԣ�\n";
		return 0;
	} else {
		cout<<"ע��ɹ��������µ�¼��";
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
	cout<<"�ճ̴�����...\n---------------���밴��ʾ���룩---------------\n";
	//ʵ��>>��<<���������
	schedule tmp;
	tmp.input();
	tmp.save(filename);
	//�ճ�����
	sort_sch_out(filename);
	cout<<"�ճ̴����ɹ�,�밴���������\n";
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
		cout<<"��"<<setw(4)<<i<<"���ճ̣�";
		sch[i].show();
	}
	delete[] sch;
	file.close();
}
//void editsch(string filename) {
////�༭�ճ�
//	//��ʼ��
//	fstream file;
//	file.open(filename);
//	int n = CountLines(filename);
//	schedule *sch = new schedule[n];
//	int tmp;
//	for(int i = 0; i<n; i++)
//		file>>sch[i];
//	//��ʽ�༭
//
//	cout<<"��һ����"<<n<<"���ճ̣���Ҫ�༭�ĸ��ճ̣�ѡ����Ҫ�༭�ı�ţ�\n";
//	showallsch(filename);
//	cin>>tmp;
//	cout<<"��Ҫɾ������\n"<<setw(15)<<"��----->1\n"<<setw(15)<<"��----->2\n";
//	int tmp0;
//	cin>>tmp0;
//	if(tmp0 == 1) {
//		for(int i = tmp; i<n-1; i++)
//			sch[i] = sch[i+1];
//		n--;
//		cout<<"ɾ���ɹ�,�������������\n";
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
//	//��β
//	delete[] sch;
//	file.close();
//}
void editsch(string filename) {
//�༭�ճ�
	//��ʼ��
	fstream file;
	file.open(filename);
	int n = CountLines(filename);
	schedule *sch = new schedule[n];
	int tmp;
	for(int i = 0; i<n; i++)
		file>>sch[i];
	//��ʽ�༭

	cout<<"��һ����"<<n<<"���ճ̣���Ҫ�༭�ĸ��ճ̣�ѡ����Ҫ�༭�ı�ţ�\n";
	showallsch(filename);
	cin>>tmp;
	cout<<"��Ҫɾ������\n"<<setw(15)<<"��----->1\n"<<setw(15)<<"��----->2\n";
	int tmp0;
	cin>>tmp0;
	if(tmp0 == 1) {
		for(int i = tmp; i<n-1; i++)
			sch[i] = sch[i+1];
		n--;
		cout<<"ɾ���ɹ�,�������������\n";
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
	//��β
	delete[] sch;
	file.close();
}
void move(int x,int y, int forecolour=grey ,int backcolour = grey) {     //forecolour ������������ɫ��backcolour�����ñ�����ɫ
	HANDLE handle;    //��ȡ���
	COORD coord;   //��ȡ������ṹ��
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //��ȡС�ڿ�ľ��
	SetConsoleCursorPosition(handle, coord);   //�ƶ���굽x��y��
	SetConsoleTextAttribute(handle, forecolour + backcolour * 0x10);//�ı䵱ǰ���ı�����������ɫ
}
void entranceshow() {
	int i;
	for(i=1; i<10; i++) {
		move(i-1,i-1,black,black);//�������һ��ɫ��
		cout<<"  ";
		move(i,i,i,grey);
		cout<<"  ";        //�ո�ȼ������С����
		Sleep(50);     //�м���ͣ100����
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
	cout<<"������鿴ģʽ��\nע��1��ʾ�鿴���ȫ���ճ� \n    2��ʾ���������޶���Χ�鿴�ճ�\n    3��ʾ����\n    4����һ�����ڣ���ʾ�����������ܵ������ճ�\n    -1��ʾ�˳���ģʽ"<<endl;
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
				cout<<"��������Ҫ�鿴�����ڷ�Χ��"<<endl;
				cout<<"��ʽ���£����+�ո�+�·�+�ո�+����"<<endl;
				cout<<"����·�Ϊ-1������ʾ��һ������ճ̣��������Ϊ-1������ʾ��һ���µ��ճ�"<<endl;
				int year,month,day;
				cin>>year>>month>>day;
				zhanshi(sch,nsch,year,month,day,n);
				break;
			}
			case 3: {
				cout<<"��ѡ������ģʽ��1��ʾ�����ճ̱���������2��ʾ���յص�������";
				int i;
				string a;
				while(1) {
					cin>>i;
					if(i==1||i==2) {
						cout<<"������������Ϣ��";
						cin>>a;
						sortsch(sch,nsch,a,i,n);
						break;
					}
					cout<<"���������������������룡����"<<endl;
				}
				break;
			}
			case 4: {
				cout<<"ע�⣡���������˹��ܽ�����21���͵��ճ̲�ѯ����������"<<endl;
				cout<<"��������Ҫ�鿴�����ڣ�"<<endl;
				cout<<"��ʽ���£����+�ո�+�·�+�ո�+����"<<endl;
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
					cout<<"��û�б��ܵ��ճ̣�����"<<endl;
				}
				break;
			}
		}
		cout<<"������鿴ģʽ��\nע��1��ʾ�鿴���ȫ���ճ� \n    2��ʾ���������޶���Χ�鿴�ճ�\n    3��ʾ����\n    4����һ�����ڣ���ʾ�����������ܵ������ճ�\n    -1��ʾ�˳���ģʽ"<<endl;
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
		cout<<"�������ʱ����û���ճ̣�"<<endl;
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
//		cout<<"�������ʱ����û���ճ̣�"<<endl;
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
	if(count==0)cout<<"�����޽��������"<<endl;
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
	ReadFile.open(filename,ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
	if(ReadFile.fail()) { //�ļ���ʧ��:����0
		return 0;
	} else { //�ļ�����
		while(getline(ReadFile,tmp,'\n')) {
			n++;
		}
		ReadFile.close();
		return n;
	}
}
