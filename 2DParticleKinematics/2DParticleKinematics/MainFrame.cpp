// MainFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "2DParticleKinematics.h"
#include "MainFrame.h"
#include "Resource.h"


// CMainFrame
const int NEWBORDERWIDTH = 2;

IMPLEMENT_DYNAMIC(CMainFrame, CWnd)

CMainFrame::CMainFrame()
{
	m_captionPanel.m_hWnd = NULL;
	m_clientPanel.m_hWnd = NULL;
}

CMainFrame::~CMainFrame()
{
}


BEGIN_MESSAGE_MAP(CMainFrame, CWnd)
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CMainFrame 消息处理程序




BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	HINSTANCE hInstance = (HINSTANCE)AfxGetInstanceHandle();
	ASSERT(hInstance);

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	// check if the wndclass has been registered
	BOOL bRet = GetClassInfoEx(hInstance, cs.lpszClass, &wcex);
	if (bRet) return TRUE;

	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = AfxWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = (HICON)::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON32));
	wcex.hIconSm = (HICON)::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON32));
	// wcex.hIcon = (HICON)::LoadImage(NULL, _T("res\\2DParticleKinematic\\ICON.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = cs.lpszClass;

	// Register the wndclass
	bRet = RegisterClassEx(&wcex);

	return bRet;
	//return CWnd::PreCreateWindow(cs);
}


void CMainFrame::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CWnd::PostNcDestroy();
}


void CMainFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nCxBorder = ::GetSystemMetrics(SM_CXBORDER);
	int nCyBorder = ::GetSystemMetrics(SM_CYBORDER);

	// lpncsp.rgrc[0] is the Rect of client
	// make window rect filled with client
	lpncsp->rgrc[0].left -= nCxBorder;
	lpncsp->rgrc[0].right += nCxBorder;
	lpncsp->rgrc[0].top -= nCyBorder;
	lpncsp->rgrc[0].bottom += nCyBorder;

	// set new non-client
	lpncsp->rgrc[0].left += NEWBORDERWIDTH;
	lpncsp->rgrc[0].right -= NEWBORDERWIDTH;
	lpncsp->rgrc[0].top += NEWBORDERWIDTH;
	lpncsp->rgrc[0].bottom -= NEWBORDERWIDTH;

	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CMainFrame::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	CWindowDC dc(this);
	CRect rcWnd;
	GetWindowRect(rcWnd);
	if (!m_imgBorder.IsNull())
	{
		// draw top border
		m_imgBorder.Draw(dc.m_hDC, 0, 0, rcWnd.Width(), NEWBORDERWIDTH);
		// draw left border
		m_imgBorder.Draw(dc.m_hDC, 0, 0, NEWBORDERWIDTH, rcWnd.Height());
		// draw right border
		m_imgBorder.Draw(dc.m_hDC, rcWnd.Width() - NEWBORDERWIDTH, 0, NEWBORDERWIDTH, rcWnd.Height());
		// draw bottom border
		m_imgBorder.Draw(dc.m_hDC, 0, rcWnd.Height() - NEWBORDERWIDTH, rcWnd.Width(), NEWBORDERWIDTH);
	}
	// 不为绘图消息调用 CWnd::OnNcPaint()
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	// TODO:  在此添加您专用的创建代码
	if (m_imgBorder.IsNull())
	{
		m_imgBorder.LoadFromResource(AfxGetInstanceHandle(), IDB_BORDER);
	}

	if (m_captionPanel.m_hWnd == NULL)
	{
		m_captionPanel.Create(_T("CaptionPanel"), WS_CHILD | WS_VISIBLE, CRect(0, 0, lpCreateStruct->cx - 4, 30), this, 10001);
	}

	if (m_clientPanel.m_hWnd == NULL)
	{
		m_clientPanel.Create(_T("ClientPanel"), WS_CHILD | WS_VISIBLE, CRect(0, 30, lpCreateStruct->cx - 4, lpCreateStruct->cy), this, 10002);
	}
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rcClient;
	GetClientRect(rcClient);
	if (m_captionPanel.m_hWnd)
	{
		CRect rcCaption = rcClient;
		rcCaption.bottom = 30;
		m_captionPanel.MoveWindow(rcCaption);
	}

	if (m_clientPanel.m_hWnd)
	{
		CRect rcC = rcClient;
		rcC.top = 30;
		m_clientPanel.MoveWindow(rcC);
	}
}
