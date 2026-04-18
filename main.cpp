#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

constexpr int MAX_LENGTH = (MAXX - MINX - 1) * (MAXY - MINY - 1);

using namespace std;
void gotoxy(int column, int line);
struct Point {
	int x, y;
};
class CONRAN {
public:
	struct Point A[MAX_LENGTH];
	int DoDai;
	CONRAN() {
		DoDai = 3;
		A[0].x = 12; A[0].y = 10;
		A[1].x = 11; A[1].y = 10;
		A[2].x = 10; A[2].y = 10;
	}
	void Ve(Point Qua, int Huong) {
		for (int i = 1; i < DoDai; i++) {
			gotoxy(A[i].x, A[i].y);
			cout << "X";
		}
		gotoxy(A[0].x, A[0].y);
		if (Huong == 0) cout << ">";
		else if (Huong == 1) cout << "v";
		else if (Huong == 2) cout << "<";
		else cout << "^";
		if (Qua.x >= 0) {
			gotoxy(Qua.x, Qua.y);
			cout << "*";
		}
	}
	void DiChuyen(int Huong, Point &Qua) {
		Point newHead = A[0];
		if (Huong == 0) newHead.x += 1;
		if (Huong == 1) newHead.y += 1;
		if (Huong == 2) newHead.x -= 1;
		if (Huong == 3) newHead.y -= 1;

		bool eating = newHead.x == Qua.x && newHead.y == Qua.y;
		if (eating && DoDai < MAX_LENGTH) DoDai++;

		for (int i = DoDai - 1; i > 0; i--)
			A[i] = A[i - 1];
		A[0] = newHead;

		if (eating) {
			if (DoDai < MAX_LENGTH) Qua = SpawnFood();
			else { Qua.x = -1; Qua.y = -1; }
		}
	}

	Point SpawnFood() {
		Point p;
		bool onSnake;
		do {
			p.x = rand() % (MAXX - MINX - 1) + MINX + 1;
			p.y = rand() % (MAXY - MINY - 1) + MINY + 1;
			onSnake = false;
			for (int i = 0; i < DoDai; i++) {
				if (A[i].x == p.x && A[i].y == p.y) {
					onSnake = true;
					break;
				}
			}
		} while (onSnake);
		return p;
	}
};
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
	Point Qua;
	srand((int)time(0));
	Qua = r.SpawnFood();
	while (1) {
		if (kbhit()) {
			t = getch();
			int newHuong = -1;
			if (t == 'a') newHuong = 2;
			else if (t == 'w') newHuong = 3;
			else if (t == 'd') newHuong = 0;
			else if (t == 'x') newHuong = 1;
			bool is180 = (newHuong ^ Huong) == 2;
			if (newHuong != -1 && !is180) Huong = newHuong;
		}
		system("cls");
		VeKhung();
		r.Ve(Qua, Huong);
		gotoxy(MINX, MAXY + 1);
		cout << "Score: " << (r.DoDai - 3);
		r.DiChuyen(Huong, Qua);

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
