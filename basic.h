#pragma
void SetCurrentCursorPos(int x, int y);				// �ܼ�â���� ���� Ŀ���� ��ġ�� �����ϴ� �Լ�
void RemoveCursor();								// �ܼ�â���� Ŀ���� �����ϴ� �Լ�
COORD GetCurrentCursorPos(void);					// �ܼ�â���� ���� Ŀ���� ��ġ�� �����ϴ� �Լ�
int DetectCollision(int posX, int posY);			// PC, NPC, PCBULLET, GameBoard ���� �浹�� �˻��ϴ� �Լ�
void Init();										// ���α׷��� �����ϴ� �Լ�
void InitGame();									// WAVE�� �����ϴ� �Լ�
void CallNextWave();								// ���� WAVE�� ȣ���ϱ� ���� �Լ�
// void Render(int x, int y)						// ������Ʈ�� BMP ���ҽ� ������ �ܼ�â�� ����ϴ� �Լ�