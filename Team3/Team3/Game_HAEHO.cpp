#include "stdafx.h"
#include "Game_HAEHO.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"




CGame_HAEHO::CGame_HAEHO()
{
}


CGame_HAEHO::~CGame_HAEHO()
{
}

void CGame_HAEHO::Initialize(void)
{
}

void CGame_HAEHO::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CGame_HAEHO::LateUpdate(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CGame_HAEHO::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CGame_HAEHO::Release(void)
{
	CObjMgr::Destroy_Instance();
}
