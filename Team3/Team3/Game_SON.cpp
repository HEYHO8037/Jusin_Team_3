#include "stdafx.h"
#include "Game_SON.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Player_SON.h"


CGame_SON::CGame_SON()
{
}


CGame_SON::~CGame_SON()
{
	Release();
}

void CGame_SON::Initialize(void)
{
	CTileMgr::Get_Instance()->Initialize();

	srand((unsigned int)time((nullptr)));

	int iRanDrop = rand() % 7 + 1;

	switch (iRanDrop)
	{
	case 1:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_A));
		break;

	case 2:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_B));
		break;

	case 3:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(25, TILE_C));
		break;

	case 4:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_D));
		break;

	case 5:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(25, TILE_E));
		break;

	case 6:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_F));
		break;

	case 7:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_G));
		break;
	}

	m_iTemp = 261;
}

void CGame_SON::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CGame_SON::LateUpdate(void)
{
	if (CObjMgr::Get_Instance()->Cheak_Player())
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Move() && dynamic_cast<CPlayer_SON*>(CObjMgr::Get_Instance()->Get_Player())->Get_New())
		{
			CTileMgr::Get_Instance()->Add_Tile(CObjMgr::Get_Instance()->Get_Player()->Get_DrawID());

			CTileMgr::Get_Instance()->Add_Tile(dynamic_cast<CPlayer_SON*>(CObjMgr::Get_Instance()->Get_Player())->Get_DrawID_1());

			CTileMgr::Get_Instance()->Add_Tile(dynamic_cast<CPlayer_SON*>(CObjMgr::Get_Instance()->Get_Player())->Get_DrawID_2());

			CTileMgr::Get_Instance()->Add_Tile(dynamic_cast<CPlayer_SON*>(CObjMgr::Get_Instance()->Get_Player())->Get_DrawID_3());

			CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
		}
	}
	else
	{
		if (CTileMgr::Get_Instance()->Get_Tile(45) || CTileMgr::Get_Instance()->Get_Tile(46) || CTileMgr::Get_Instance()->Get_Tile(66)) // 생성 위치에 블럭이 있으면 켜짐
		{
			// 게임 오버 메세지
			CTileMgr::Get_Instance()->SetStopDelete();

			if (0 < m_iTemp)
			{
				if (!CTileMgr::Get_Instance()->Get_Tile(m_iTemp))
				{
					CTileMgr::Get_Instance()->Add_Tile(m_iTemp);
					++m_iTemp;

					if (m_iTemp % TILEX == 11)
						m_iTemp -= TILEX + 10;
				}
				else
				{
					++m_iTemp;

					if (m_iTemp % TILEX == 11)
						m_iTemp -= TILEX + 10;
				}
			}
			else
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
				{
					CSceneMgr::Get_Instance()->Scene_Change(GAME_MENU);
					return;
				}
			}
		}
		else
		{
			srand((unsigned int)time((nullptr)));

			int iRanDrop = rand() % 7 + 1;

			switch (iRanDrop)
			{
			case 1:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_A));
				break;

			case 2:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_B));
				break;

			case 3:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(25, TILE_C));
				break;

			case 4:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_D));
				break;

			case 5:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(25, TILE_E));
				break;

			case 6:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_F));
				break;

			case 7:
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SON>::Create_Tetris(26, TILE_G));
				break;
			}
		}
	}
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->Late_Update();
}

void CGame_SON::Render(HDC hDC)
{
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	// 점수 UI
}

void CGame_SON::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
}
