#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static bool		Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY);
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);

	static void		Collision_MonsterRayCast(D3DXVECTOR3 NormalVec, D3DXVECTOR3 vPos, list<CObj*> _Sour);
	static void		Collision_Bullet_Monster(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Wall_Bullet(list<CObj*> _Dest, list<CObj*> _Sour);

};

