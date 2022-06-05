#include "stdafx.h"
#include "Game_HAEHO.h"
#include "Player_Ho.h"
#include "Monster_HO.h"
#include "CollisionMgr.h"
#include "Wall_HO.h"
#include "SceneMgr.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"




CGame_HAEHO::CGame_HAEHO()
{
}


CGame_HAEHO::~CGame_HAEHO()
{
	Release();
}

void CGame_HAEHO::Initialize(void)
{
	D3DXVECTOR3 pos;
	pos.x = 100.f;
	pos.y = 100.f;

	CWall_HO* pWall = new CWall_HO(400, 500);
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, pWall);

	pWall = new CWall_HO(400, 450);
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, pWall);

	CObj* pObj = CAbstractFactory<CPlayer_Ho>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pObj);

	pos.x = 600.f;
	pos.y = 500.f;
	CObj* pMonsterObj = CAbstractFactory<CMonster_HO>::Create(pos);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonsterObj);
	dynamic_cast<CMonster_HO*>(pMonsterObj)->Set_Target(pObj);

	pos.x = 300.f;
	pos.y = 100.f;
	pMonsterObj = CAbstractFactory<CMonster_HO>::Create(pos);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonsterObj);
	dynamic_cast<CMonster_HO*>(pMonsterObj)->Set_Target(pObj);

}

void CGame_HAEHO::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CGame_HAEHO::LateUpdate(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).empty())
	{
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
		CCollisionMgr::Collision_MonsterRayCast(dynamic_cast<CPlayer_Ho*>(pPlayer)->Get_PovRayCast(), dynamic_cast<CPlayer_Ho*>(pPlayer)->Get_GunPoint(), CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));
		CCollisionMgr::Collision_Wall_Bullet(CObjMgr::Get_Instance()->Get_ObjList(OBJ_WALL), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
		CCollisionMgr::Collision_Bullet_Monster(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));
		CCollisionMgr::Collision_Bullet_Player(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER));
	}


}

void CGame_HAEHO::Render(HDC hDC)
{
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty() || CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).empty())
	{
		//TextOut(hDC, 400, 300, TEXT("Game Over"), 10);
		//Sleep(1000);
		CSceneMgr::Get_Instance()->Scene_Change(GAME_MENU);
	}

}

void CGame_HAEHO::Release(void)
{
	CObjMgr::Destroy_Instance();
}
