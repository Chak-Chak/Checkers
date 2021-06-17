#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <conio.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;

/*
		Black         = 0,
		Blue          = 1,
		Green         = 2,
		Cyan          = 3,
		Red           = 4,
		Magenta       = 5,
		Brown         = 6,
		LightGray     = 7,
		DarkGray      = 8,
		LightBlue     = 9,
		LightGreen    = 10,
		LightCyan     = 11,
		LightRed      = 12,
		LightMagenta  = 13,
		Yellow        = 14,
		White         = 15
*/
enum Direction { right, left, up, down };
enum Player { Pwhite = 1, Pblack };
enum Side { bwhite, bblack, bgreen, bblue, bred };
enum ColorChecker { empty, white, black };
struct Point { int x, y; };
struct CoordChopQueen { int x, y; };
struct GreenCoord { int x, y; };

class Checker
{
private:
	bool isQueen;
	ColorChecker color;
public:
	~Checker();
	bool getIsQueen() { return this->isQueen; }
	ColorChecker getColorChecker() { return this->color; }
	void setColorChecker(ColorChecker color);
	void setIsQueen(bool isQueen);
	void setPoint(int x, int y);
	void setEmptyChecker();
};

class Cell
{
private:
	bool isActive;
	Side side;
	Checker *checker;
public:
	bool getIsActive() { return this->isActive; }
	void setIsActive(bool isActive) { this->isActive = isActive; }
	Checker *getChecker() { return this->checker; }
	void setChecker(Checker* value) { this->checker = value; }
	Side getSide() { return this->side; }
	void setSide(Side side) { this->side = side; }
	char getSymbol();
};

class Field
{
private:
	Player player;
	int width;
	int height;
	Cell** map;
	int countActiveCells;
	GreenCoord greenCoord;
	bool needMove = false;
	bool canChopMore = false;
public:
	Field();
	Field(int w, int h);
	~Field();
	void print();
	void fill();
	void fillBackground();
	Cell** getMap() { return this->map; }
	int getcountActiveCells() { return this->countActiveCells; }
	void setcountActiveCells(int count) { this->countActiveCells = count; }

	void setFieldsize(int w, int h)
	{
		this->width = w;
		this->height = h;
	}
	int getSizeWidth() { return this->width; }
	int getSizeHeight() { return this->height; }
	Player getPlayer();
	void setPlayer(Player value);
	int getGreenCoordX();
	int getGreenCoordY();
	void setGreenCoord(int x, int y);
	vector<string> getActiveCellCoord();
	Side getOriginalColor(int i, int j);
	void clearMap();
	void deleteChecker(int x, int y);
	void addChecker(int x, int y, ColorChecker color, bool isQuin);
	Player stepChecker();
	void swapCells(int activeX, int activeY, int greenX, int greenY, Checker* activeChecker, Checker* greenChecker);
	bool getNeedMove() { return this->needMove; }
	void setNeedMove(bool value);
	bool getCanChopMore() { return this->canChopMore; }
	void setCanChopMore(bool value);
	Point coordChop(Player player, int activeX, int activeY, int greenX, int greenY);
	void defaultChop(Player player, int activeX, int activeY, int greenX, int greenY, Checker* activeChecker, Checker* greenChecker);
	bool needMoreChop(Player player, int activeX, int activeY, bool isQuin = false);
	CoordChopQueen coordsEnemyCheckerForQueen(int activeX, int activeY, int greenX, int greenY);
};

class Game
{
public:
	int select = 1;
	int text_1 = 0;
	int text_2 = 15;
	int text_3 = 15;
	int background_1 = 15;
	int background_2 = 0;
	int background_3 = 0;
	int choice = 0;
	int numbCheckerWhite;
	int numbCheckerBlack;
	void main_menu_2();
	void main_menu();
	int game(Field *field, int width, int height);
	void move(Field *field, int width, int height, Player color);
	void displacement(Field* field, Direction direction, Side side);
	int checkWin(Field* field);
};