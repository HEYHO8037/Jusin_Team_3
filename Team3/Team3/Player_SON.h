#pragma once
#include "Obj.h"
class CPlayer_SON :
	public CObj
{
public:
	CPlayer_SON();
	CPlayer_SON(int _iIndex, TILETYPE _eTileType);
	~CPlayer_SON();

	const int& Get_DrawID_1(void) const { return m_iDrawID_1; }
	const int& Get_DrawID_2(void) const { return m_iDrawID_2; }
	const int& Get_DrawID_3(void) const { return m_iDrawID_3; }
	const bool& Get_New(void) const { return m_bNew; }

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void KeyInput(void);
	void UpdateDraw(void);

	bool m_bNew;

	int			m_iDrawID_1;
	int			m_iDrawID_2;
	int			m_iDrawID_3;

	D3DXVECTOR3		m_vPos_1;
	D3DXVECTOR3		m_vPos_2;
	D3DXVECTOR3		m_vPos_3;

	D3DXVECTOR3		m_vPosRen_1;
	D3DXVECTOR3		m_vPosRen_2;
	D3DXVECTOR3		m_vPosRen_3;

	TILETYPE m_eTileType;
};

