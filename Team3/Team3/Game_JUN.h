#pragma once
#include "Scene.h"
class CGame_JUN :
	public CScene
{
public:
	CGame_JUN();
	virtual ~CGame_JUN();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

