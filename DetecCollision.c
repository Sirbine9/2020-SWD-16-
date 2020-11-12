#include"define.h"
#include"basic.h"
#include"Map.h"
// 2020.11.08 �ۼ���: ������

int NpcDetectCollision(Enemy* in) {             // ���� �����ϋ� �浹�˻縦 �ǽ��ϴ� �Լ�.
    if (in->life == 0)
        return FALSE;
    else {
        switch (DetectCollision(in->x, in->y))  // ���� ��ǥ�� �浹�˻縦 �ǽ�
        {
        case PCBULLET:
            in->life--;                         // ���� PCBullet�̶�� BUlLET�� �浹
            if (in->life == 0) {
                SetCurrentCursorPos(in->x, in->y);
                printf("  ");
            }
            return FALSE;                       // FALSE return
        case BLOCK: return FALSE;               // BLOCK�̶�� �� Ȥ�� bot�� �浹 FALSE����
        case EMPTY: return TRUE;
        case BULLET: return TRUE;
        case NPC: return FALSE;
        default:break;
        }
    }
}

int PcDetectCollision(int posX, int posY) {
    switch (DetectCollision(posX, posY))       // ���� ��ǥ�� �浹�˻縦 �ǽ�
    {
    case BULLET: life--;                       // ���� PC�� ���� źȯ�� �浹�� LIFE�� ����ϴ�.
        SetCurrentCursorPos(GBOARD_ORIGIN_X + 62, GBOARD_ORIGIN_Y + 2);
        printf("LIFE: ");
        TextColor(12);
        for (int i = 0; i < life; i++)
            printf("��");
        printf("  ");
        return TRUE; 
    case BLOCK: return FALSE;                   // BLOCK�̶�� �� Ȥ�� bot�� �浹 FALSE����
    case EMPTY: return TRUE;
    case NPC: life-- ;                          // ���� PC�� ���� �浹�� LIFE�� ����ϴ�. 
        SetCurrentCursorPos(GBOARD_ORIGIN_X + 62, GBOARD_ORIGIN_Y + 2); 
        printf("LIFE: ");
        TextColor(12);
        for (int i = 0; i < life; i++)
            printf("��");
        printf("  ");
        return FALSE;
    default: return TRUE; break;
    }
}

int NpcBulletDetectCollision(int posX, int posY) {
    switch (DetectCollision(posX, posY))        // BULLET�� ��ǥ�� �˻��ؼ�
    {
    case PC: life--; return FALSE;              // FALSE return
    case BLOCK: return FALSE;                   // BLOCK�̶�� �� Ȥ�� bot�� �浹 FALSE����
    case EMPTY: return TRUE;
    case NPC: return FALSE;
    default:break;
    }
}

int PcBulletDetectCollision(int posX, int posY, EnemyList* in) {
    int arrX, arrY;
    switch (DetectCollision(posX, posY))        //���� ��ǥ�� �浹�˻縦 �ǽ�
    {
    case NPC:
        for (int i = 0; i < in->numberofEnemy; i++) // PC�� źȯ�� ���� �´´ٸ� ��ǥ�� ���� �ش� ���� ã�Ƽ� ���� LIFE�� ��� ���� LIFE�� 0�� �Ǹ� �ش� ���� �����ǿ��� ����ϴ�.
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
    case BLOCK: return FALSE; // BLOCK�̶�� �� Ȥ�� bot�� �浹 FALSE����
    case EMPTY: return TRUE;
    default:break;
    }
}