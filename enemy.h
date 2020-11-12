#pragma once
#include"define.h"

void DeleteEnemy(EnemyList* in);							// NPC를 free해주는 함수
void PrintEnemy(EnemyList* in);								// NPC를 출력하는 함수
void SetEnemy(EnemyList* in);								// NPC의 속성을 설정하는 함수
void MakeEnemy(EnemyList* in, int N);						// NPC를 만드는 함수
int CheckEnemyPosition(int posX, int posY);					// 적의 위치가 PC근처가 아니도록 조정하는 함수