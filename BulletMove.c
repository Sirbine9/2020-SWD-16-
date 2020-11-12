#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "define.h"
#include "basic.h"
#include "BulletMove.h"
#include "DetectCollision.h"
// 2020.11.08 �ۼ���: ������

bullet *GetNode()								// ��带 �����ϴ� �Լ�
{			
	bullet *L = (bullet*)malloc(sizeof(bullet));
	L->next = NULL;
	L->prev = NULL;
	return L;
}

void AddLast(bullet *a)							// ����Ʈ�� ��������(Ʈ���Ϸ� �տ�) ��带 �߰��ϴ� �Լ�
{	
	bullet *b = BulletT->prev;
	b->next = a;
	a->prev = b;
	BulletT->prev = a;
	a->next = BulletT;
}

void RemoveBullet(bullet *a)					// �ش� ��带 �����ϴ� �Լ�
{		
	bullet *b = a->next; bullet*c = a->prev;
	c->next = b;
	b->prev = c;
	free(a);
}

void BulletPrint(EnemyList* in)					// źȯ�� ����ϴ� �Լ�
{				
	bullet *cnt,*cn;
	for (cnt = BulletH->next; cnt != BulletT;)	// źȯ�� ������ ����� ����Ʈ�� Ž����
	{		
		RemoveCursor();
		if ((cnt->CurBulletX - cnt->TargetX * 2 != CurPcX) || (cnt->CurBulletY - cnt->TargetY != CurPcY))		// źȯ�� �ܻ� ����(���ǹ��� Pc ���� ����)
		{				
			SetCurrentCursorPos(cnt->CurBulletX - cnt->TargetX * 2, cnt->CurBulletY - cnt->TargetY);	printf("  ");
		}
		if (PcBulletDetectCollision(cnt->CurBulletX, cnt->CurBulletY,in)==FALSE)								// źȯ�� ���� �̵��ÿ� ���� ��´ٸ� źȯ ���� OR źȯ�� �� NPC�� ��� �ٸ� źȯ ����
		{			
			cn = cnt->next;
			RemoveBullet(cnt);
			cnt = cn;
		}
		else
		{
			SetCurrentCursorPos(cnt->CurBulletX, cnt->CurBulletY);	printf("��");				// ���� źȯ�� �־�� �� ���� źȯ ���.
			cnt->CurBulletX = cnt->CurBulletX + cnt->TargetX * 2;								// źȯ�� ��� 
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