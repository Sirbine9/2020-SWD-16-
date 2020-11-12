#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "define.h"
#include "basic.h"
#include "BulletMove.h"
#include "DetectCollision.h"
// 2020.11.08 작성자: 차명진

bullet *GetNode()								// 노드를 생성하는 함수
{			
	bullet *L = (bullet*)malloc(sizeof(bullet));
	L->next = NULL;
	L->prev = NULL;
	return L;
}

void AddLast(bullet *a)							// 리스트의 마지막에(트레일러 앞에) 노드를 추가하는 함수
{	
	bullet *b = BulletT->prev;
	b->next = a;
	a->prev = b;
	BulletT->prev = a;
	a->next = BulletT;
}

void RemoveBullet(bullet *a)					// 해당 노드를 삭제하는 함수
{		
	bullet *b = a->next; bullet*c = a->prev;
	c->next = b;
	b->prev = c;
	free(a);
}

void BulletPrint(EnemyList* in)					// 탄환을 출력하는 함수
{				
	bullet *cnt,*cn;
	for (cnt = BulletH->next; cnt != BulletT;)	// 탄환의 정보가 저장된 리스트를 탐색함
	{		
		RemoveCursor();
		if ((cnt->CurBulletX - cnt->TargetX * 2 != CurPcX) || (cnt->CurBulletY - cnt->TargetY != CurPcY))		// 탄환의 잔상 제거(조건문은 Pc 삭제 방지)
		{				
			SetCurrentCursorPos(cnt->CurBulletX - cnt->TargetX * 2, cnt->CurBulletY - cnt->TargetY);	printf("  ");
		}
		if (PcBulletDetectCollision(cnt->CurBulletX, cnt->CurBulletY,in)==FALSE)								// 탄환의 다음 이동시에 벽에 닿는다면 탄환 삭제 OR 탄환이 적 NPC에 닿는 다면 탄환 삭제
		{			
			cn = cnt->next;
			RemoveBullet(cnt);
			cnt = cn;
		}
		else
		{
			SetCurrentCursorPos(cnt->CurBulletX, cnt->CurBulletY);	printf("＠");				// 현재 탄환이 있어야 할 곳에 탄환 출력.
			cnt->CurBulletX = cnt->CurBulletX + cnt->TargetX * 2;								// 탄환의 경로 
			cnt->CurBulletY = cnt->CurBulletY + cnt->TargetY;
			cnt = cnt->next;
		}
	}
}

void BulletAdd()
{
	bullet *L = GetNode();
	L->TargetX = DirPcX;
	L->TargetY = DirPcY;
	L->CurBulletY = CurPcY + DirPcY;
	L->CurBulletX = CurPcX + DirPcX*2;
	int x = L->CurBulletX / 2;
	if (GBOARD_ORIGIN_X <= x && x <= GBOARD_WIDTH + GBOARD_ORIGIN_X && GBOARD_ORIGIN_Y + 2 <= L->CurBulletY && L->CurBulletY <= GBOARD_HEIGHT + GBOARD_ORIGIN_Y )
		AddLast(L);
	else
		free(L);
}