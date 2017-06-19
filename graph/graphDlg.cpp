
// graphDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "graph.h"
#include "graphDlg.h"
#include "afxdialogex.h"
#include <ctime>
#include <sstream>
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CgraphDlg::CgraphDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAPH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgraphDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CgraphDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CgraphDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CgraphDlg ��Ϣ�������

BOOL CgraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CgraphDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// print the game area boundary
void CgraphDlg::printBox()
{
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect(rect);

	for (int i = rect.top + side; i <= rect.bottom - down - side; i++)
	{
		pDC->SetPixel(rect.left + side, i, black);
		pDC->SetPixel(rect.right - side, i, black);
	}

	for (int i = rect.left + side; i <= rect.right - side; i++)
	{
		pDC->SetPixel(i, rect.top + side, black);
		pDC->SetPixel(i, rect.bottom - down - side, black);
	}
}

// clear the game area, with init color
void CgraphDlg::clearBox()
{
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect(rect);
	rect.bottom -= side + down;
	rect.top += side + 1;
	rect.left += side + 1;
	rect.right -= side;

	pDC->FillSolidRect(rect, background);

}

// init function
void CgraphDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}


	srand(time(NULL));
	CDC *pdc = GetDC();
	background = pdc->GetPixel(0, 0);
	printBox();
}

HCURSOR CgraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// start game
void CgraphDlg::OnBnClickedOk()
{
	//clearBox();
	SetTimer(1, flush, NULL);				// flush the frame, per flush ms
	SetTimer(2, create, NULL);				// create a bubble, per create ms
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// CDialogEx::OnOK();
}

// exit game
void CgraphDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

// draw the circles in the list, with input color
void drawCircle(std::list<node> &point, CDC *dc, int top, int left, int right, COLORREF color)
{
	CBrush *brush = new CBrush(color);
	CBrush *old = dc->SelectObject(brush);		// change color
	auto p = point.begin();
	while (p != point.end())
	{
		// go up
		p->o.y -= p->v;

		// left or right
		int mx = rand() % 4;
		if (p->o.x + p->dir * mx - p->r <= left || p->o.x + p->dir * mx + p->r >= right)
			p->dir = -p->dir;	
		
		p->o.x += p->dir * mx;

		if (rand() % 8 == 0)
		{
			p->dir = rand() % 3 - 1;
		}


		// disappear or not
		if (p->o.y - p->r < top)
			p = point.erase(p);
		else
		{
			dc->Ellipse(p->o.x - p->r, p->o.y - p->r, p->o.x + p->r, p->o.y + p->r);
			p++;
		}
	}
	dc->SelectObject(old);		// change color back
}

// timer
void CgraphDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDC *dc = GetDC();
	CRect rect;
	GetClientRect(rect);
	rect.right -= side;
	rect.left += side;
	rect.top += side;
	rect.bottom -= down + side;
	if(nIDEvent == 2)		//create a bubble timer, or flush timer
	{
		if (rand() & 1)
		{
			if (rand() % 6 == 0)  // 3 points, faster  or 1 point, slower
			{
				node temp;
				temp.r = rand() % 6 + 6;	// r -> 2 - 5
				temp.o.x = rand() % (int)(rect.right - rect.left - 2 * temp.r - 1) + rect.left + temp.r;
				temp.v = rand() % 10 + 4;	// v-> 10 - 25
				temp.o.y = rect.bottom - temp.r - 1 + temp.v;
				temp.dir = rand() % 3 - 1;
				point3.push_back(temp);
			}
			else
			{
				node temp;
				temp.r = rand() % 8 + 8;	// r -> 6 - 13
				temp.o.x = rand() % (int)(rect.right - rect.left - 2 * temp.r - 1) + rect.left + temp.r;
				temp.v = rand() % 5 + 2;	// v-> 5 - 12
				temp.o.y = rect.bottom - temp.r - 1 + temp.v;
				temp.dir = rand() % 3 - 1;
				point1.push_back(temp);
			}
		}
	}
	else
	{
		clearBox();

		drawCircle(point3, dc, rect.top, rect.left, rect.right, red);
		drawCircle(point1, dc, rect.top, rect.left, rect.right, white);
	}
	CDialogEx::OnTimer(nIDEvent);
}


// calc the distance between (x, y) and (xx, yy)
inline int dis(int x, int y, int xx, int yy)
{
	return (xx - x) * (xx - x) + (yy - y) * (yy - y);
}

// test clickPoint is in one circle in the list or not
bool testPoint(std::list<node> &point, CPoint clickPoint, int p, int &score)
{
	auto e = point.begin();
	while (e != point.end())
	{
		if (dis(e->o.x, e->o.y, clickPoint.x, clickPoint.y) <= e->r * e->r)
		{
			score += p;
			e = point.erase(e);
			return true;
		}
		else
		{
			e++;
		}
	}
	return false;
}

// int to string
std::string itos(int i)
{
	std::ostringstream os;
	os << i;
	return os.str();
}

// check the bubbles in the list, and update the score
void CgraphDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!testPoint(point1, point, 1, score))
		testPoint(point3, point, 3, score);
	GetDlgItem(IDC_score)->SetWindowText(itos(score).c_str());
	CDC *dc = GetDC();
	dc->SetTextColor(black);
	CDialogEx::OnLButtonDown(nFlags, point);
}

