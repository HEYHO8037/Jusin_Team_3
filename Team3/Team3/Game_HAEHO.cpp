#include "stdafx.h"
#include "Game_HAEHO.h"
#include "Player_Ho.h"

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
	D3DXVECTOR3 pos;
	pos.x = 100.f;
	pos.y = 100.f;
	
	CObj* pObj = CAbstractFactory<CPlayer_Ho>::Create(pos, 0.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pObj);
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
