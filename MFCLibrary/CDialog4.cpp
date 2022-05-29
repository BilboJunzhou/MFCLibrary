// CDialog4.cpp: 实现文件
//

#include "pch.h"
#include "MFCLibrary.h"
#include "afxdialogex.h"
#include "CDialog4.h"
#include "LibraryMes.h"

// CDialog4 对话框

IMPLEMENT_DYNAMIC(CDialog4, CDialogEx)
Library::BookS bookWay;
CDialog4::CDialog4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, writerCS(_T(""))
	, nameCS(_T(""))
	, numCS(_T(""))
{

}

CDialog4::~CDialog4()
{
}

void CDialog4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list2);
	DDX_Text(pDX, IDC_EDIT1, writerCS);
	DDX_Text(pDX, IDC_EDIT2, nameCS);
	DDX_Text(pDX, IDC_EDIT3, numCS);
}


BEGIN_MESSAGE_MAP(CDialog4, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialog4::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog4::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog4::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog4::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDialog4 消息处理程序


void CDialog4::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDialog4::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL CDialog4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	bookWay.saveBookMes();
	m_list2.InsertColumn(0, TEXT("书名"), LVCFMT_LEFT, 130);
	m_list2.InsertColumn(1, TEXT("作者"), LVCFMT_LEFT, 130);
	m_list2.InsertColumn(2, TEXT("图书编号"), LVCFMT_LEFT, 110);
	m_list2.InsertColumn(3, TEXT("总量"), LVCFMT_LEFT, 80);
	m_list2.InsertColumn(4, TEXT("现存量"), LVCFMT_LEFT, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog4::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_list2.DeleteAllItems();
	UpdateData(FALSE);

	if (!writerCS.IsEmpty()) {
		string str = (CT2A)writerCS;
		m_list2.DeleteAllItems();
		UpdateData(TRUE);
		auto abc = bookWay.searchBookWriter(str);
		if (abc.empty()) {
			MessageBox(TEXT("该作者没有书籍"));
		}
		else
		{
			CString b;
			for (int i = 0; i < abc.size();i++) {
				m_list2.InsertItem(i, abc[i]->book_name.c_str());
				m_list2.SetItemText(i, 1, abc[i]->writer.c_str());
				
				b.Format("%d", abc[i]->book_num);
				m_list2.SetItemText(i, 2, b);
				b.Format("%d", abc[i]->all_save);
				m_list2.SetItemText(i, 3, b);
				b.Format("%d", abc[i]->now_save);
				m_list2.SetItemText(i, 4, b);
			}
		}
	}
	else MessageBox(TEXT("输入为空"));
}


void CDialog4::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_list2.DeleteAllItems();
	UpdateData(FALSE);
	if (!nameCS.IsEmpty()) {
		string ass = (CT2A)nameCS;
		auto a = bookWay.searchBookName(ass);
		if (bookWay.searchBookName(ass)) {
			m_list2.InsertItem(0, a->book_name.c_str());
			m_list2.SetItemText(0, 1, a->writer.c_str());
			CString b;
			b.Format("%d", a->book_num);
			m_list2.SetItemText(0, 2, b);
			b.Format("%d", a->all_save);
			m_list2.SetItemText(0, 3, b);
			b.Format("%d", a->now_save);
			m_list2.SetItemText(0, 4, b);
		}
		else {
			MessageBox(TEXT("没有该书籍"));
		}
	}
	else
		MessageBox(TEXT("输入为空"));
}


void CDialog4::OnBnClickedButton3()
{
	UpdateData(TRUE);
	m_list2.DeleteAllItems();
	UpdateData(FALSE);
	// TODO: 在此添加控件通知处理程序代码
	if (!numCS.IsEmpty()) {
		string	asd = (CT2A)numCS;
		int numStu = atoi(asd.c_str());
		auto a = bookWay.searchBookNum(numStu);
		if (a) {
			m_list2.InsertItem(0, a->book_name.c_str());
			m_list2.SetItemText(0, 1, a->writer.c_str());
			CString b;
			b.Format("%d", a->book_num);
			m_list2.SetItemText(0, 2, b);
			b.Format("%d", a->all_save);
			m_list2.SetItemText(0, 3, b);
			b.Format("%d", a->now_save);
			m_list2.SetItemText(0, 4, b);
		}
		else {
			MessageBox(TEXT("没有该书籍"));
		}
	}
	else MessageBox(TEXT("内容为空"));
}


void CDialog4::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}
