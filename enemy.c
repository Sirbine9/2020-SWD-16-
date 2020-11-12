#include "enemy.h"
#include "basic.h"
// 2020.11.08 작성자: 김현수

void SetEnemy(EnemyList* in)                                                // NPC의 속성을 설정하는 함수
{                                              
    int rep;
    int arrX, arrY;
    int posX, posY;
    for (int i = 0; i < in->numberofEnemy; i++) {
        do {
            posX = rand() % (GBOARD_WIDTH * 2) + 1 + GBOARD_ORIGIN_X;       // X값의 CONSOLE상의 좌표를 랜덤으로 할당 
            posY = rand() % (GBOARD_HEIGHT - 5) + 5 + GBOARD_ORIGIN_Y;      // Y값의 CONSOLE 상의 좌표를 랜덤으로 할당
            if (posX % 2 == 1)
                posX++;
            if (DetectCollision(posX, posY) == EMPTY && CheckEnemyPosition(posX, posY) == TRUE) // 할당한 값들이 충돌이 일어나지 않고 위치가 올바르면 break문을 이용하여 탈출  
                break;
        } while (1);
        in->enemy[i].x = posX;
        in->enemy[i].y = posY;


        rep = (rand() % 100) + 1;                                    // 난수 생성후 해당 난수의 값에 따라 형태 결정함.
        if (0 <= rep && rep < 15)                                    // SENTRY BOT 5%
        {                                  
            arrX = (in->enemy[i].x - GBOARD_ORIGIN_X) / 2;           // 현재 enemy의 게임판 내 x좌표 할당
            arrY = in->enemy[i].y - GBOARD_ORIGIN_Y;                 // 현재 enemy의 게임판 내 y좌표 할당
            in->enemy[i].type = 0;
            in->enemy[i].life = 2100000;                             // 현재 적이 존재한다. 
            gameBoardInfo[arrY][arrX] = BLOCK;                       // BLOCK은 막혀있다는 의미 
        }
        else if (16 <= rep && rep < 21)                              // MINE 15 %
        {                           
            arrX = (in->enemy[i].x - GBOARD_ORIGIN_X) / 2;
            arrY = in->enemy[i].y - GBOARD_ORIGIN_Y;
            in->enemy[i].type = 1;
            in->enemy[i].life = 1;
            gameBoardInfo[arrY][arrX] = NPC;                         // NPC은 닿으면 데미지를 입는다는 의미
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

int CheckEnemyPosition(int posX, int posY)                          // 적의 위치가 PC근처가 아니도록 조정하는 함수
{                        
    int arrX = (posX - GBOARD_ORIGIN_X) / 2;                        // 0 현재 블록의 게임판 내 x좌표
    int arrY = posY - GBOARD_ORIGIN_Y;
    if ((arrX >= (CurPcX - GBOARD_ORIGIN_X) / 2 - 1) && (arrX <= (CurPcX - GBOARD_ORIGIN_X) / 2 + 1)) {
        if (arrY >= (CurPcY - GBOARD_ORIGIN_Y) - 1 && arrY <= (CurPcY - GBOARD_ORIGIN_Y) + 1)
            return FALSE;                                           // PC근처의 좌표라면 FALSE return
    }
    return TRUE;                                                    // 아니라면 TRUE return
}

void MakeEnemy(EnemyList* in, int N)                                // 입력받은 수 만큼 Enemy구조체 배열을 할당하여 각각 적을 생성
{                              
    in->enemy = malloc(sizeof(Enemy) * N);
    in->numberofEnemy = N;
    in->numberofexistEnmey = 0;
    if (in->enemy == NULL) {
        printf("error\n");
        return NULL;
    }
}

void PrintEnemy(EnemyList* in)                                      // NPC를 그리는 함수
{                                    
    int posX, posY;
    for (int i = 0; i < in->numberofEnemy; i++)
    {
        if (in->enemy[i].life > 0)                                  // 적이 아직 존재한다면 그리고 적이 존재하지 않으면 그리지 않는다.
        {                                
            posX = in->enemy[i].x;
            posY = in->enemy[i].y;
            SetCurrentCursorPos(posX, posY);
            switch (in->enemy[i].type)
            {
                case 0: printf("▤"); break;
                case 1: printf("※"); break;
                case 2: printf("◇"); break;
            }
        }
    }
}

void DeleteEnemy(EnemyList* in)                                     // 메모리 free해주는 함수
{                                   
    if (in->enemy != NULL)
    {
        free(in->enemy);
        in->numberofEnemy = 0;
        in->enemy = NULL;
    }
    return;
}