
// 2DParticleExplosion.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy2DParticleExplosionApp: 
// �йش����ʵ�֣������ 2DParticleExplosion.cpp
//

class CMy2DParticleExplosionApp : public CWinApp
{
public:
	CMy2DParticleExplosionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy2DParticleExplosionApp theApp;