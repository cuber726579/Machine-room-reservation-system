#include<iostream>
#include<string>
#include<fstream>
#include"Identity.h"
#include"student.h"
#include"teacher.h"
#include"administrator.h"
#include"globalFile.h"
using namespace std;

void mainMenu(void);
void adminMenu(Identity*&);
void studentMenu(Identity*&);
void LoginIn(string, int);

//主菜单
void mainMenu(void)
{
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.学生代表     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.老    师     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     3.管 理 员     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     0.退    出     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t----------------------" << endl;
}

//进入管理员子菜单
void adminMenu(Identity*& administrator)
{
	cout << "\t欢迎管理员 " << administrator->M_UsrName << " 登录!" << endl;
	int option;		//接收用户选项

	while (true)
	{
		administrator->operMenu();

	//将父类指针强转为子类指针,以调用子类接口
		Administrator* admin = (Administrator*)administrator;

		cout << "请输入您的选择 : ";
		cin >> option;
		switch (option)
		{
			case 1:	//添加账号
				admin->addAccount();
				break;
			case 2:	//查看所有账号
				admin->viewAccount_All();
				break;			
			case 3:	//添加机房
				admin->addPcClassroom();
				break;
			case 4:	//查看机房信息
				admin->viewPcInfo();
				break;
			case 5:	//清空预约记录
				admin->clearAppointment();
				break;
			case 0:	//退出登录
				delete admin;
				cout << "\t已退出登录" << endl;
				return;
			default:
				cout << "\tError ---- 您的选择无效!" << endl;
				break;
		}
		system("pause");
		system("cls");
	}
}

//进入学生子菜单
void studentMenu(Identity*& student)
{
	cout << "\t欢迎学生 " << student->M_UsrName << " 登录!" << endl;
	int option;

	while (true)
	{
		student->operMenu();

		Student* stu = (Student*)student;

		cout << "请输入您的选择 : ";
		cin >> option;
		switch (option)
		{
		case 1:	//申请预约
			stu->applyAppointment();
			break;
		case 2:	//查看自身预约
			stu->viewAppointment_Own();
			break;
		case 3:	//查看所有预约
			stu->viewAppointment_All();
			break;
		case 4:	//取消预约
			stu->cancelAppointment();
			break;
		case 0:	//退出登录
			delete stu;
			cout << "\t已退出登录" << endl;
			return;
		default:
			cout << "\tError ---- 您的选择无效!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//进入老师子菜单
void teacherMenu(Identity*& teacher)
{
	cout << "\t欢迎老师 " << teacher->M_UsrName << " 登录!" << endl;
	int option;		//接收用户选项
	while(true)
	{
		teacher->operMenu();

		Teacher*tea = (Teacher*)teacher;

		cout << "请输入您的选择 : ";
		cin >> option;
		switch (option)
		{
		case 1:	//查看所有预约
			tea->viewAppointment_All();
			break;
		case 2:	//审核预约
			tea->checkAppointment();
			break;
		case 0:	//退出登录
			delete tea;
			cout << "\t已退出登录" << endl;
			return;
		default:
			cout << "\tError ---- 您的选择无效!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//登录功能
void LoginIn(string fileName, int idType)
{
	Identity* usr;

	//读入文件
	ifstream ifs(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "\tError ---- 文件不存在!" << endl;
		ifs.close();
		return;
	}

	//读入用户信息
	int id;
	string name;
	string pwd;

	if (1 == idType)
	{
		cout << "请输入学号 : ";
		cin >> id;
	}
	else if (2 == idType)
	{
		cout << "请输入职工号 : ";
		cin >> id;
	}
	
	cout << "请输入用户名 : ";
	cin >> name;

	cout << "请输入密码 : ";
	cin >> pwd;

	if (1 == idType)
	{//学生身份验证
		int fileId;
		string fileName;
		string filePwd;

		while (ifs >> fileId && ifs >> fileName && ifs >> filePwd)
		{
			if (fileId == id && fileName == name && filePwd == pwd)
			{
				cout << "\t学生验证登录成功!" << endl;
				usr = new Student(id, name, pwd);
				
				system("pause");
				system("cls");

				studentMenu(usr);

				return;
			}
		}
	}
	else if (2 == idType)
	{//教师身份验证
		int fileId;
		string fileName;
		string filePwd;

		while (ifs >> fileId && ifs >> fileName && ifs >> filePwd)
		{
			if (fileId == id && fileName == name && filePwd == pwd)
			{
				cout << "\t老师验证登录成功!" << endl;
				usr = new Teacher(id, name, pwd);

				system("pause");
				system("cls");

				teacherMenu(usr);

				return;
			}
		}
	}
	else
	{//管理员身份验证
		string fileName;
		string filePwd;

		while (ifs >> fileName && ifs >> filePwd)
		{
			if (fileName == name && filePwd == pwd)
			{
				cout << "\t管理员验证登录成功!" << endl;
				usr = new Administrator(name, pwd);

				system("pause");
				system("cls");

				adminMenu(usr);

				return;
			}
		}
	}

	cout << "\tError ---- 验证登录失败!" << endl;
	return;
}

int main(void)
{
	int option;		//接收用户选项

	while (true)
	{
		cout << "======== 欢迎进入机房预约系统 ========" << endl;
		mainMenu();

		cout << "请输入您的选择 : ";
		cin >> option;
		switch (option)
		{
		case 1:	//学生身份
			LoginIn(STU_FILE, 1);
			break;
		case 2:	//老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:	//管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:	//退出系统
			cout << "\t欢迎下次使用" << endl;
			system("pause");
			return 0;
		default:
			cout << "\tError ---- 您的选择无效!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}