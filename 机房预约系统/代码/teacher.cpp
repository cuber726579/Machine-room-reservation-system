#include"teacher.h"

Teacher::Teacher()
{

}

Teacher::Teacher(int id, string usrName, string pwd)
{
	M_TeacherId = id;
	M_UsrName = usrName;
	M_Password = pwd;
}

void Teacher::operMenu()
{
	cout << "\t\t老师 : " << this->M_UsrName << endl;
	cout << "\t-----------------------" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     1.查看全部预约  |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     2.审核预约      |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t|     0.注销登录      |" << endl;
	cout << "\t|                     |" << endl;
	cout << "\t-----------------------" << endl;
}

void Teacher::viewAppointment_All()
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

void Teacher::checkAppointment()
{
	AppointFile af;
	if (!af.M_Size)
	{
		cout << "\t无预约记录" << endl;
		return;
	}

	vector<int> v;
	int index = 0;
	for (int i = 0; i < af.M_Size; i++)
		if ("1" == af.mapAppoint[i]["status"])
		{
			if (0 == index)
				cout << "    待审核的预约 : " << endl;
			v.push_back(i);

			cout << "\t\t第 " << ++index << " 条记录" << endl;
			cout << "预约用户学号: " << af.mapAppoint[i]["stuId"];
			cout << "\t预约日期: 周" << af.mapAppoint[i]["date"];
			cout << " " << (af.mapAppoint[i]["interval"] == "1" ? "上午" : "下午");
			cout << "\t机房号: " << af.mapAppoint[i]["roomId"] << endl << endl;
		}

	if (!index)
	{
		cout << "\t未找到需要审核的预约" << endl;
		return;
	}

	int checkNum;
	cout << "请输入需要审核的预约号 : ";
	while (true)
	{
		cin >> checkNum;
		if (checkNum >= 1 && checkNum <= v.size())	break;
		else
			cout << "输入有误,请重新输入 : ";
	}

	int option;
	cout << "\t1 --- 通过\t2 --- 不通过" << endl;
	cout << "是否确认通过该预约 : ";
	while (true)
	{
		cin >> option;
		if (option == 1 || option == 2)	break;
		else
			cout << "输入有误,请重新输入 : ";
	}

	if (2 == option)
	{
		af.mapAppoint[v[checkNum - 1]]["status"] = "-1";
		af.updateAppoint();
		cout << "\t未通过选中的预约记录" << endl;
	}
	else
	{
		//修改状态并更新
		af.mapAppoint[v[checkNum - 1]]["status"] = "2";
		af.updateAppoint();
		cout << "\t已通过选中的预约记录" << endl;
	}
}
