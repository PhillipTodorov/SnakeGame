#include <iostream>
#include <conio.h>
#include <windows.h>
#include <deque>

//gameLevel()
//##########
//drawing the boundaries of the game level
int i; // verical axis
int i_max; // vertical axis max
int j; // horizontal axis
int j_max; // horizontal axis max 
//##########


int x, y; //Snake location
int fruitX, fruitY, score;
enum class eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
bool gameOver;
int k; // used to iterate through tail vectors below
std::deque<int>tailX;
std::deque<int>tailY;


void Setup() {
	i_max = 25;
	j_max = 25;
	dir = eDirection::STOP;
	x = 3;
	y = 4;
	fruitX = rand() % (i_max - 2) + 1;
	fruitY = rand() % (j_max - 2) + 1;
	gameOver = false;
	score = 1;
	k = 625;
	tailX.push_front(x);
	tailY.push_front(y);

}

void SnakeCollisionLogic()
{
	// wall collision case
	if (x == 0 || x == i_max || y == 0 || y == j_max) {
		gameOver = true;
	}


}

void PrintSnakeForTroubleshooting() {
	std::deque<int>tailX_print = tailX;
	std::deque<int>tailY_print = tailY;

	std::cout << "Snake head: " << x << " " << y << "\n";

	std::cout << "Tail x coords:"; 
	while (!tailX_print.empty()) {
		std::cout << tailX_print.front() << " ";
		tailX_print.pop_front();
	}
	std::cout << '\n' << "Tail y coords:";
	while (!tailY_print.empty()) {
		std::cout << tailY_print.front() << " ";
		tailY_print.pop_front();
	}
		
}

void AddHeadPositionToTailArray()
{
	tailX.push_back(i);
	tailY.push_back(j);

	while (tailX.size() > unsigned(score)) {
		tailX.pop_front();
	}
	while (tailY.size() > unsigned(score)) {
		tailY.pop_front();
	}
}

void gameLevel()
{
	system("cls");

	for (j = 0; j <= j_max; j++) {
		for (i = 0; i <= i_max; i++) {
			if ((j == 0) || (j == j_max)) {
				std::cout << "@";
			}
			else {
				if ((i == 0) || (i == i_max)) {
					std::cout << "#";
				}
				else {
					SnakeCollisionLogic();
					if (j == y && i == x) { //caseForSnakeHead()
						std::cout << "S";
						AddHeadPositionToTailArray();
					}
					else if (i == fruitX && j == fruitY) { //caseForFruit()
						std::cout << "F";
					}
					else if (fruitX == x && fruitY == y) { //caseForFruitEaten()
						score++;
						fruitX = rand() % (i_max - 2) + 1;
						fruitY = rand() % (j_max - 2) + 1;
					}
					else {
						bool isSnakeHere = false;
						for (int k_isSnakeHere = 0; k_isSnakeHere < tailX.size(); k_isSnakeHere++) {
							if (tailX[k_isSnakeHere] == i && tailY[k_isSnakeHere] == j) {
								isSnakeHere = true;	
							}
						}
						if (isSnakeHere) {
							std::cout << "T";	
						}
						else {
						std::cout << " ";
							}
					}
				}
			}
		}
		std::cout << "\n";
	}
	std::cout << "Score: " << score << "\n";
	PrintSnakeForTroubleshooting();
}

// keyboard inputs
void Input()
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = eDirection::LEFT;
			break;
		case 'd':
			dir = eDirection::RIGHT;
			break;
		case 's':
			dir = eDirection::DOWN;
			break;
		case 'w':
			dir = eDirection::UP;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	switch (dir) {
	case eDirection::LEFT:
		x--;
		break;
	case eDirection::RIGHT:
		x++;
		break;
	case eDirection::UP:
		y--;
		break;
	case eDirection::DOWN:
		y++;
		break;
	default:
		break;
	}
}

int main() 
{
	Setup();

	while (!gameOver) {
		gameLevel();
		Input();
		Logic();
		Sleep(10);

	}


	return 0;

}