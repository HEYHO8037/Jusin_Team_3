#pragma once
#include "Scene.h"
class CGame_SEOK :
	public CScene
{
public:
	CGame_SEOK();
	virtual ~CGame_SEOK();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
private:
	int m_pHp;
	int m_mHp;

};

