#pragma once
#include "Obj.h"
class CBullet_Seok :
	public CObj
{
public:
	CBullet_Seok();
	virtual ~CBullet_Seok();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual		void	LateUpdate(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void    Set_Damage(void) override;
public:
	void Throw();
	void Line_Collision(void);
private:
	bool					m_bThrow;		// 던지기 상태 확인
	float					m_fThrowPower;	// 던지기 힘
	float					m_fThrowTime;	// 던지기 중 진행 시간
};
