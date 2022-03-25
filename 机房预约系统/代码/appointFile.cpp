#include"appointFile.h"

//截取数据
pair<string, string> Pairing(string str)
{
	int pos = str.find(":");
	if (pos == -1)
	{
		cout << "\tError ---- 预约数据有误!" << endl;
		exit(1);
	}

	string key = str.substr(0, pos);
	string value = str.substr(pos + 1, str.size() - pos - 1);

	return make_pair(key, value);
}

//默认构造
AppointFile::AppointFile()
{
	ifstream ifs(APPOINT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "\tError ---- 文件不存在!" << endl;
		ifs.close();
		return;
	}

	map<string, string> m;

	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	//读入数据 读入的为一整段数据 : data:1
	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
	//截取申请日期
		pair<string, string> datePair = Pairing(date);
		m.insert(datePair);

	//截取申请时间段
		pair<string, string> intervalPair = Pairing(interval);
		m.insert(intervalPair);

	//截取学号
		pair<string, string> stuIdPair = Pairing(stuId);
		m.insert(stuIdPair);

	//截取学生用户名
		pair<string, string> stuNamePair = Pairing(stuName);
		m.insert(stuNamePair);

	//截取申请的机房编号
		pair<string, string> roomIdPair = Pairing(roomId);
		m.insert(roomIdPair);

	//截取预约状态
		pair<string, string> statusPair = Pairing(status);
		m.insert(statusPair);

		this->mapAppoint.insert(make_pair(M_Size++, m));
		m.clear();
	}
	ifs.close();

	//测试大容器
	//for (map<int, map<string, string>>::iterator it = mapAppoint.begin(); it != mapAppoint.end(); it++)
	//{
	//	cout << "第 " << it->first + 1 << " 条预约记录 : ";
	//	for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << "key = " << mit->first << " value = " << mit->second << endl;
	//	}
	//	cout << endl;
	//}
}

//更新预约记录
void AppointFile::updateAppoint()
{
	if (!this->M_Size)
		return;

	ofstream ofs(APPOINT_FILE, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		cout << "\tError ---- 文件不存在!" << endl;
		ofs.close();
		return;
	}

	for (int i = 0; i < this->M_Size; i++)
	{
		ofs << "date:" << this->mapAppoint[i]["date"] << " ";
		ofs << "interval:" << this->mapAppoint[i]["interval"] << " ";
		ofs << "stuId:" << this->mapAppoint[i]["stuId"] << " ";
		ofs << "stuName:" << this->mapAppoint[i]["stuName"] << " ";
		ofs << "roomId:" << this->mapAppoint[i]["roomId"] << " ";
		ofs << "status:" << this->mapAppoint[i]["status"] << " ";
	}
}
