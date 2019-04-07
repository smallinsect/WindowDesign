
#include "SqlServerFunc.h"

//SQL server 连接
void func1() {
	string server = "SERVER=127.0.0.1,1434";
	string database = "DATABASE=GameSQL";
	string uid = "UID=sa";
	string pwd = "PWD=1234";

	string conStr = "Provider=SQLOLEDB;" + server + ";" + database + ";" + uid + ";" + pwd + ";";
	cout << conStr << endl;

	//初始化COM环境
	::CoInitialize(NULL);

	//定义连接对象并实例化对象 
	_ConnectionPtr pMyConnect(__uuidof(Connection));
	try {
		//步骤2：创建数据源连接 打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况
		pMyConnect->Open("Provider=SQLOLEDB;SERVER=127.0.0.1,1434;DATABASE=GameSQL;UID=sa;PWD=1234;","","",adModeUnknown);
	} catch (_com_error &e) {
		cout << "Initiate failed!" << endl;
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return ;
	}
	cout << "Connect succeed!" << endl;

	//定义记录集对象并实例化对象
	_RecordsetPtr pMyRecordset(__uuidof(Recordset));
	//步骤3：对数据源中的数据库/表进行操作
	try {
		pMyRecordset = pMyConnect->Execute("select * from user_table", NULL, adCmdText);//执行SQL： select * from iecc_Works          

		if (pMyRecordset->BOF) {
			cout << "Data is empty!" << endl;
			return;
		}
		vector<_bstr_t> column_name;

		FieldPtr fp;
		//存储表的所有列名，显示表的列名
		for (long i = 0; i < pMyRecordset->Fields->GetCount(); i++) {
			fp = pMyRecordset->Fields->GetItem(i);
			//cout<< fp->Name << " ";
			//cout<< fp->Type << " ";
			column_name.push_back(fp->Name);
		}
		//对表进行遍历访问,显示表中每一行的内容
		while (!pMyRecordset->adoEOF) {
			
			for (vector<_bstr_t>::iterator iter = column_name.begin(); 
				iter != column_name.end(); iter++) {
				_variant_t variant = pMyRecordset->GetCollect(*iter);
				if(variant.vt !=VT_NULL){
				    cout<<(_bstr_t)variant << " ";
				}else{
				    cout<<"NULL";
				}
			}
			cout << endl;
			pMyRecordset->MoveNext();
		}
	} catch (_com_error &e) {
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return ;
	}

	//步骤4：关闭数据源 关闭数据库并释放指针
	try {
		pMyRecordset->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pMyRecordset.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	} catch (_com_error &e) {
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return ;
	}
	::CoUninitialize(); //释放COM环境
}

void func2() {
	//初始化COM环境
	::CoInitialize(NULL);

	//使用_ConnectionPtr(基于DSN)
	//_ConnectionPtr MyDb;
	//MyDb.CreateInstance(__uuidof(Connection));
	//MyDb->Open("DSN=samp;UID=admin;PWD=admin", "", "", -1);
	//使用_ConnectionPtr(基于非DSN)
	_ConnectionPtr MyDb;
	MyDb.CreateInstance(__uuidof(Connection));
	MyDb->Open("Provider=SQLOLEDB;SERVER=127.0.0.1:1434;DATABASE=GameSQL;UID=sa;PWD=1234", "", "", -1);

	//使用_RecordsetPtr执行SQL语句
	_RecordsetPtr MySet;
	MySet.CreateInstance(__uuidof(Recordset));
	MySet->Open("select * from some_table",
		MyDb.GetInterfacePtr(),
		adOpenDynamic,
		adLockOptimistic, adCmdText);

	_variant_t Holder;
	try {
		while (!MySet->BOF) {
			Holder = MySet->GetCollect("FILE_1");
			if (Holder.vt != VT_NULL) {
				cout << Holder.bstrVal << endl;
			}
			MySet->MoveNext();
		}
	} catch (_com_error e) {
		//CString Error = e.ErrorMessage();
		//AfxMessageBox(e.ErrorMessage());
	} catch (...){
		MessageBox(NULL, TEXT("DAO发生错误"), TEXT("tips"), MB_OK);
	}

	//释放对象
	::CoUninitialize();
}
