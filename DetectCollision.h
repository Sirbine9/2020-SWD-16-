#pragma once
#include"define.h"

int NpcDetectCollision(Enemy* in);								// NPC�� �����϶� �浹�˻�
int PcDetectCollision(int posX, int posY);						// PC�� �����϶� �浹�˻�
int NpcBulletDetectCollision(int poxX, int posY);				// NPCBULLET�� �浹�˻� 
int PcBulletDetectCollision(int posX, int posY, EnemyList* in); // PCBULLET�� �浹�˻�