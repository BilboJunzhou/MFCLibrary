// CDialog1.cpp: 实现文件
//

#include "pch.h"
#include "MFCLibrary.h"
#include "afxdialogex.h"
#include "CDialog1.h"
#include "LibraryMes.h"
#pragma comment(lib,"Project1.lib")

// CDialog1 对话框

IMPLEMENT_DYNAMIC(CDialog1, CDialogEx)


CDialog1::CDialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, bor_num(_T(""))
	, bor_bo(_T(""))
	, re_num(_T(""))
	, re_bo(_T(""))
{

}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, bor_num);
	DDX_Text(pDX, IDC_EDIT2, bor_bo);
	DDX_Text(pDX, IDC_EDIT3, re_num);
	DDX_Text(pDX, IDC_EDIT4, re_bo);
}


BEGIN_MESSAGE_MAP(CDialog1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog1::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDialog1 消息处理程序


void CDialog1::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL CDialog1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	bookWay.saveBookMes();
	studentWay.saveStuMes();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog1::OnBnClickedButton1()
{
	 //TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!bor_bo.IsEmpty() || !bor_num.IsEmpty()) {
		string num1 = (CT2A)bor_num, num2 = (CT2A)bor_bo;
		int a1 = atoi(num1.c_str()), a2 = atoi(num2.c_str());
		if (libraryWay.borrowBook(a2, a1, studentWay, bookWay)) {
			MessageBox(TEXT("借阅成功"));
		}
		else {
			MessageBox(TEXT("借阅失败"));
		}
	}
	else {
		MessageBox(TEXT("输入为空"));
	}
}


void CDialog1::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!re_bo.IsEmpty() || !re_num.IsEmpty()) {
		string num1 = (CT2A)re_num, num2 = (CT2A)re_bo;
		int a1 = atoi(num1.c_str()), a2 = atoi(num2.c_str());
		if (libraryWay.returnBook(a2, a1, studentWay, bookWay)) {
			MessageBox(TEXT("归还成功"));
		}
		else {
			MessageBox(TEXT("归还失败"));
		}
	}
	else {
		MessageBox(TEXT("输入为空"));
	}
}


void CDialog1::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}
