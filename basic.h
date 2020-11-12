#pragma
void SetCurrentCursorPos(int x, int y);				// 콘솔창에서 현재 커서의 위치를 지정하는 함수
void RemoveCursor();								// 콘솔창에서 커서를 제거하는 함수
COORD GetCurrentCursorPos(void);					// 콘솔창에서 현재 커서의 위치를 리턴하는 함수
int DetectCollision(int posX, int posY);			// PC, NPC, PCBULLET, GameBoard 간의 충돌을 검사하는 함수
void Init();										// 프로그램을 시작하는 함수
void InitGame();									// WAVE를 시작하는 함수
void CallNextWave();								// 다음 WAVE를 호출하기 위한 함수
// void Render(int x, int y)						// 프로젝트의 BMP 리소스 파일을 콘솔창에 출력하는 함수