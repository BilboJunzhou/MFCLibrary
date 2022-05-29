// CDialog3.cpp: 实现文件
//

#include "pch.h"
#include "MFCLibrary.h"
#include "afxdialogex.h"
#include "CDialog3.h"
#include "LibraryMes.h"
#pragma comment(lib,"Project1.lib")
// CDialog3 对话框

IMPLEMENT_DYNAMIC(CDialog3, CDialogEx)

CDialog3::CDialog3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, stu_num(_T(""))
	, stu_name(_T(""))
	, stu_numm(_T(""))
	, instert_num(_T(""))
{

}

CDialog3::~CDialog3()
{
}

void CDialog3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_EDIT1, stu_num);
	DDX_Text(pDX, IDC_EDIT2, stu_name);
	DDX_Text(pDX, IDC_EDIT3, stu_numm);
	DDX_Text(pDX, IDC_EDIT4, instert_num);
}


BEGIN_MESSAGE_MAP(CDialog3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog3::OnBnClickedButton2)

	ON_BN_CLICKED(IDC_BUTTON1, &CDialog3::OnBnClickedButton1)

	ON_BN_CLICKED(IDC_BUTTON3, &CDialog3::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDialog3 消息处理程序





BOOL CDialog3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	stuWay.saveStuMes();
	bookWay.saveBookMes();
	m_list1.InsertColumn(0, TEXT("学生姓名"), LVCFMT_LEFT, 60);
	m_list1.InsertColumn(1, TEXT("学生借阅号码"), LVCFMT_LEFT, 60);
	m_list1.InsertColumn(3, TEXT("借阅书籍1"), LVCFMT_LEFT, 70);
	m_list1.InsertColumn(4, TEXT("时间"), LVCFMT_LEFT, 55);
	m_list1.InsertColumn(5, TEXT("借阅书籍2"), LVCFMT_LEFT, 70);
	m_list1.InsertColumn(6, TEXT("时间"), LVCFMT_LEFT, 55);
	//for (int i = 0; i < stuWay.stu_mes_save.size(); i++) {
	//	m_list1.InsertItem(i, stuWay.stu_mes_save[i]->stu_name.c_str());
	//	//m_list1.Format(i, stuWay.stu_mes_save[i]->stu_name.c_str());
	//	CString sss;
	//	sss.Format("%d", stuWay.stu_mes_save[i]->stu_num);
	//	m_list1.SetItemText(i, 1, sss);
	//}


	m_list1.Update(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog3::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_list1.DeleteAllItems();
	stuWay.saveStuMes();
	bookWay.saveBookMes();
	//int numm = atoi((CT2A)aio);
	string num = (CT2A)stu_numm;
	int numm = atoi(num.c_str());
	string name = (CT2A)stu_name;
	if (!stu_num.IsEmpty() || !stu_name.IsEmpty()) {
		if (stuWay.stu_hash_save.find(numm) == stuWay.stu_hash_save.end()) {
			stuWay.getStuMes(name, numm);
			MessageBox(TEXT("插入成功"));
		}
		else
		{
			MessageBox(TEXT("该号码已存在"));
		}
	}
	else MessageBox(TEXT("输入内容为空"));
}


void CDialog3::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialog3::OnBnClickedButton2();
	//CDialogEx::OnOK();
}



void CDialog3::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	m_list1.DeleteAllItems();
	UpdateData(TRUE);
	stuWay.saveStuMes();
	//cout << stuWay.stu_mes_save.size();
	bookWay.saveBookMes();
	CString sss;
	for (int i = 0; i < stuWay.stu_mes_save.size(); i++) {
		m_list1.InsertItem(i, stuWay.stu_mes_save[i]->stu_name.c_str());
		//m_list1.Format(i, stuWay.stu_mes_save[i]->stu_name.c_str());
		sss.Format("%d", stuWay.stu_mes_save[i]->stu_num);
		m_list1.SetItemText(i, 1, sss); 

		if (stuWay.stu_mes_save[i]->stu_borrow1.first == 0) {
			m_list1.SetItemText(i, 2, TEXT("无"));
		}
		else {
			auto aNum = bookWay.searchBookNum(stuWay.stu_mes_save[i]->stu_borrow1.first);
			m_list1.SetItemText(i, 2, aNum->book_name.c_str());
			m_list1.SetItemText(i, 3, stuWay.stu_mes_save[i]->stu_borrow1.second.c_str());
		}
		if (stuWay.stu_mes_save[i]->stu_borrow2.first == 0) {
			m_list1.SetItemText(i, 4, TEXT("无"));
		}
		else {
			auto aNum = bookWay.searchBookNum(stuWay.stu_mes_save[i]->stu_borrow2.first);
			m_list1.SetItemText(i, 4, aNum->book_name.c_str());
			m_list1.SetItemText(i, 5, stuWay.stu_mes_save[i]->stu_borrow2.second.c_str());
		}
	}
}




void CDialog3::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//取得ListBox
	UpdateData(TRUE);
	m_list1.DeleteAllItems();
	UpdateData(FALSE);
	stuWay.saveStuMes();
	bookWay.saveBookMes();
	if (!instert_num.IsEmpty()) {
		string aa = (CT2A)instert_num;
		int numa = atoi(aa.c_str());
		auto asd = stuWay.searchStuMes(numa);
		if (asd) {
			m_list1.InsertItem(0, asd->stu_name.c_str());
			//m_list1.Format(i, stuWay.stu_mes_save[i]->stu_name.c_str());
			CString sss;
			sss.Format("%d", asd->stu_num);
			m_list1.SetItemText(0, 1, sss);
			if (asd->stu_borrow1.first == 0) {
				m_list1.SetItemText(0, 2, TEXT("无"));
			}
			else {
				auto aNum = bookWay.searchBookNum(asd->stu_borrow1.first);
				m_list1.SetItemText(0, 2, aNum->book_name.c_str());
				m_list1.SetItemText(0, 3, asd->stu_borrow1.second.c_str());
			}
			if (asd->stu_borrow2.first == 0) {
				m_list1.SetItemText(0, 4, TEXT("无"));
			}
			else {
				auto aNum = bookWay.searchBookNum(asd->stu_borrow2.first);
				m_list1.SetItemText(0, 4, aNum->book_name.c_str());
				m_list1.SetItemText(0, 5, asd->stu_borrow2.second.c_str());
			}
		}
		else
		{
			MessageBox(TEXT("不存在该学生"));
		}
		
	}
	else MessageBox(TEXT("输入内容为空"));
}


void CDialog3::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}
