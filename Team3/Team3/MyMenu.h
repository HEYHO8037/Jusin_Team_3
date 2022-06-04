#pragma once

#include "Scene.h"
#include "Timer.h"

#include "MyButton.h"
class CMyMenu : public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CMyButton*		m_pGameStart[4];

	D3DXVECTOR3		m_vRightEye[2];
	D3DXVECTOR3		m_vLeftEye[2];

	D3DXVECTOR3		m_vOriginDir[2];
	D3DXVECTOR3		m_vDir[2];

	//D3DXVECTOR3		m_vPos[2];

	D3DXVECTOR3		m_vArrive;

	D3DXMATRIX		m_matWorld;

	bool			m_bClick;
	float			m_fSpeed;
};

