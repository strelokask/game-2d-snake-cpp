// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"
/* =========================*/
#include <cstdlib>
#include <stdlib.h> // to use system, rand()
#include <iostream> // use cout
#include <conio.h> // 
#include <windows.h>
/* =========================*/
#include <stdio.h>
#include <tchar.h>



// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы

// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum Direction { STOP = 0, Left, Right, Up, Down }; 
Direction dir;
int tailX[100], tailY[100];//координаты долек змеек
int nTail = 1; // количество элементов в массиве
void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < width + 1; ++i) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (j == 0 || j == width - 1)	cout << '#';
			else if (i == fruitY && j == fruitX) cout << "F";
			else if (i == y && j == x) cout << "0";
			else {
				bool print = true;
				for (int l = 0; l < nTail; ++l) {
					if (tailY[l] == i && tailX[l] == j) {
						cout << "o";
						print = false;
					}
				}
				if (print) cout << ' ';
			}
		}
		cout << "\n";
	}
	for (int i = 0; i < width + 1; ++i) {
		cout << '#';
	}
	cout << '\n';
	cout << "Score: " << score << '\n';
	cout << "N: " << nTail << '\n';

}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 's':
			dir = Down;
			break;
		case 'w':
			dir = Up;
			break;
		case 'x':
			gameOver = true;
			break;
		default: break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;

	int prev2X, prev2Y;
	for (int i = 1; i < nTail; ++i) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (_getch()) {
	case 'a':
		x--;
		break;
	case 'd':
		x++;
		break;
	case 's':
		y++;
		break;
	case 'w':
		y--;
		break;
	default:
		gameOver = true;
		break;
	}
	for (int i = 0; i < nTail; ++i)
		if (tailX[i] == x && tailY[i] == y) gameOver = true;
	if (x > width - 1) x = width - 2;
	if (y > height - 1) y = height - 1;
	if (x < 1) x = 1;
	if (y < 1) y = 0;
	if (x == fruitX && y == fruitY) {
		nTail++;
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}
int main(){

	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
    return 0;
}

