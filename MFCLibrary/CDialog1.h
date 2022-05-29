#pragma once
#include "afxdialogex.h"
#include "LibraryMes.h"
#pragma comment(lib,"Project1.lib")
// CDialog1 对话框

class CDialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog1)

public:
	CDialog1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString bor_num;
	CString bor_bo;
	CString re_num;
	CString re_bo;
	Library::BookS bookWay;
	Library::StudentS studentWay;
	Library libraryWay;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void OnCancel();
};
