#include "stdafx.h"
#include "Player_SON.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"


CPlayer_SON::CPlayer_SON()
	: m_iDrawID_1(0)
	, m_iDrawID_2(0)
	, m_iDrawID_3(0)
	, m_eTileType(TILE_END)
{
	ZeroMemory(&m_vPos_1, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vPos_2, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vPos_3, sizeof(D3DXVECTOR3));

	ZeroMemory(&m_vPosRen_1, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vPosRen_2, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vPosRen_3, sizeof(D3DXVECTOR3));
}

CPlayer_SON::CPlayer_SON(int _iIndex, TILETYPE _eTileType)
{
	m_iDrawID = _iIndex;
	m_eTileType = _eTileType;
}

CPlayer_SON::~CPlayer_SON()
{
	Release();
}

void CPlayer_SON::Initialize(void)
{
	m_tInfo.vPos = { float((m_iDrawID % TILEX) * TILECX + (TILECX / 2)), float((m_iDrawID / TILEX) * TILECY + (TILECY / 2)), 0.f };

	switch (m_eTileType)
	{
	case TILE_A: // ㅗ
		m_vPos_1 = { -TILECX, 0.f, 0.f };
		m_vPos_2 = { TILECX, 0.f, 0.f };
		m_vPos_3 = { 0.f, -TILECY, 0.f };
		break;

	case TILE_B: // ㅣ
		m_vPos_1 = { 0.f, TILECY + TILECY, 0.f };
		m_vPos_2 = { 0.f, TILECY, 0.f };
		m_vPos_3 = { 0.f, -TILECY, 0.f };
		break;

	case TILE_C: // ㅁ
		m_vPos_1 = { TILECX, 0.f, 0.f };
		m_vPos_2 = { 0.f, -TILECY, 0.f };
		m_vPos_3 = { TILECX, -TILECY, 0.f };
		break;

	case TILE_D: // 좌
		m_vPos_1 = { -TILECX, -TILECY, 0.f };
		m_vPos_2 = { -TILECX, 0.f, 0.f };
		m_vPos_3 = { 0.f, TILECY, 0.f };
		break;

	case TILE_E: // 우
		m_vPos_1 = { TILECX, -TILECY, 0.f };
		m_vPos_2 = { TILECX, 0.f, 0.f };
		m_vPos_3 = { 0.f, TILECY, 0.f };
		break;

	case TILE_F: // ㄴ
		m_vPos_1 = { -TILECX, 0.f, 0.f };
		m_vPos_2 = { TILECX, 0.f, 0.f };
		m_vPos_3 = { -TILECX, -TILECY, 0.f };
		break;

	case TILE_G: // ㄴ 좌우반전
		m_vPos_1 = { -TILECX, 0.f, 0.f };
		m_vPos_2 = { TILECX, 0.f, 0.f };
		m_vPos_3 = { TILECX, -TILECY, 0.f };
		break;
	}

	UpdateDraw();

	m_iLocationIndex = m_iDrawID;
	m_bNew = false;
}

int CPlayer_SON::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (!m_bStopMove || !m_bNew)
	{
		UpdateDraw();
	}

	if (m_bStopMove)
	{
		if (m_dwDownTime + 1000 < GetTickCount())
		{
			if ((!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID + TILEX))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_1 + TILEX))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_2 + TILEX))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_3 + TILEX)))
			{
				m_bStopMove = false;
			}
			else
			{
				m_bNew = true;
			}
		}
	}

	return OBJ_NOEVENT;
}

void CPlayer_SON::LateUpdate(void)
{
	if (!m_bStopMove || !m_bNew)
	{
		if ((m_iDrawID % TILEX < 1) || (m_iDrawID_1 % TILEX < 1) || (m_iDrawID_2 % TILEX < 1) || (m_iDrawID_3 % TILEX < 1))
		{
			m_iDrawID += 1;
		}
		else if ((m_iDrawID % TILEX > 10) || (m_iDrawID_1 % TILEX > 10) || (m_iDrawID_2 % TILEX > 10) || (m_iDrawID_3 % TILEX > 10))
		{
			m_iDrawID -= 1;
		}
		else if ((CTileMgr::Get_Instance()->Get_Tile(m_iDrawID))
			|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_1))
			|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_2))
			|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_3)))
			m_iDrawID -= TILEX;

		if (!m_bStopMove)
		{
			if ((m_iDrawID % TILEX > 0) && (m_iDrawID_1 % TILEX > 0) && (m_iDrawID_2 % TILEX > 0) && (m_iDrawID_3 % TILEX > 0))
				if ((m_iDrawID % TILEX < 11) && (m_iDrawID_1 % TILEX < 11) && (m_iDrawID_2 % TILEX < 11) && (m_iDrawID_3 % TILEX < 11))
					if ((CTileMgr::Get_Instance()->Get_Tile(m_iDrawID + TILEX))
						|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_1 + TILEX))
						|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_2 + TILEX))
						|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_3 + TILEX)))
					{
						m_dwDownTime = GetTickCount();
						m_bStopMove = true;
						return;
					}

			if (m_dwDownTime + 2300 < GetTickCount())
			{
				m_iDrawID += TILEX;
				m_dwDownTime = GetTickCount();
			}
		}

		KeyInput();
	}
}

void CPlayer_SON::Render(HDC hDC)
{
	Rectangle(hDC, (int)m_tInfo.vPos.x - (TILECX / 2), (int)m_tInfo.vPos.y - (TILECY / 2), (int)m_tInfo.vPos.x + (TILECX / 2), (int)m_tInfo.vPos.y + (TILECY / 2));
	Rectangle(hDC, (int)m_vPosRen_1.x - (TILECX / 2) + 1, (int)m_vPosRen_1.y - (TILECY / 2) + 1, (int)m_vPosRen_1.x + (TILECX / 2) + 1, (int)m_vPosRen_1.y + (TILECY / 2) + 1);
	Rectangle(hDC, (int)m_vPosRen_2.x - (TILECX / 2) + 1, (int)m_vPosRen_2.y - (TILECY / 2) + 1, (int)m_vPosRen_2.x + (TILECX / 2) + 1, (int)m_vPosRen_2.y + (TILECY / 2) + 1);
	Rectangle(hDC, (int)m_vPosRen_3.x - (TILECX / 2) + 1, (int)m_vPosRen_3.y - (TILECY / 2) + 1, (int)m_vPosRen_3.x + (TILECX / 2) + 1, (int)m_vPosRen_3.y + (TILECY / 2) + 1);
}

void CPlayer_SON::Release(void)
{
	/*std::cout << m_bStopMove << std::endl;
	std::cout << std::endl;
	std::cout << m_bNew << std::endl;
	std::cout << std::endl;*/
}

void CPlayer_SON::KeyInput(void)
{
	// 좌
	if ((m_iDrawID % TILEX > 1) && (m_iDrawID_1 % TILEX > 1) && (m_iDrawID_2 % TILEX > 1) && (m_iDrawID_3 % TILEX > 1))
	{
		if ((!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID - 1))
			&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_1 - 1))
			&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_2 - 1))
			&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_3 - 1)))
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
			{
				m_iDrawID -= 1;
			}
	}

	// 우
	if ((m_iDrawID % TILEX < 10) && (m_iDrawID_1 % TILEX < 10) && (m_iDrawID_2 % TILEX < 10) && (m_iDrawID_3 % TILEX < 10))
	{
		if((TILEX * TILEY) >= m_iDrawID && (TILEX * TILEY) >= m_iDrawID_1 && (TILEX * TILEY) >= m_iDrawID_2 && (TILEX * TILEY) >= m_iDrawID_3)
			if ((!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID + 1))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_1 + 1))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_2 + 1))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_3 + 1)))
				if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
				{
					m_iDrawID += 1;
				}
	}

	// 하
	if ((m_iDrawID % TILEX > 0) && (m_iDrawID_1 % TILEX > 0) && (m_iDrawID_2 % TILEX > 0) && (m_iDrawID_3 % TILEX > 0))
	{
		if ((m_iDrawID % TILEX < 11) && (m_iDrawID_1 % TILEX < 11) && (m_iDrawID_2 % TILEX < 11) && (m_iDrawID_3 % TILEX < 11))
		{
			if ((!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID + TILEX))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_1 + TILEX))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_2 + TILEX))
				&& (!CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_3 + TILEX)))
				if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				{
					m_iDrawID += TILEX;
				}
		}
	}

	// 회전
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		// ㅁ일 경우 리턴
		if (TILE_C == m_eTileType)
		{
			return;
		}

		if (260 < m_iDrawID)
		{
			m_fAngle += D3DXToRadian(90.f);
			if (D3DXToRadian(360.f) == m_fAngle)
			{
				m_fAngle = 0.f;
			}

			UpdateDraw();

			if ((CTileMgr::Get_Instance()->Get_Tile(m_iDrawID))
				|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_1))
				|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_2))
				|| (CTileMgr::Get_Instance()->Get_Tile(m_iDrawID_3)))
				m_iDrawID -= TILEX;
		}
		else
		{
			m_fAngle += D3DXToRadian(90.f);
			if (D3DXToRadian(360.f) == m_fAngle)
			{
				m_fAngle = 0.f;
			}
		}
	}

	if (m_iLocationIndex != m_iDrawID)
	{
		m_tInfo.vPos.x = float((m_iDrawID % TILEX) * TILECX + (TILECX / 2));
		m_tInfo.vPos.y = float((m_iDrawID / TILEX) * TILECY + (TILECY / 2));

		m_iLocationIndex = m_iDrawID;
	}
}

void CPlayer_SON::UpdateDraw(void)
{
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	D3DXVec3TransformCoord(&m_vPosRen_1, &m_vPos_1, &m_tInfo.matWorld);
	D3DXVec3TransformCoord(&m_vPosRen_2, &m_vPos_2, &m_tInfo.matWorld);
	D3DXVec3TransformCoord(&m_vPosRen_3, &m_vPos_3, &m_tInfo.matWorld);
	m_iDrawID_1 = ((m_vPosRen_1.x - (TILECX / 2)) / TILECX) + (((m_vPosRen_1.y - (TILECY / 2)) / TILECY) * TILEX) + 1;
	m_iDrawID_2 = ((m_vPosRen_2.x - (TILECX / 2)) / TILECX) + (((m_vPosRen_2.y - (TILECY / 2)) / TILECY) * TILEX) + 1;
	m_iDrawID_3 = ((m_vPosRen_3.x - (TILECX / 2)) / TILECX) + (((m_vPosRen_3.y - (TILECY / 2)) / TILECY) * TILEX) + 1;
}
