#include "stdafx.h"
#include "Game_SEOK.h"
#include "Player_Seok.h"
#include "Monster_SEOK.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"


CGame_SEOK::CGame_SEOK()
{
}


CGame_SEOK::~CGame_SEOK()
{
}

void CGame_SEOK::Initialize(void)
{
	CLineMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_Seok>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_SEOK>::Create());
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
	CLineMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CGame_SEOK::Release(void)
{
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Destroy_Instance();

}
