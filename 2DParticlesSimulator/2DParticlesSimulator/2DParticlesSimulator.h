
// 2DParticlesSimulator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy2DParticlesSimulatorApp: 
// �йش����ʵ�֣������ 2DParticlesSimulator.cpp
//

class CMy2DParticlesSimulatorApp : public CWinApp
{
public:
	CMy2DParticlesSimulatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy2DParticlesSimulatorApp theApp;