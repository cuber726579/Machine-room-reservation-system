#pragma once
#include<iostream>
using namespace std;

//身份抽象基类
class Identity
{
public:
	string M_UsrName;
	string M_Password;

	//操作菜单 纯虚函数
	virtual void operMenu() = 0;
};