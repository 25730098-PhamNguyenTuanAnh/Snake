#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
void gotoxy(int column, int line);
struct Point {
	int x, y;
};
class CONRAN {
public:
	struct Point A[100];
	int DoDai;
	CONRAN() {
		DoDai = 3;
		A[0].x = 12; A[0].y = 10;
		A[1].x = 11; A[1].y = 10;
		A[2].x = 10; A[2].y = 10;
	}
	void Ve() {
		for (int i = 0; i < DoDai; i++) {
			gotoxy(A[i].x, A[i].y);
			cout << "X";
		}
	}
	void DiChuyen(int Huong) {
		for (int i = DoDai - 1; i > 0;i--)
			A[i] = A[i - 1];
		if (Huong == 0) A[0].x = A[0].x + 1;
		if (Huong == 1) A[0].y = A[0].y + 1;
		if (Huong == 2) A[0].x = A[0].x - 1;
		if (Huong == 3) A[0].y = A[0].y - 1;

	}
};
#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

void VeKhung()
{
    for (int i = MINX; i <= MAXX; i++)
    {
        for (int j = MINY; j <= MAXY; j++)
        {
            if (i == MINX || i == MAXX || j == MINY || j == MAXY)
            {
                gotoxy(i, j);
                cout << "+";
            }
        }
    }
}
int main()
{
	CONRAN r;
	int Huong = 0;
	char t;

	while (1) {
		if (kbhit()) {
			t = getch();
			if (t == 'a') Huong = 2;
			if (t == 'w') Huong = 3;
			if (t == 'd') Huong = 0;
			if (t == 'x') Huong = 1;
		}
		system("cls");
		VeKhung();
		r.Ve();
		r.DiChuyen(Huong);

		bool hitBorder = r.A[0].x <= MINX || r.A[0].x >= MAXX
			|| r.A[0].y <= MINY || r.A[0].y >= MAXY;
		bool hitSelf = false;
		for (int i = 1; i < r.DoDai; i++) {
			if (r.A[0].x == r.A[i].x && r.A[0].y == r.A[i].y) {
				hitSelf = true;
				break;
			}
		}
		if (hitBorder || hitSelf) {
			gotoxy(MINX, MAXY + 2);
			cout << "Game Over! " << (hitBorder ? "Hit the wall." : "Hit yourself.")
				<< " Score: " << (r.DoDai - 3) << ". Press any key to exit.";
			getch();
			break;
		}

		Sleep(300);
	}

	return 0;
}


void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

