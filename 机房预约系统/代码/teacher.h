#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Identity.h"
#include"appointFile.h"
using namespace std;

//教师类
class Teacher :public Identity
{
public:
	int M_TeacherId;

	//默认构造
	Teacher();

	//有参构造
	Teacher(int id,string usrName,string pwd);

	//操作菜单
	virtual void operMenu();

	//查看所有预约
	void viewAppointment_All();

	//审核预约
	void checkAppointment();
};
