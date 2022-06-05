#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "Player_SON.h"

#include "Monster_HO.h"
#include "Player_Ho.h"
#include "Bullet_HO.h"
#include "Wall_HO.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			Dest->Set_Damage();
			Sour->Set_Damage();
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY)
{
	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	// abs : 절대값을 구해주는 함수
	//float	fWidth = fabs(pSour->Get_Info().vPos.x - pDest->Get_Info().vPos.x);
	//float	fHeight = fabs(pSour->Get_Info().vPos.y - pDest->Get_Info().vPos.y);
	float	fWidth = fabs(pDest->Get_Info().vPos.x - pSour->Get_Info().vPos.x);
	float	fHeight = fabs(pDest->Get_Info().vPos.y - pSour->Get_Info().vPos.y);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

 	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

bool CCollisionMgr::Check_Sphere_JUN(D3DXVECTOR3 PlayerVec, float _fPRange, D3DXVECTOR3 TrapVec, float _fTRange)
{
	// abs : 절대값을 구해주는 함수
	//float	fWidth = fabs(pSour->Get_Info().vPos.x - pDest->Get_Info().vPos.x);
	//float	fHeight = fabs(pSour->Get_Info().vPos.y - pDest->Get_Info().vPos.y);
	float	fWidth = fabs(PlayerVec.x - TrapVec.x);
	float	fHeight = fabs(PlayerVec.y - TrapVec.y);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_fPRange + _fTRange);

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{ 
				Dest->Set_Damage();
				Sour->Set_Damage();
			}
		}
	}
}

void CCollisionMgr::Collision_MonsterRayCast(D3DXVECTOR3 NormalVec, D3DXVECTOR3 vPos, list<CObj*> _Sour)
{

	for (auto& Sour : _Sour)
	{
		float LeftX = Sour->Get_Info().vPos.x - 25.f;
		float RightX = Sour->Get_Info().vPos.x + 25.f;
		float TopY = Sour->Get_Info().vPos.y - 25.f;
		float BottomY = Sour->Get_Info().vPos.y + 25.f;

		for (int i = 0; i < 200; ++i)
		{
			vPos += NormalVec;

			if (vPos.x >= LeftX && vPos.x <= RightX
				&& vPos.y >= TopY && BottomY >= vPos.y)
			{
				dynamic_cast<CMonster_HO*>(Sour)->Set_bIsRender(true);
				break;
			}
			else
			{
				dynamic_cast<CMonster_HO*>(Sour)->Set_bIsRender(false);
			}
		}
	}
}

void CCollisionMgr::Collision_Bullet_Monster(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		D3DXVECTOR3* BulletPoint = dynamic_cast<CBullet_HO*>(Dest)->Get_Point();

		if (dynamic_cast<CBullet_HO*>(Dest)->Get_Type() == PLAYER_BULLET)
		{
			for (auto& Sour : _Sour)
			{
				D3DXVECTOR3* MonsterPoint = dynamic_cast<CMonster_HO*>(Sour)->Get_Point();

				if (MonsterPoint[0].x <= BulletPoint[0].x &&
					MonsterPoint[1].x >= BulletPoint[1].x &&
					MonsterPoint[0].y <= BulletPoint[0].y &&
					MonsterPoint[2].y >= BulletPoint[2].y)
				{
					Sour->Set_Dead(true);
					Dest->Set_Dead(true);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Wall_Bullet(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		D3DXVECTOR3* WallPoint = dynamic_cast<CWall_HO*>(Dest)->Get_Point();
		
		for (auto& Sour : _Sour)
		{
			D3DXVECTOR3* BulletPoint = dynamic_cast<CBullet_HO*>(Sour)->Get_Point();

			if (WallPoint[0].x <= BulletPoint[0].x &&
				WallPoint[1].x >= BulletPoint[1].x &&
				WallPoint[0].y <= BulletPoint[0].y &&
				WallPoint[2].y >= BulletPoint[2].y)
			{
				Sour->Set_Dead(true);
			}
		}
	}
}

void CCollisionMgr::Collision_Bullet_Player(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		D3DXVECTOR3* BulletPoint = dynamic_cast<CBullet_HO*>(Dest)->Get_Point();

		if (dynamic_cast<CBullet_HO*>(Dest)->Get_Type() == MONSTER_BULLET)
		{
			for (auto& Sour : _Sour)
			{
				D3DXVECTOR3* PlayerPoint = dynamic_cast<CPlayer_Ho*>(Sour)->Get_Point();

				if (PlayerPoint[0].x <= BulletPoint[0].x &&
					PlayerPoint[1].x >= BulletPoint[1].x &&
					PlayerPoint[0].y <= BulletPoint[0].y &&
					PlayerPoint[2].y >= BulletPoint[2].y)
				{
					Dest->Set_Dead(true);
					dynamic_cast<CPlayer_Ho*>(Sour)->Minus_HP();
				}
			}
		}
	}

}

