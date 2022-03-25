#include"student.h"

//打印机房信息
void printPcInfo(const PcClassroom& p)
{
	cout << "\t编号 : " << p.M_PcId << "\t容量 : " << p.M_Capacity << endl;
}

//默认构造
Student::Student()
{

}

//有参构造 参数 : 学号 用户名 密码
Student::Student(int id, string usrName, string pwd)
{
	M_StuId = id;
	M_UsrName = usrName;
	M_Password = pwd;

	vecPc.clear();
	ifstream ifs(PC_FILE, ios::in);
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

//操作菜单
void Student::operMenu()
{
	cout << "\t\t学生 : " << this->M_UsrName << endl;
	cout << "\t-----------------------" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     1.申请预约      |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     2.查看我的预约  |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     3.查看所有预约  |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     4.取消预约      |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     0.退出登录      |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t-----------------------" << endl;
}

//预约机房
void Student::applyAppointment()
{
	int date,interval,room;

	cout << "\n1. 周一  2. 周二  3. 周三  4.周四  5.周五 " << endl;
	cout << "请输入申请的日期 : ";
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)	break;
		else
			cout << "您的输入无效,请重新输入 : ";
	}

	cout << "\n1 . 上午\t2 . 下午" << endl;
	cout << "请输入申请的时间段 : ";
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)	break;
		else
			cout << "您的输入无效,请重新输入 : ";
	}

	cout << "\t机房信息 :" << endl;
	for_each(vecPc.begin(), vecPc.end(), printPcInfo);
	cout << "请输入申请的机房编号 : ";
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= vecPc.size())	break;
		else
			cout << "您的输入无效,请重新输入 : ";
	}

	ofstream ofs(APPOINT_FILE, ios::out | ios::app);
	ofs << "date:" << date << " "
		<< "interval:" << interval << " "
		<< "stuId:" << this->M_StuId << " "
		<< "stuName:" << this->M_UsrName << " "
		<< "roomId:" << room << " "
		<< "status:" << 1 << endl;	//1表示状态 审核中
	ofs.close();

	cout << "\t预约成功!" << endl;
}

//查看自己的预约
void Student::viewAppointment_Own()
{
	int flag = 0;	//标志是否找到预约记录
	AppointFile af;

	if (!af.M_Size)
	{
		cout << "\t无预约记录" << endl;
		return;
	}

	for (int i = 0; i < af.M_Size; i++)
	{
	//string容器中 c_str 成员函数将c++风格字符串转换为c风格的字符串
	//atoi函数将字符数组转换为数字
		if (this->M_StuId == atoi(af.mapAppoint[i]["stuId"].c_str()))
		{
			cout << "\t\t第 " << ++flag << " 条记录" << endl;
			cout << "预约日期: 周" << af.mapAppoint[i]["date"];
			cout << " " << (af.mapAppoint[i]["interval"] == "1" ? "上午" : "下午");
			cout << "\t机房号: " << af.mapAppoint[i]["roomId"];

			string status = "\t状态: ";
			if ("0" == af.mapAppoint[i]["status"])
				status += "已取消预约";
			else if ("1" == af.mapAppoint[i]["status"])
				status += "审核中";
			else if ("2" == af.mapAppoint[i]["status"])
				status += "预约成功";
			else
				status += "预约失败,审核未通过";
			cout << status << endl << endl;
		}
	}
	if (!flag)
		cout << "\t未找到预约记录" << endl;
}

//查看所有预约
void Student::viewAppointment_All()
{
	AppointFile af;
	if (!af.M_Size)
	{
		cout << "\t无预约记录" << endl;
		return;
	}

	for (int i = 0; i < af.M_Size; i++)
	{
		cout << "\t\t第 " << i + 1 << " 条记录" << endl;
		cout << "预约日期: 周" << af.mapAppoint[i]["date"];
		cout << " " << (af.mapAppoint[i]["interval"] == "1" ? "上午" : "下午");
		cout << "\t预约学生学号: " << af.mapAppoint[i]["stuId"];
		cout << "\t机房号: " << af.mapAppoint[i]["roomId"];

		string status = "\t状态: ";
		if ("0" == af.mapAppoint[i]["status"])
			status += "已取消预约";
		else if ("1" == af.mapAppoint[i]["status"])
			status += "审核中";
		else if ("2" == af.mapAppoint[i]["status"])
			status += "预约成功";
		else
			status += "预约失败,审核未通过";
		cout << status << endl << endl;
	}
}

//取消自身预约
void Student::cancelAppointment()
{
	AppointFile af;
	if (!af.M_Size)
	{
		cout << "\t无预约记录" << endl;
		return;
	}

	vector<int> v;	//标记学生的记录号(index)对应容器中的编号
	int index = 0;	//标记当前学生的记录数
	for (int i = 0; i < af.M_Size; i++)
	{
		if (this->M_StuId == atoi(af.mapAppoint[i]["stuId"].c_str()))
			if ("1" == af.mapAppoint[i]["status"] || "2" == af.mapAppoint[i]["status"])
			{//只能取消 审核中 和 审核成功 的预约记录
				if(0 == index)
					cout << "    当前可取消的预约 : " << endl;
				v.push_back(i);

				cout << "\t\t第 " << ++index << " 条记录" << endl;
				cout << "预约日期: 周" << af.mapAppoint[i]["date"];
				cout << " " << (af.mapAppoint[i]["interval"] == "1" ? "上午" : "下午");
				cout << "\t机房号: " << af.mapAppoint[i]["roomId"];

				string status = "\t状态: ";
				if ("1" == af.mapAppoint[i]["status"])
					status += "审核中";
				else if ("2" == af.mapAppoint[i]["status"])
					status += "预约成功";

				cout << status << endl << endl;
			}
	}

	if (!index)
	{
		cout << "\t未找到可取消的预约记录" << endl;
		return;
	}

	int cancelNum;
	cout << "请输入需要取消的预约号 : ";
	while (true)
	{
		cin >> cancelNum;
		if (cancelNum >= 1 && cancelNum <= v.size())	break;
		else
			cout << "输入有误,请重新输入 : ";
	}

	int option;
	cout << "\t1 --- 确认\t2 --- 取消" << endl;
	cout << "是否确认取消该预约 : ";
	while (true)
	{
		cin >> option;
		if (option == 1 || option == 2)	break;
		else
			cout << "输入有误,请重新输入 : ";
	}

	if (2 == option)
	{
		cout << "\t已取消" << endl;
		return;
	}
	else
	{
	//修改状态并更新
		af.mapAppoint[v[cancelNum-1]]["status"] = "0";
		af.updateAppoint();
		cout << "\t已取消选中的预约记录" << endl;
	}
}
