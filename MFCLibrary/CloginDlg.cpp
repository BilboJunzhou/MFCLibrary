// CloginDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCLibrary.h"
#include "afxdialogex.h"
#include "CloginDlg.h"
#include "LibraryMes.h"
#pragma comment(lib,"Project1.lib")
// CloginDlg 对话框

IMPLEMENT_DYNAMIC(CloginDlg, CDialogEx)

CloginDlg::CloginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, reader_name(_T(""))
	, reader_num(_T(""))
{

}

CloginDlg::~CloginDlg()
{
}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, reader_name);
	DDX_Text(pDX, IDC_EDIT2, reader_num);
}


BEGIN_MESSAGE_MAP(CloginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CloginDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CloginDlg 消息处理程序


void CloginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 登录按钮点击事件
	UpdateData(TRUE);
	Library::StudentS stuWay;
	stuWay.saveStuMes();
	if (reader_name.IsEmpty() || reader_num.IsEmpty()) {
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	// 获取正确的值
	string name = (CT2A)reader_name;
	string numG = (CT2A)reader_num;
	auto mesA = stuWay.searchStuMes(atoi(numG.c_str()));
	if (mesA) {
		if (mesA->stu_name == name) {
			if (mesA->stu_num == atoi(numG.c_str()))
				// 关闭当前对话框
				CDialog::OnCancel();
			else MessageBox(TEXT("借阅号有误"));
		}
		else MessageBox(TEXT("用户名有误"));
	}
	else MessageBox(TEXT("借阅号有误"));

}


BOOL CloginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CloginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 回车bug
	CloginDlg::OnBnClickedButton1();

}


void CloginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 退出
	exit(0);
	//CDialogEx::OnClose();
}


void CloginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	exit(0);
}
