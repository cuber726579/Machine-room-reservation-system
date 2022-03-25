#include"administrator.h"

//打印学生信息
void printStu(const Student& s)
{
	cout << "\t学号 : " << s.M_StuId << "\t用户名 : " << s.M_UsrName << endl;
}

//打印老师信息
void printTeacher(const Teacher& t)
{
	cout << "\t职工号 : " << t.M_TeacherId << "\t用户名 : " << t.M_UsrName << endl;
}

//默认构造
Administrator::Administrator()
{

}

//有参构造
Administrator::Administrator(string usrName, string pwd)
{
	this->M_UsrName = usrName;
	this->M_Password = pwd;
	this->initVector();
}

//操作菜单
void Administrator::operMenu()
{
	cout << "\t    管理员 : " << this->M_UsrName << endl;
	cout << "\t当前学生数量为 : " << vecStu.size() << endl;
	cout << "\t当前老师数量为 : " << vecTeacher.size() << endl;
	cout << "\t当前机房数量为 : " << vecPc.size() << endl;
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.添加账号     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.查看账号     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     3.添加机房     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     4.查看机房     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     5.清空预约     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     0.退出登录     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t----------------------" << endl;
}

//添加账号
void Administrator::addAccount()
{
	int option;		//接收用户选项
	cout << "1 -- 学生\t2 -- 老师" << endl;
	cout << "请输入添加账号类型 : ";
	cin >> option;

	string idTip;	//提示学号或职工号
	string errorTip;//重复时提示学号或职工号

	string fileName;
	ofstream ofs;

	if (1 == option)
	{
		fileName = STU_FILE;
		idTip =  "请输入学号 : ";
		errorTip = "学号重复,请重新输入 : ";
	}
	else if (2 == option)
	{
		fileName = TEACHER_FILE;
		idTip = "请输入职工号 :";
		errorTip = "职工号重复,请重新输入 : ";
	}
	else
	{
		cout << "\tError ---- 您的选择无效,添加失败!" << endl;
		return;
	}

	ofs.open(fileName, ios::out | ios::app);

//获取新账号信息
	int id;
	string usrName;
	string usrPwd;

	cout << idTip;
	while (true)
	{
		cin >> id;
		bool ret = checkRepetition(id, option);
		if (ret)	//重复
			cout << errorTip;
		else	break;
	}

	cout << "请输入用户名 : ";
	cin >> usrName;

	cout << "请输入密码 : ";
	cin >> usrPwd;

//向文件中添加账号信息
	ofs << id << " " << usrName << " " << usrPwd << endl;
	ofs.close();

//向列表中添加数据(重新从文件中获取数据)
	this->initVector();
	
	cout << "\t添加成功" << endl;
}

//查看所有账号
void Administrator::viewAccount_All()
{
	int option;		//接收用户选项
	cout << "1 -- 学生\t2 -- 老师" << endl;
	cout << "请输入查看账号类型 : ";
	cin >> option;

	if (1 == option)
	{
		if (!vecStu.size())
		{
			cout << "\t当前无学生账号" << endl; 
			return;
		}
		cout << "\t学生信息 :" << endl;
		for_each(vecStu.begin(), vecStu.end(), printStu);
	}
	else if (2 == option)
	{
		if (!vecTeacher.size())
		{
			cout << "\t当前无老师账号" << endl;
			return;
		}
		cout << "\t老师信息 :" << endl;
		for_each(vecTeacher.begin(), vecTeacher.end(), printTeacher);
	}
	else
	{
		cout << "\tError ---- 您的选择无效,查看失败!" << endl;
		return;
	}
}

//添加机房
void Administrator::addPcClassroom()
{
	int id;
	int capacity;

	cout << "请输入机房编号 : ";
	while (true)
	{
		cin >> id;
		bool ret = checkRepetition(id, 3);
		if (ret)
			cout << "机房编号重复,请重新输入 : ";
		else	break;
	}

	cout << "请输入机房容量 : ";
	cin >> capacity;

	ofstream ofs(PC_FILE, ios::out | ios::app);
	ofs << id << " " << capacity << 0 << endl;	//0 --- 机房初始时都为 未占用
	ofs.close();

	this->initVector();
	cout << "\t添加成功" << endl;
}

//查看机房信息
void Administrator::viewPcInfo()
{
	if (!vecPc.size())
	{
		cout << "\t当前无机房" << endl;
		return;
	}
	else
	{
		cout << "\t机房信息 :" << endl;
		for_each(vecPc.begin(), vecPc.end(), printPcInfo);
	}
}

//清空预约记录
void Administrator::clearAppointment()
{
	ofstream ofs(APPOINT_FILE, ios::trunc);
	ofs.close();

	cout << "\t预约清空成功!" << endl;
}

//初始化老师 学生 机房列表
void Administrator::initVector()
{
//读取学生信息
	vecStu.clear();
	ifstream ifs(STU_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "\tError ---- 文件不存在!" << endl;
		ifs.close();
		return;
	}

	Student stu;
	while (ifs >> stu.M_StuId && ifs >> stu.M_UsrName && ifs >> stu.M_Password)
		vecStu.push_back(stu);
	ifs.close();

//读取老师信息
	vecTeacher.clear();
	ifs.open(TEACHER_FILE, ios::in);
	if(!ifs.is_open())
	{
		cout << "\tError ---- 文件不存在!" << endl;
		ifs.close();
		return;
	}

	Teacher teacher;
	while (ifs >> teacher.M_TeacherId && ifs >> teacher.M_UsrName && ifs >> teacher.M_Password)
		vecTeacher.push_back(teacher);
	ifs.close();
//读取机房信息
	vecPc.clear();
	ifs.open(PC_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "\tError ---- 文件不存在!" << endl;
		ifs.close();
		return;
	}

	PcClassroom classroom;
	while (ifs >> classroom.M_PcId && ifs >> classroom.M_Capacity)
		vecPc.push_back(classroom);
	ifs.close();

}

//检测学号、职工号、机房号是否重复
bool Administrator::checkRepetition(int id, int idType)
{
	if (1 == idType)
	{//检测学号
		for (int i = 0; i < vecStu.size(); i++)
		{
			if (id == vecStu[i].M_StuId)
				return true;
		}
	}
	else if(2 == idType)
	{//检测职工号
		for (int i = 0; i < vecTeacher.size(); i++)
		{
			if (id == vecTeacher[i].M_TeacherId)
				return true;
		}
	}
	else if (3 == idType)
	{
		for (int i = 0; i < vecPc.size(); i++)
		{
			if (id == vecPc[i].M_PcId)
				return true;
		}
	}
	return false;
}
