#pragma once
#include"define.h"

void DeleteEnemy(EnemyList* in);							// NPC�� free���ִ� �Լ�
void PrintEnemy(EnemyList* in);								// NPC�� ����ϴ� �Լ�
void SetEnemy(EnemyList* in);								// NPC�� �Ӽ��� �����ϴ� �Լ�
void MakeEnemy(EnemyList* in, int N);						// NPC�� ����� �Լ�
int CheckEnemyPosition(int posX, int posY);					// ���� ��ġ�� PC��ó�� �ƴϵ��� �����ϴ� �Լ�