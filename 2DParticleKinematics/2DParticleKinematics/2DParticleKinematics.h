
// 2DParticleKinematics.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy2DParticleKinematicsApp: 
// �йش����ʵ�֣������ 2DParticleKinematics.cpp
//

class CMy2DParticleKinematicsApp : public CWinApp
{
public:
	CMy2DParticleKinematicsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy2DParticleKinematicsApp theApp;