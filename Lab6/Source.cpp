#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_star(int x, int y)
{
	gotoxy(x, y); setcolor(4, 0); printf("*");
}
void delete_star(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
void draw_ship(int x, int y)
{
	gotoxy(x, y); setcolor(2, 4); printf("<-0->");
}
void delete_ship(int x, int y)
{
	gotoxy(x, y); setcolor(0, 0); printf("      ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void draw_ammo(int x, int y)
{
	gotoxy(x += 2, --y); setcolor(2, 0); printf("^");
}
void delete_ammo(int x, int y)
{
	gotoxy(x += 2, --y); setcolor(0, 0); printf(" ");
}
int main()
{
	setcursor(0);
	int xShip = 38, xAmmo = 38, yShip = 20, yAmmo = 20, ammo = 0, xstar[20], ystar[20], countStar = 0, score = 0;
	draw_ship(xShip, yShip);
	char ch = '.';
	srand(time(NULL));
	do {
		gotoxy(90, 2); setcolor(10, 0); printf("Score = %d", score);
		for (; countStar < 20; countStar++)
		{
			if (countStar == 0) { xstar[countStar] = (rand() % 61) + 9;	ystar[countStar] = (rand() % 5) + 1; }
			for (int checkStars = 0; checkStars < countStar; checkStars++)
				do {
					xstar[countStar] = (rand() % 61) + 9;
					ystar[countStar] = (rand() % 4) + 1;
				} while (xstar[countStar] == xstar[checkStars] && ystar[countStar] == ystar[checkStars]);
				draw_star(xstar[countStar], ystar[countStar]);
		}
		if (ammo == 0) { xAmmo = xShip; }
		if (_kbhit()) {
			fflush(stdin);
			ch = _getch();
			if (ch == 'a') { delete_ship(xShip, yShip); draw_ship(--xShip, yShip); }
			if (ch == 's') { delete_ship(xShip, yShip); draw_ship(++xShip, yShip); }
			if (ch == ' ') { ammo = 1; }
		}
		if (ammo == 1 && yAmmo > 0) { delete_ammo(xAmmo, yAmmo); draw_ammo(xAmmo, --yAmmo); }
		if (cursor(xAmmo + 2, yAmmo - 2) == '*')
		{
			delete_ammo(xAmmo, yAmmo); delete_star(xAmmo + 2, yAmmo - 2); countStar--; score++; yAmmo = yShip; ammo = 0; Beep(2000, 100);
		}
		if (yAmmo == 1) { delete_ammo(xAmmo, yAmmo); ammo = 0; yAmmo = yShip; }
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
