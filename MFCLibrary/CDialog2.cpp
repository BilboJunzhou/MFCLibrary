// CDialog2.cpp: 实现文件
//

#include "pch.h"
#include "MFCLibrary.h"
#include "afxdialogex.h"
#include "CDialog2.h"
#include "LibraryMes.h"
#pragma comment(lib,"Project1.lib")
// CDialog2 对话框

IMPLEMENT_DYNAMIC(CDialog2, CDialogEx)
Library::BookS bookway;
CDialog2::CDialog2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, book_num(_T(""))
	, book_name(_T(""))
	, book_writer(_T(""))
{

}

CDialog2::~CDialog2()
{
}

void CDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list3);
	DDX_Text(pDX, IDC_EDIT1, book_num);
	DDX_Text(pDX, IDC_EDIT2, book_name);
	DDX_Text(pDX, IDC_EDIT3, book_writer);
}


BEGIN_MESSAGE_MAP(CDialog2, CDialogEx)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialog2::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog2::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog2::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDialog2 消息处理程序




void CDialog2::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL CDialog2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(TRUE);
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化
	bookway.saveBookMes();
	m_list3.InsertColumn(0, TEXT("书名"), LVCFMT_LEFT, 85);
	m_list3.InsertColumn(1, TEXT("作者"), LVCFMT_LEFT, 65);
	m_list3.InsertColumn(2, TEXT("图书编号"), LVCFMT_LEFT, 70);
	m_list3.InsertColumn(3, TEXT("总量"), LVCFMT_LEFT, 55);
	m_list3.InsertColumn(4, TEXT("现存量"), LVCFMT_LEFT, 55);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog2::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list3.DeleteAllItems();
	UpdateData(TRUE);
	bookway.saveBookMes();
	CString b;
	for (int i = 0; i < bookway.book_save.size(); i++) {
		m_list3.InsertItem(i, bookway.book_save[i]->book_name.c_str());
		m_list3.SetItemText(i, 1, bookway.book_save[i]->writer.c_str());

		b.Format("%d", bookway.book_save[i]->book_num);
		m_list3.SetItemText(i, 2, b);
		b.Format("%d", bookway.book_save[i]->all_save);
		m_list3.SetItemText(i, 3, b);
		b.Format("%d", bookway.book_save[i]->now_save);
		m_list3.SetItemText(i, 4, b);
	}
}


void CDialog2::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!book_name.IsEmpty() || !book_num.IsEmpty() || !book_writer.IsEmpty()) {
		string name = (CT2A)book_name, num = (CT2A)book_num, writer = (CT2A)book_writer;
		bookway.writeBookMes(name, atoi(num.c_str()), writer);
	}
	else {
		MessageBox(TEXT("输入信息为空"));
	}
	CDialog2::OnBnClickedButton3();
}


void CDialog2::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}
