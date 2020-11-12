#include"define.h"
#include"basic.h"
#include"Map.h"
// 2020.11.08 작성자: 김현수

int NpcDetectCollision(Enemy* in) {             // 적이 움직일떄 충돌검사를 실시하는 함수.
    if (in->life == 0)
        return FALSE;
    else {
        switch (DetectCollision(in->x, in->y))  // 적의 좌표에 충돌검사를 실시
        {
        case PCBULLET:
            in->life--;                         // 만약 PCBullet이라면 BUlLET과 충돌
            if (in->life == 0) {
                SetCurrentCursorPos(in->x, in->y);
                printf("  ");
            }
            return FALSE;                       // FALSE return
        case BLOCK: return FALSE;               // BLOCK이라면 벽 혹은 bot과 충돌 FALSE리턴
        case EMPTY: return TRUE;
        case BULLET: return TRUE;
        case NPC: return FALSE;
        default:break;
        }
    }
}

int PcDetectCollision(int posX, int posY) {
    switch (DetectCollision(posX, posY))       // 적의 좌표에 충돌검사를 실시
    {
    case BULLET: life--;                       // 만약 PC가 적의 탄환과 충돌시 LIFE를 깎습니다.
        SetCurrentCursorPos(GBOARD_ORIGIN_X + 62, GBOARD_ORIGIN_Y + 2);
        printf("LIFE: ");
        TextColor(12);
        for (int i = 0; i < life; i++)
            printf("♥");
        printf("  ");
        return TRUE; 
    case BLOCK: return FALSE;                   // BLOCK이라면 벽 혹은 bot과 충돌 FALSE리턴
    case EMPTY: return TRUE;
    case NPC: life-- ;                          // 만약 PC가 적과 충돌시 LIFE를 깎습니다. 
        SetCurrentCursorPos(GBOARD_ORIGIN_X + 62, GBOARD_ORIGIN_Y + 2); 
        printf("LIFE: ");
        TextColor(12);
        for (int i = 0; i < life; i++)
            printf("♥");
        printf("  ");
        return FALSE;
    default: return TRUE; break;
    }
}

int NpcBulletDetectCollision(int posX, int posY) {
    switch (DetectCollision(posX, posY))        // BULLET의 좌표를 검사해서
    {
    case PC: life--; return FALSE;              // FALSE return
    case BLOCK: return FALSE;                   // BLOCK이라면 벽 혹은 bot과 충돌 FALSE리턴
    case EMPTY: return TRUE;
    case NPC: return FALSE;
    default:break;
    }
}

int PcBulletDetectCollision(int posX, int posY, EnemyList* in) {
    int arrX, arrY;
    switch (DetectCollision(posX, posY))        //적의 좌표에 충돌검사를 실시
    {
    case NPC:
        for (int i = 0; i < in->numberofEnemy; i++) // PC의 탄환이 적과 맞는다면 좌표를 통해 해당 적을 찾아서 적의 LIFE를 깎고 만약 LIFE가 0이 되면 해당 적을 게임판에서 지웁니다.
        { 
            if (in->enemy[i].life <= 0)
                continue;
            else {
                if ((posX == in->enemy[i].x) && (posY == in->enemy[i].y)) 
                    in->enemy[i].life--;
                if (in->enemy[i].life <= 0)
                {
                    SetCurrentCursorPos(in->enemy[i].x, in->enemy[i].y);
                    in->numberofexistEnmey--;
                    int arrX = (in->enemy[i].x - GBOARD_ORIGIN_X) / 2; 
                    int arrY = in->enemy[i].y - GBOARD_ORIGIN_Y; 
                    gameBoardInfo[arrY][arrX] = EMPTY;
                    printf("  "); 
                }
            }
        }
        return FALSE;
    case BLOCK: return FALSE; // BLOCK이라면 벽 혹은 bot과 충돌 FALSE리턴
    case EMPTY: return TRUE;
    default:break;
    }
}