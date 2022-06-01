#include "stdafx.h"
#include "Game_SON.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"


CGame_SON::CGame_SON()
{
}


CGame_SON::~CGame_SON()
{
}

void CGame_SON::Initialize(void)
{
}

void CGame_SON::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CGame_SON::LateUpdate(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CGame_SON::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CGame_SON::Release(void)
{
	CObjMgr::Destroy_Instance();
}
