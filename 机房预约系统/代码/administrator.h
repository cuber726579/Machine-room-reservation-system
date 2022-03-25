#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include"Identity.h"
#include"student.h"
#include"teacher.h"
#include"pc_classroom.h"
#include"globalFile.h"
using namespace std;

//打印学生信息
void printStu(const Student&);

//打印老师信息
void printTeacher(const Teacher& t);

//管理员类
class Administrator :public Identity
{
public:
	//学生列表
	vector<Student> vecStu;

	//老师列表
	vector<Teacher> vecTeacher;

	//机房列表
	vector<PcClassroom> vecPc;

	//默认构造
	Administrator();

	//有参构造
	Administrator(string usrName, string pwd);

	//操作菜单
	virtual void operMenu();

	//添加账号
	void addAccount();

	//查看所有账号
	void viewAccount_All();

	//添加机房
	void addPcClassroom();

	//查看机房信息
	void viewPcInfo();

	//清空预约记录
	void clearAppointment();

	//初始化老师、学生、机房列表
	void initVector();

	//检测学号或职工号是否重复
	bool checkRepetition(int, int);
};