
#include "SqlServerFunc.h"

//SQL server ����
void func1() {
	string server = "SERVER=127.0.0.1,1434";
	string database = "DATABASE=GameSQL";
	string uid = "UID=sa";
	string pwd = "PWD=1234";

	string conStr = "Provider=SQLOLEDB;" + server + ";" + database + ";" + uid + ";" + pwd + ";";
	cout << conStr << endl;

	//��ʼ��COM����
	::CoInitialize(NULL);

	//�������Ӷ���ʵ�������� 
	_ConnectionPtr pMyConnect(__uuidof(Connection));
	try {
		//����2����������Դ���� �����ݿ⡰SQLServer����������Ҫ�����Լ�PC�����ݿ�����
		pMyConnect->Open("Provider=SQLOLEDB;SERVER=127.0.0.1,1434;DATABASE=GameSQL;UID=sa;PWD=1234;","","",adModeUnknown);
	} catch (_com_error &e) {
		cout << "Initiate failed!" << endl;
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return ;
	}
	cout << "Connect succeed!" << endl;

	//�����¼������ʵ��������
	_RecordsetPtr pMyRecordset(__uuidof(Recordset));
	//����3��������Դ�е����ݿ�/����в���
	try {
		pMyRecordset = pMyConnect->Execute("select * from user_table", NULL, adCmdText);//ִ��SQL�� select * from iecc_Works          

		if (pMyRecordset->BOF) {
			cout << "Data is empty!" << endl;
			return;
		}
		vector<_bstr_t> column_name;

		FieldPtr fp;
		//�洢���������������ʾ�������
		for (long i = 0; i < pMyRecordset->Fields->GetCount(); i++) {
			fp = pMyRecordset->Fields->GetItem(i);
			//cout<< fp->Name << " ";
			//cout<< fp->Type << " ";
			column_name.push_back(fp->Name);
		}
		//�Ա���б�������,��ʾ����ÿһ�е�����
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

	//����4���ر�����Դ �ر����ݿⲢ�ͷ�ָ��
	try {
		pMyRecordset->Close();     //�رռ�¼��               
		pMyConnect->Close();//�ر����ݿ�               
		pMyRecordset.Release();//�ͷż�¼������ָ��               
		pMyConnect.Release();//�ͷ����Ӷ���ָ��
	} catch (_com_error &e) {
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return ;
	}
	::CoUninitialize(); //�ͷ�COM����
}

void func2() {
	//��ʼ��COM����
	::CoInitialize(NULL);

	//ʹ��_ConnectionPtr(����DSN)
	//_ConnectionPtr MyDb;
	//MyDb.CreateInstance(__uuidof(Connection));
	//MyDb->Open("DSN=samp;UID=admin;PWD=admin", "", "", -1);
	//ʹ��_ConnectionPtr(���ڷ�DSN)
	_ConnectionPtr MyDb;
	MyDb.CreateInstance(__uuidof(Connection));
	MyDb->Open("Provider=SQLOLEDB;SERVER=127.0.0.1:1434;DATABASE=GameSQL;UID=sa;PWD=1234", "", "", -1);

	//ʹ��_RecordsetPtrִ��SQL���
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
		MessageBox(NULL, TEXT("DAO��������"), TEXT("tips"), MB_OK);
	}

	//�ͷŶ���
	::CoUninitialize();
}
