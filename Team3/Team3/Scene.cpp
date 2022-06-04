#include "stdafx.h"
#include "Scene.h"
#include "BmpMgr_3.h"


CScene::CScene()
{
	m_hMemDC = CBmpMgr_3::Get_Instance()->Find_Image(L"GROUND");
}


CScene::~CScene()
{
}
