
// 2DParticlesSimulator.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "2DParticlesSimulator.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2DParticlesSimulatorApp

BEGIN_MESSAGE_MAP(CMy2DParticlesSimulatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMy2DParticlesSimulatorApp ����

CMy2DParticlesSimulatorApp::CMy2DParticlesSimulatorApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMy2DParticlesSimulatorApp ����

CMy2DParticlesSimulatorApp theApp;


// CMy2DParticlesSimulatorApp ��ʼ��

BOOL CMy2DParticlesSimulatorApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CMainFrame* pMainFrame = new CMainFrame();
	// create window, including register window
	pMainFrame->CreateEx(0, _T("MAINFRAMECLASS"), _T("2D Particle Simulator"), WS_POPUPWINDOW | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, CRect(0, 0, 1000, 700), NULL, NULL, NULL);
	// for conveneince, link pMainFrame to theApp
	m_pMainWnd = pMainFrame;
	// show and update the window
	pMainFrame->CenterWindow();
	pMainFrame->ShowWindow(SW_SHOW);
	pMainFrame->UpdateWindow();

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return TRUE;
}

