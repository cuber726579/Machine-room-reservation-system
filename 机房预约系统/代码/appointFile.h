#pragma once
#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include"globalFile.h"
using namespace std;

//截取数据
pair<string, string> Pairing(string str);

class AppointFile
{
public:
	//记录预约条数
	int M_Size;

	//记录列表 int 为记录条数 map存放记录
	map<int, map<string, string>> mapAppoint;
	
	//默认构造
	AppointFile();

	//更新预约记录
	void updateAppoint();
};