#include "stdafx.h"
#include "Game_JUN.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "Player_JUN.h"


CGame_JUN::CGame_JUN()
{
}


CGame_JUN::~CGame_JUN()
{
}

void CGame_JUN::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_JUN>::Create());
}

void CGame_JUN::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CGame_JUN::LateUpdate(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CGame_JUN::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CGame_JUN::Release(void)
{
	CObjMgr::Destroy_Instance();
}
