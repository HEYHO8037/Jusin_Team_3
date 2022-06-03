#include "stdafx.h"
#include "Player_JUN.h"

#include "KeyMgr.h"
/*
�׸� �׸���, �÷��̾�� ȸ�� ����? ��?
���ϴ�����
�׷� ȸ�� �Ƚ�Ű��?
�Ƴ� ȸ�� �־�, �ֳĸ� ������ �߸������� ���� �ö󰡰�
���� �ְ�, 
*/

/*
�÷��̾� ������ ������ 30�� ��ŭ ȸ���ϰ� �ٽ� false��
�÷��̾� ������ ������ -30�� ��ŭ ȸ���ϰ� �ٽ� false��

�̰� �÷��̾� ���� ���� �����־�� �ϴϱ�...
obj �Ŵ������� �Լ� ��������, -> ���� �÷��̾�� 30�� �Ѱ���
//�׸��� 1�� �Ѿ�� ������ 4�� �̵�

�׷� ���� �Ŵ����� �����ְ�
���� �Ŵ���
*/

//������ŭ ���� ������ �� ��ġ�� ���ư� �����
// �ٽ� ������ ���� �ٽ� ���ư� �����

// 


CPlayer_JUN::CPlayer_JUN()
{
	m_tInfo.vPos = { 400.f, 560.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_tInfo.vDir = { 0.f, -1.f, 0.f };

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	//������ �߽��� ����

	m_vBody[0] = { -20.f, -20.f, 0.f };
	m_vBody[1] = { 20.f, -20.f, 0.f };
	m_vBody[2] = { 20.f, 20.f, 0.f };
	m_vBody[3] = { -20.f, 20.f, 0.f };

	m_vBody[4] = { -10.f, 20.f, 0.f };
	m_vBody[5] = { -10.f, 40.f, 0.f };

	m_vBody[6] = { 10.f, 20.f, 0.f };
	m_vBody[7] = { 10.f, 40.f, 0.f };

	m_vBody[8] = { 0.f, -45.f, 0.f };

	m_fAngle = 0.f;

	for (int i = 0; i < 9; ++i)
	{
		m_vOriginBody[i] = m_vBody[i];
	}

	m_iDistance = 120;

	m_fObjAngle = 0.f;
}


CPlayer_JUN::~CPlayer_JUN()
{
}

void CPlayer_JUN::Initialize(void)
{
}

int CPlayer_JUN::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	Keyinput();

	/*if (m_fObjAngle != 0.f)
	{
		if (m_fObjAngle > 0.f)
		{
			m_fObjAngle -= 2.f;
			
			
		}
		else if (m_fObjAngle < 0.f)
		{
			m_fObjAngle += 2.f;
		}
	}*/

	if (m_tInfo.vPos.x != 400 - 120 + m_iDistance)
	{
		if (m_tInfo.vPos.x > 400 - 120 + m_iDistance)
		{
			m_tInfo.vPos.x -= 18.f;
			if (m_tInfo.vPos.x < 400 - 120 + m_iDistance)
			{
				m_tInfo.vPos.x = 400 - 120 + m_iDistance;
			}
		}
		else if (m_tInfo.vPos.x < 400 - 120 + m_iDistance)
		{
			m_tInfo.vPos.x += 18.f;
			if (m_tInfo.vPos.x > 400 - 120 + m_iDistance)
			{
				m_tInfo.vPos.x = 400 - 120 + m_iDistance;
			}
		}
	}

	



	D3DXMATRIX matScale, matRotz, matTrans;

	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotz);
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotz, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotz * matTrans;

	for (int i = 0; i < 9; ++i)
	{
		D3DXVec3TransformCoord(&m_vBody[i], &m_vOriginBody[i], &m_tInfo.matWorld);
	}

	//std::cout << m_tInfo.vPos.x << std::endl;
	//�ø�120��
	//120��ŭ ���� 3���� 15�� ȸ���ϰ� 
	// �ø� 120�� �Ѿ����...
	// int�� -30 �Ǵ� 30

	// -120 ~ 120 : 240���� �ΰ� 120���� �ȴ�
	// 

	return OBJ_NOEVENT;
}

void CPlayer_JUN::LateUpdate(void)
{
	//�� �Ⱥҷ� �̰�-> üũ�غ���
}

void CPlayer_JUN::Render(HDC hDC)
{	
	MoveToEx(hDC, (int)m_vBody[0].x, (int)m_vBody[0].y, nullptr);

	for (int i = 1; i < 5; ++i)
		LineTo(hDC, (int)m_vBody[i % 4].x, (int)m_vBody[i % 4].y);


	MoveToEx(hDC, (int)m_vBody[4].x, (int)m_vBody[4].y, nullptr);
	LineTo(hDC, (int)m_vBody[5].x, (int)m_vBody[5].y);

	MoveToEx(hDC, (int)m_vBody[6].x, (int)m_vBody[6].y, nullptr);
	LineTo(hDC, (int)m_vBody[7].x, (int)m_vBody[7].y);

	Ellipse(hDC, m_vBody[8].x - 25.f, m_vBody[8].y - 25.f, m_vBody[8].x + 25.f, m_vBody[8].y + 25.f);
}

void CPlayer_JUN::Release(void)
{
}

void CPlayer_JUN::Keyinput(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.vPos.x -= 5.f;
		m_iDistance -= 5;
		if (m_iDistance < 0)
		{
			m_bRight = false;
			m_bLeft = true;
			m_iDistance = 240 - m_iDistance;
			m_fObjAngle -= 45.f;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.vPos.x += 5.f;
		m_iDistance += 5;
		if (m_iDistance > 240)
		{
			m_bRight = true;
			m_bLeft = false;
			m_iDistance = 240 - m_iDistance;
			m_fObjAngle += 45.f;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		// ������ ���� Ŀ���� 
	}
}