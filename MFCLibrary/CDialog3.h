#pragma once
#include "afxdialogex.h"
#include "LibraryMes.h"
#pragma comment(lib,"Project1.lib")

// CDialog3 对话框

class CDialog3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog3)

public:
	CDialog3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list1;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CString stu_num;
	CString stu_name;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CString stu_numm;
	CString instert_num;
	Library::StudentS stuWay;
	Library::BookS bookWay;
	afx_msg void OnBnClickedButton3();
	virtual void OnCancel();
};
