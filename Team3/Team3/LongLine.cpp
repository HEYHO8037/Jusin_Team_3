#include "stdafx.h"
#include "LongLine.h"
#include "KeyMgr.h"

#include "ObjMgr.h"

#include "Player_JUN.h"


CLongLine::CLongLine()
{
	m_vPoint[0] = { -450.f, 0.f,0.f };
	m_vPoint[1] = { 450.f, 0.f,0.f };
	for (int i = 0; i < 2; ++i)
	{
		m_vLocalPoint[i] = m_vPoint[i];
	}

	//6번 돌려서
	//pos 있어야하는데 그건 딱 중앙
	// 거기 중점으로 딱 반이 0,0이도록

	m_tInfo.vPos = { 400.f,300.f,0.f };

	m_fAngle_6 = D3DXToRadian(45.f);
	m_fAngle = 22.5f;

	m_fAngle_Coc = 22.5;

	m_fObjAngle = 0;
}

CLongLine::CLongLine(const D3DXVECTOR3 * _vPoint)
{

}


CLongLine::~CLongLine()
{
}

void CLongLine::Initialize(void)
{

}

void CLongLine::Update(void)
{
	/*D3DXMATRIX matScale, matRotz, matTrans;

	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotz);
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotz, D3DXToRadian(50.f +
		static_cast<CPlayer_JUN*>(CObjMgr::Get_Instance()->Get_Player())->Get_ObjAngle()
	));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	

	m_tInfo.matWorld = matScale * matRotz * matTrans;

	for (int i = 0 ; i < 2 ; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vLocalPoint[i], &m_tInfo.matWorld);
	

	Keyinput();*/
}

void CLongLine::LateUpdate(void)
{
}

void CLongLine::Render(HDC hDC)
{
	HPEN hpen;
	HPEN hpenOld;

	hpen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));   // 선 스타일, 굵기, 색상
	hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);   // 펜 선택
	

	for (int i = 0; i < 4; ++i)
	{
		D3DXMATRIX matScale, matRotz, matTrans;

		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matRotz);
		D3DXMatrixIdentity(&matTrans);

		m_fObjAngle_Player = static_cast<CPlayer_JUN*>(CObjMgr::Get_Instance()->Get_Player())->Get_ObjAngle();

		if (m_fObjAngle_Player != m_fObjAngle)
		{
			if (m_fObjAngle_Player > m_fObjAngle)
			{
				m_fObjAngle += 1.f;
				if (m_fObjAngle_Player < m_fObjAngle)
				{
					m_fObjAngle = m_fObjAngle_Player;
				}
			}
			else if (m_fObjAngle_Player < m_fObjAngle)
			{
				m_fObjAngle -= 1.f;
				if (m_fObjAngle_Player > m_fObjAngle)
				{
					m_fObjAngle = m_fObjAngle_Player;
				}
			}
		}

		//std::cout << m_fObjAngle_Player << " " << m_fObjAngle << std::endl;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matRotz, m_fAngle_6 * i + D3DXToRadian(m_fAngle + m_fObjAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matScale * matRotz * matTrans;

		for (int i = 0; i < 2; ++i)
			D3DXVec3TransformCoord(&m_vPoint[i], &m_vLocalPoint[i], &m_tInfo.matWorld);

		MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);
		LineTo(hDC, m_vPoint[1].x, m_vPoint[1].y);
	}
	hpen = (HPEN)SelectObject(hDC, hpenOld);   // 기존의 펜 다시 선택
	DeleteObject(hpen);   // 생성한 펜 삭제
}

void CLongLine::Release(void)
{
}
void CLongLine::Keyinput(void)
{
	/*if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_fAngle -= 1.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_fAngle += 1.f;
	}*/
}