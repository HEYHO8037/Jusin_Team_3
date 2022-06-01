#pragma once
#include "Obj.h"
class CUI : public CObj
{
public:
	CUI();
	~CUI();

	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

};
