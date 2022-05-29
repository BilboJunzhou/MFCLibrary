#pragma once
#include "afxdialogex.h"


// CloginDlg 对话框

class CloginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CloginDlg)

public:
	CloginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CloginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString reader_name;
	CString reader_num;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	virtual void OnCancel();
};
