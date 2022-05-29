#pragma once
#include "afxdialogex.h"


// CDialog4 对话框

class CDialog4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog4)

public:
	CDialog4(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog4();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CListCtrl m_list2;
	CString writerCS;
	CString nameCS;
	CString numCS;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual void OnCancel();
};
