#include<iostream>
#include<fstream>
#include"schedule.h"
using namespace std;
string path = "C:\\Users\\B G M\\Desktop\\C++test\\id\\徐梓浩.txt";
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
	ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件
	if(ReadFile.fail()) { //文件打开失败:返回0
		cout<<"fail to open\n";
		return 0;
	} else { //文件存在
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
		cout<<"第"<<setw(4)<<i<<"个日程：";
		sch[i].show();
	}
	file.close();
}
