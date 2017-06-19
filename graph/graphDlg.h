
// graphDlg.h : 头文件
//

#pragma once

#include <vector>
#include <list>
#include "afxwin.h"
class node
{
public:
	CPoint o;
	double r;
	int v;
	int dir;
};

// CgraphDlg 对话框
class CgraphDlg : public CDialogEx
{
// 构造
public:
	CgraphDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;


	// my variables
	COLORREF background = RGB(255, 255, 255);
	COLORREF red = RGB(255, 0, 0);
	COLORREF black = RGB(0, 0, 0);
	COLORREF white = RGB(255, 255, 255);
	const int down = 100;
	const int side = 20;
	const int flush = 50;
	const int create = 200;
	int score = 0;
	// end variables

	// my function
	void printBox();
	void clearBox();
	std::list<node> point1;
	std::list<node> point3;
	// end function


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
