#include<iostream>
#include<fstream>
#include"schedule.h"
using namespace std;
string path = "C:\\Users\\B G M\\Desktop\\C++test\\id\\������.txt";
void showallsch(string filename);
int CountLines(string filename);
void clear_file(string filename) {
	fstream fout(path,ios::out|ios::trunc);
	fout.close();
}
int main() {
	clear_file(path);
	return 0;
}

int CountLines(string filename) {
	ifstream ReadFile;
	int n=0;
	string tmp;
	ReadFile.open(filename,ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
	if(ReadFile.fail()) { //�ļ���ʧ��:����0
		cout<<"fail to open\n";
		return 0;
	} else { //�ļ�����
		while(getline(ReadFile,tmp,'\n')) {
			n++;
		}
		ReadFile.close();
		return n;
	}
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
	file.close();
}
