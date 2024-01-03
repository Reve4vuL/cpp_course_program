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

void entrance() {
	entranceshow();
	cout<<endl;
	cout<<setw(50)<<"���鿴����->1"<<'\n'<<setw(50)<<"ע����¼�ʻ�->2"<<'\n';
	int tmp;
	cin>>tmp;
	if(tmp == 1) {
		system("cls");
		//�����
	} else if(tmp == 2) {
		system("cls");
		login();
	}
}
void login() {
	string tmp;
	cout<<"���������ڱ�������ϵ�id:\n";
	cin>>tmp;
	tmp = tmp;
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
	cout<<"---------------------------------------------------�鿴����->1---------------------------------------------------\n"
	    <<"---------------------------------------------------�����ճ�->2---------------------------------------------------\n"
	    <<"---------------------------------------------------�༭�ճ�->3---------------------------------------------------\n"
	    <<"---------------------------------------------------�鿴�ճ�->4---------------------------------------------------\n"
	    <<"-------------------------------------------������������ţ�-1�˳�����------------------------------------------\n";
	int tmp1;
	cin>>tmp1;
	schedule tmp2;
	if(tmp1 == -1) {
		system("cls");
		//�˳�
//		file.close();
		return;
	} else if(tmp1 == 1) {
		//�鿴����
		system("cls");
		//�����
//		file.close();
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
	}
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
	file2<<tmp2;
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
	file.close();
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
	if(count==0)cout<<"�����޽��������"<<endl;
}
void clear_file(string filename) {
	fstream fout;
	fout.open(filename,ios::out);
	if(fout.fail())
		cout<<"fail to open\n";
	fout.close();
}
