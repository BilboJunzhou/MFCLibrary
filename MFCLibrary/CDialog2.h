#pragma once
#include "afxdialogex.h"


// CDialog2 对话框

class CDialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog2)

public:
	CDialog2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list3;
	CString book_num;
	CString book_name;
	CString book_writer;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	virtual void OnCancel();
};
