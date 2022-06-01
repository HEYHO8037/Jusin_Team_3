#include "stdafx.h"
#include "Game_SEOK.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"


CGame_SEOK::CGame_SEOK()
{
}


CGame_SEOK::~CGame_SEOK()
{
}

void CGame_SEOK::Initialize(void)
{
}

void CGame_SEOK::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CGame_SEOK::LateUpdate(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CGame_SEOK::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CGame_SEOK::Release(void)
{
	CObjMgr::Destroy_Instance();
}
