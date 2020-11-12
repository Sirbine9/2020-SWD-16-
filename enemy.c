#include "enemy.h"
#include "basic.h"
// 2020.11.08 �ۼ���: ������

void SetEnemy(EnemyList* in)                                                // NPC�� �Ӽ��� �����ϴ� �Լ�
{                                              
    int rep;
    int arrX, arrY;
    int posX, posY;
    for (int i = 0; i < in->numberofEnemy; i++) {
        do {
            posX = rand() % (GBOARD_WIDTH * 2) + 1 + GBOARD_ORIGIN_X;       // X���� CONSOLE���� ��ǥ�� �������� �Ҵ� 
            posY = rand() % (GBOARD_HEIGHT - 5) + 5 + GBOARD_ORIGIN_Y;      // Y���� CONSOLE ���� ��ǥ�� �������� �Ҵ�
            if (posX % 2 == 1)
                posX++;
            if (DetectCollision(posX, posY) == EMPTY && CheckEnemyPosition(posX, posY) == TRUE) // �Ҵ��� ������ �浹�� �Ͼ�� �ʰ� ��ġ�� �ùٸ��� break���� �̿��Ͽ� Ż��  
                break;
        } while (1);
        in->enemy[i].x = posX;
        in->enemy[i].y = posY;


        rep = (rand() % 100) + 1;                                    // ���� ������ �ش� ������ ���� ���� ���� ������.
        if (0 <= rep && rep < 15)                                    // SENTRY BOT 5%
        {                                  
            arrX = (in->enemy[i].x - GBOARD_ORIGIN_X) / 2;           // ���� enemy�� ������ �� x��ǥ �Ҵ�
            arrY = in->enemy[i].y - GBOARD_ORIGIN_Y;                 // ���� enemy�� ������ �� y��ǥ �Ҵ�
            in->enemy[i].type = 0;
            in->enemy[i].life = 2100000;                             // ���� ���� �����Ѵ�. 
            gameBoardInfo[arrY][arrX] = BLOCK;                       // BLOCK�� �����ִٴ� �ǹ� 
        }
        else if (16 <= rep && rep < 21)                              // MINE 15 %
        {                           
            arrX = (in->enemy[i].x - GBOARD_ORIGIN_X) / 2;
            arrY = in->enemy[i].y - GBOARD_ORIGIN_Y;
            in->enemy[i].type = 1;
            in->enemy[i].life = 1;
            gameBoardInfo[arrY][arrX] = NPC;                         // NPC�� ������ �������� �Դ´ٴ� �ǹ�
        }
        else if (21 <= rep && rep < 100)                             // HANDY 80%
        {                           
            arrX = (in->enemy[i].x - GBOARD_ORIGIN_X) / 2;
            arrY = in->enemy[i].y - GBOARD_ORIGIN_Y;
            in->enemy[i].type = 2;
            in->enemy[i].life = 1;
            in->numberofexistEnmey++;
            gameBoardInfo[arrY][arrX] = NPC;
        }
    }
}

int CheckEnemyPosition(int posX, int posY)                          // ���� ��ġ�� PC��ó�� �ƴϵ��� �����ϴ� �Լ�
{                        
    int arrX = (posX - GBOARD_ORIGIN_X) / 2;                        // 0 ���� ����� ������ �� x��ǥ
    int arrY = posY - GBOARD_ORIGIN_Y;
    if ((arrX >= (CurPcX - GBOARD_ORIGIN_X) / 2 - 1) && (arrX <= (CurPcX - GBOARD_ORIGIN_X) / 2 + 1)) {
        if (arrY >= (CurPcY - GBOARD_ORIGIN_Y) - 1 && arrY <= (CurPcY - GBOARD_ORIGIN_Y) + 1)
            return FALSE;                                           // PC��ó�� ��ǥ��� FALSE return
    }
    return TRUE;                                                    // �ƴ϶�� TRUE return
}

void MakeEnemy(EnemyList* in, int N)                                // �Է¹��� �� ��ŭ Enemy����ü �迭�� �Ҵ��Ͽ� ���� ���� ����
{                              
    in->enemy = malloc(sizeof(Enemy) * N);
    in->numberofEnemy = N;
    in->numberofexistEnmey = 0;
    if (in->enemy == NULL) {
        printf("error\n");
        return NULL;
    }
}

void PrintEnemy(EnemyList* in)                                      // NPC�� �׸��� �Լ�
{                                    
    int posX, posY;
    for (int i = 0; i < in->numberofEnemy; i++)
    {
        if (in->enemy[i].life > 0)                                  // ���� ���� �����Ѵٸ� �׸��� ���� �������� ������ �׸��� �ʴ´�.
        {                                
            posX = in->enemy[i].x;
            posY = in->enemy[i].y;
            SetCurrentCursorPos(posX, posY);
            switch (in->enemy[i].type)
            {
                case 0: printf("��"); break;
                case 1: printf("��"); break;
                case 2: printf("��"); break;
            }
        }
    }
}

void DeleteEnemy(EnemyList* in)                                     // �޸� free���ִ� �Լ�
{                                   
    if (in->enemy != NULL)
    {
        free(in->enemy);
        in->numberofEnemy = 0;
        in->enemy = NULL;
    }
    return;
}