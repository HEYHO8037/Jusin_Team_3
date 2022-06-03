#include "stdafx.h"
#include "Item_JUN.h"

#include "Player_JUN.h"
#include "ObjMgr.h"

//점점 커지면서 다가오고
// 일단은 회전 없이 커지면서 다가오는 부분 만들고
//회전 넣어서 공전도 같이 할 수 있도록!

CItem_JUN::CItem_JUN(const float& _fRandAngle)
{
	m_fAngle = D3DXToRadian(_fRandAngle);
}


CItem_JUN::~CItem_JUN()
{
}

void CItem_JUN::Initialize(void)
{
	
	m_vLocalPos[0] = { -15.f, -10.f,0.f };
	m_vLocalPos[1] = { 15.f, -10.f,0.f };
	m_vLocalPos[2] = { 15.f, 10.f,0.f };
	m_vLocalPos[3] = { -15.f, 10.f,0.f };

	m_vWorldTrans = { 400.f,300.f,0.f };
	m_vLocalCollision = { 0.f,0.f,0.f };

	m_vLocalRange = 10.f;
	
	for (int i = 0; i < 4; ++i)
	{
		m_vWorldPos[i] = m_vLocalPos[i];
	}
	
	m_fRatio_X = 1.f;
	m_fRatio_Y = 1.f;

	m_vWorldDir = {0.f,1.f,0.f};
	m_vLocalDir = m_vWorldDir;

	m_fSpeed = 3.f;

	m_fObjAngle = static_cast<CPlayer_JUN*>(CObjMgr::Get_Instance()->Get_Player())->Get_ObjAngle();
}

int CItem_JUN::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX _matScale, _matRotZ, _matTrans, _matRotA, _matTransA;

	D3DXMatrixIdentity(&_matScale);
	D3DXMatrixIdentity(&_matRotZ);
	D3DXMatrixIdentity(&_matTrans);
	D3DXMatrixIdentity(&_matRotA);
	D3DXMatrixIdentity(&_matTransA);

	m_fObjAngle_Player = static_cast<CPlayer_JUN*>(CObjMgr::Get_Instance()->Get_Player())->Get_ObjAngle();


	if (m_fObjAngle_Player != m_fObjAngle)
	{
		if (m_fObjAngle_Player > m_fObjAngle)
		{
			m_fObjAngle += 4.f;
			if (m_fObjAngle_Player < m_fObjAngle)
			{
				m_fObjAngle = m_fObjAngle_Player;
			}
		}
		else if (m_fObjAngle_Player < m_fObjAngle)
		{
			m_fObjAngle -= 4.f;
			if (m_fObjAngle_Player > m_fObjAngle)
			{
				m_fObjAngle = m_fObjAngle_Player;
			}
		}
	}

	std::cout << m_fObjAngle << " / " << m_fObjAngle_Player << std::endl;
	
	//D3DXMatrixRotationZ(&_matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixRotationZ(&_matRotA, m_fAngle + D3DXToRadian(m_fObjAngle));
	D3DXMatrixTranslation(&_matTrans, m_vWorldTrans.x - 400.f, m_vWorldTrans.y - 300.f, 0.f);
	D3DXMatrixTranslation(&_matTransA, 400.f, 300.f, 0.f);

	m_fRatio_X *= 1.015f;
	m_fRatio_Y *= 1.02f;

	m_vWorldRange = m_fRatio_X * m_vLocalRange;

	for (int i = 0; i < 4; ++i)
	{
		switch (i)
		{
		case 0:
			D3DXMatrixScaling(&_matScale, m_fRatio_X, m_fRatio_Y, 1.f);
			break;
		case 1:
			D3DXMatrixScaling(&_matScale, m_fRatio_X, m_fRatio_Y, 1.f);
			break;
		case 2:
			D3DXMatrixScaling(&_matScale, m_fRatio_X, 1.f, 1.f);
			break;
		case 3:
			D3DXMatrixScaling(&_matScale, m_fRatio_X, 1.f, 1.f);
			break;
		}

		m_tInfo.matWorld = _matScale * _matRotZ * _matTrans * _matRotA * _matTransA;
		
		D3DXVec3TransformCoord(&m_vWorldPos[i], &m_vLocalPos[i], &m_tInfo.matWorld);
		//D3DXVec3TransformNormal(&m_vWorldDir, &m_vLocalDir, &m_tInfo.matWorld);
	}

	//D3DXVec3TransformNormal(&m_vWorldDir, &m_vLocalDir, &m_tInfo.matWorld);

	//공전 하기 전 좌표를 가져오고, 그 이후에 연산
	D3DXMatrixTranslation(&_matTrans 
		, (m_vWorldPos[1].x + m_vWorldPos[0].x) / 2.f - 400.f
		, (m_vWorldPos[0].y + m_vWorldPos[3].y) / 2.f - 300.f
		, 0.f);
	D3DXMatrixTranslation(&_matTransA, 400.f, 300.f, 0.f);
	m_tInfo.matWorld = _matTrans * _matRotA * _matTransA;

	D3DXVec3TransformCoord(&m_vWorldCollision, &m_vLocalCollision, &m_tInfo.matWorld);

	m_vWorldTrans += m_vWorldDir * m_fSpeed;

	return OBJ_NOEVENT;
}

void CItem_JUN::LateUpdate(void)
{
	if (m_vWorldTrans.x < 0.f || m_vWorldTrans.x > 800.f)
		m_bDead = true;
	else if (m_vWorldTrans.y < 0.f || m_vWorldTrans.y > 600.f)
		m_bDead = true;
}

void CItem_JUN::Render(HDC hDC)
{
	MoveToEx(hDC, m_vWorldPos[0].x, m_vWorldPos[0].y, nullptr);

	for (int i = 1; i < 5; ++i)
	{
		LineTo(hDC, m_vWorldPos[i % 4].x, m_vWorldPos[i % 4].y);
	}
	Ellipse(hDC, m_vWorldCollision.x - m_vWorldRange, m_vWorldCollision.y - m_vWorldRange, m_vWorldCollision.x + m_vWorldRange, m_vWorldCollision.y + m_vWorldRange);
	
}

void CItem_JUN::Release(void)
{
}
