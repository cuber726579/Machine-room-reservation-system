#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>
#include"Identity.h"
#include"pc_classroom.h"
#include"globalFile.h"
#include"appointFile.h"
using namespace std;

//打印机房信息
void printPcInfo(const PcClassroom& p);

//学生类
class Student :public Identity
{
public:
	int M_StuId;

	//机房列表
	vector<PcClassroom> vecPc;

	//默认构造
	Student();

	//有参构造 参数 : 学号 用户名 密码
	Student(int id, string usrName, string pwd);

	//操作菜单
	virtual void operMenu();

	//预约机房
	void  applyAppointment();

	//判断机房是否被预约
	bool checkReserved(int roomid);

	//查看自己的预约
	void viewAppointment_Own();

	//查看所有预约
	void viewAppointment_All();

	//取消预约
	void cancelAppointment();
};