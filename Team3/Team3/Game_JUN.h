#pragma once
#include "Scene.h"
class CGame_JUN :
	public CScene
{
public:
	CGame_JUN();
	virtual ~CGame_JUN();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

