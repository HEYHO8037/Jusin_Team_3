#include "stdafx.h"
#include "Tetris.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "TileMgr.h"


CTetris::CTetris()
{
}


CTetris::~CTetris()
{
	Release();
}

void CTetris::Initialize(void)
{

	/*for (int i = 0; i < 5; ++i)
	{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY));
	}*/
	//CLineMgr::Get_Instance()->Initialize();

	CTileMgr::Get_Instance()->Initialize();

	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create());
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
}	


void CTetris::Update(void)
{
	//CObjMgr::Get_Instance()->Update();	
	CTileMgr::Get_Instance()->Update();

}

void CTetris::LateUpdate(void)
{
	//CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->LateUpdate();

}

void CTetris::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	/*HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundMemDC, 0, 0, SRCCOPY);*/

	CTileMgr::Get_Instance()->Render(hDC);

	//CLineMgr::Get_Instance()->Render(hMemDC);
	//CObjMgr::Get_Instance()->Render(hDC);
}

void CTetris::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();

	//CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
}
