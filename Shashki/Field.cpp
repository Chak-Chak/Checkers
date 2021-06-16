#include "Field.h"

void to_json(json& j, Field& field) {
	j["width"] = field.getSizeWidth();
	j["height"] = field.getSizeHeight();
	string name;
	for (int x = 0; x < field.getSizeWidth(); x++)
	{
		for (int y = 0; y < field.getSizeHeight(); y++)
		{
			name = "cell" + std::to_string(x) + std::to_string(y);
			j["map"][name]["isQueen"] = field.getMap()[x][y].getChecker()->getIsQueen();
			j["map"][name]["colorChecker"] = field.getMap()[x][y].getChecker()->getColorChecker();
			j["map"][name]["isActive"] = field.getMap()[x][y].getIsActive();
			j["map"][name]["side"] = field.getMap()[x][y].getSide();
		}
	}
	//j["firstPlayerMove"] = field.getFirstPlayerMove();
	j["player"] = field.getPlayer();
	j["needMove"] = field.getNeedMove();
	j["canChopMore"] = field.getCanChopMore();
	j["countActiveCells"] = field.getcountActiveCells();
	j["greenCoordX"] = field.getGreenCoordX();
	j["greenCoordY"] = field.getGreenCoordY();
}

Field* from_json(const json& j) {
	int sizeX, sizeY = 0;
	sizeX = j["width"].get<int>();
	sizeY = j["height"].get<int>();
	Field* temp = new Field(sizeX, sizeY);
	temp->setFieldsize(sizeX, sizeY);
	temp->setcountActiveCells(j["countActiveCells"].get<int>());
	temp->setGreenCoord(j["greenCoordX"].get<int>(), j["greenCoordY"].get<int>());
	//temp->setFirstPlayerMove(j["firstPlayerMove"].get<bool>());
	temp->setPlayer(j["player"].get<Player>());
	temp->setNeedMove(j["needMove"].get<bool>());
	temp->setCanChopMore(j["canChopMore"].get<bool>());

	string name;

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			name = "cell" + std::to_string(x) + std::to_string(y);
			temp->getMap()[x][y].getChecker()->setIsQueen(j["map"][name]["isQueen"].get<bool>());
			temp->getMap()[x][y].getChecker()->setColorChecker(j["map"][name]["colorChecker"].get<ColorChecker>());
			temp->getMap()[x][y].setIsActive(j["map"][name]["isActive"].get<bool>());
			temp->getMap()[x][y].setSide(j["map"][name]["side"].get<Side>());
		}
	}
	return temp;
}


void SetColor(int text, int background = 0)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

/*char Cell::getSymbol()
{
	if (this->checker->getColorChecker() == ColorChecker::empty) {
		return ' ';
	}
	else if (this->checker->getColorChecker() == ColorChecker::white){
		return 'A';
	}
	else {
		return 'U';
	}
}*/


void Checker::setColorChecker(ColorChecker value) { this->color = value; }
void Checker::setIsQueen(bool isQueen) { this->isQueen = isQueen; }

Field::Field()
{
	width = 8;
	height = 8;
	Cell** field = new Cell * [width];
	for (int i = 0; i < width; i++)
		field[i] = new Cell[height];

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			field[i][j].setChecker(new Checker());
			field[i][j].getChecker()->setColorChecker(ColorChecker::white);
			field[i][j].setIsActive(false);
			field[i][j].setIsActive(false);
			//this->setFirstPlayerMove(true);
			this->setPlayer(Player::Pwhite);
			this->setcountActiveCells(0);
		}
	}
	this->map = field;
}

Field::Field(int w, int h)
{
	this->width = w;
	this->height = h;
	Cell** cells = new Cell *[this->width];
	for (int i = 0; i < this->width; i++)
		cells[i] = new Cell[this->height];

	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			cells[i][j].setChecker(new Checker());
			cells[i][j].getChecker()->setColorChecker(ColorChecker::empty);
			cells[i][j].setIsActive(false);
			cells[i][j].getChecker()->setIsQueen(false);
			//this->setFirstPlayerMove(true);
			this->setPlayer(Player::Pwhite);
			this->setcountActiveCells(0);
		}
	}
	this->map = cells;
}

Checker::~Checker()
{
	//delete this->isQueen;
	//delete this->
}

Field::~Field() 
{ 
	//delete width;
	//delete height;
	//delete[] map; 
	for (int x = 0; x < this->getSizeWidth(); x++)
	{
		for (int y = 0; y < this->getSizeHeight(); y++)
		{
			//delete this->ma
		}
	}
}

void Field::clearMap()
{
	for (int x = 0; x < this->getSizeWidth(); x++)
	{
		for (int y = 0; y < this->getSizeHeight(); y++)
		{
			this->getMap()[x][y].getChecker()->setEmptyChecker();
		}
	}
}

void Field::fill()
{
	for (int x = 0; x < this->getSizeWidth(); x++)
	{
		for (int y = 0; y < this->getSizeHeight(); y++)
		{
			if (x < 3)
			{
				if (this->map[x][y].getSide() == Side::bblack)
				{
					this->map[x][y].getChecker()->setColorChecker(ColorChecker::white);
					continue;
				}
				else
				{
					this->map[x][y].getChecker()->setColorChecker(ColorChecker::empty);
					continue;
				}
			}
			else
			{
				if (x >= this->getSizeWidth() - 3)
				{
					if (this->map[x][y].getSide() == Side::bblack)
					{
						this->map[x][y].getChecker()->setColorChecker(ColorChecker::black);
						continue;
					}
					else
					{
						this->map[x][y].getChecker()->setColorChecker(ColorChecker::empty);
						continue;
					}
				}
				else
				{
					this->map[x][y].getChecker()->setColorChecker(ColorChecker::empty);
					continue;
				}
			}
		}
	}
}

void Field::fillBackground()
{
	for (int x = 0; x < this->getSizeWidth(); x++)
	{
		for (int y = 0; y < this->getSizeHeight(); y++)
		{
			if (x % 2 == 0)
			{
				if (y % 2 == 0)
				{
					this->getMap()[x][y].setSide(Side::bwhite);
				}
				else
				{
					this->getMap()[x][y].setSide(Side::bblack);
				}
			}
			else
			{
				if (y % 2 == 0)
				{
					this->getMap()[x][y].setSide(Side::bblack);
				}
				else
				{
					this->getMap()[x][y].setSide(Side::bwhite);
				}
			}
		}
	}
}

void Field::print()
{
	int Xmax = this->getSizeWidth();
	int Ymax = this->getSizeHeight();
	SetColor(15, 7); //Рамка для поля
	cout << " ";
	for (int x = 0; x < Ymax; x++)
	{
		cout << "   ";
	}
	cout << " "; 
	SetColor(15);
	cout << "\n"; //Рамка для поля
	for (int x = 0; x < Xmax; x++)
	{
		SetColor(15, 7);
		cout << " ";
		SetColor(15);
		for (int y = 0; y < Ymax; y++)
		{
			switch (this->getMap()[x][y].getSide())
			{
				case Side::bblack:
				{
					if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty)
					{
						SetColor(15);
						cout << " " << " " << " ";
					}
					else
					{
						SetColor(15);
						if (this->getMap()[x][y].getChecker()->getIsQueen()) cout << " " << (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white ? "&" : "@") << " "; //Отображение дамки
						else cout << " " << this->getMap()[x][y].getChecker()->getColorChecker() << " ";
					}
					break;
				}
				case Side::bwhite:
				{
					SetColor(0, 15);
					cout << " " << " " << " ";
					SetColor(15);
					break;
				}
				case Side::bgreen:
				{
					if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty)
					{
						SetColor(15, 2);
						cout << " " << " " << " ";
						SetColor(15);
					}
					else
					{
						SetColor(15, 2);
						if (this->getMap()[x][y].getChecker()->getIsQueen()) cout << " " << (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white ? "&" : "@") << " "; //Отображение дамки
						else cout << " " << this->getMap()[x][y].getChecker()->getColorChecker() << " ";
						SetColor(15);
					}
					break;
				}
				case Side::bblue:
				{
					if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty)
					{
						SetColor(15, 1);
						cout << " " << " " << " ";
						SetColor(15);
					}
					else
					{
						SetColor(15, 1);
						if (this->getMap()[x][y].getChecker()->getIsQueen()) cout << " " << (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white ? "&" : "@") << " "; //Отображение дамки
						else cout << " " << this->getMap()[x][y].getChecker()->getColorChecker() << " ";
						SetColor(15);
					}
					break;
				}
			}
		}
		SetColor(15, 7);
		cout << " ";
		SetColor(15);
		cout << endl; //<< "\t\t\t\t";
	}
	SetColor(15, 7); //Рамка для поля
	cout << " ";
	for (int x = 0; x < Ymax; x++)
	{
		cout << "   ";
	}
	cout << " ";
	SetColor(15); //Рамка для поля
	cout << "\n";
}

//bool Field::getFirstPlayerMove() { return this->firstPlayerMove; }
//void Field::setFirstPlayerMove(bool value) { this->firstPlayerMove = value; }
Player Field::getPlayer() { return this->player; }
void Field::setPlayer(Player value) { this->player = value; }

int Field::getGreenCoordX() { return this->greenCoord.x; }

int Field::getGreenCoordY() { return this->greenCoord.y; }

void Field::setGreenCoord(int x, int y)
{
	this->greenCoord.x = x;
	this->greenCoord.y = y;
}

vector<string> Field::getActiveCellCoord()
{
	vector<string> array = { "NULL" , "NULL" };
	for (int x = 0; x < this->getSizeWidth(); x++)
	{
		for (int y = 0; y < this->getSizeHeight(); y++)
		{
			if (this->getMap()[x][y].getIsActive() == true)
			{
				array[0] = to_string(x);
				array[1] = to_string(y);
				return array;
			}
		}
	}
	return array ;
}

Side Field::getOriginalColor(int i, int j)
{
	if (this->getMap()[i][j].getIsActive() == false)
	{
		if ((i % 2 == 0) && (j % 2 == 0)) return Side::bwhite;
		if ((i % 2 == 0) && (j % 2 != 0)) return Side::bblack;
		if ((i % 2 != 0) && (j % 2 == 0)) return Side::bblack;
		if ((i % 2 != 0) && (j % 2 != 0)) return Side::bwhite;
	}
	else
	{
		return Side::bblue;
		/*if ((i % 2 == 0) && (j % 2 == 0)) return Side::bblue;
		if ((i % 2 == 0) && (j % 2 != 0)) return Side::bblue;
		if ((i % 2 != 0) && (j % 2 == 0)) return Side::bblue;
		if ((i % 2 != 0) && (j % 2 != 0)) return Side::bblue;*/
	}
	
}

void Field::addChecker(int x, int y, ColorChecker color, bool isQuin)
{
	if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty)
	{
		if (color == ColorChecker::white)
		{
			this->getMap()[x][y].getChecker()->setColorChecker(ColorChecker::white);
			this->getMap()[x][y].getChecker()->setIsQueen(isQuin);
			return;
		}
		if (color == ColorChecker::black)
		{
			this->getMap()[x][y].getChecker()->setColorChecker(ColorChecker::black);
			this->getMap()[x][y].getChecker()->setIsQueen(isQuin);
			return;
		}
	}
	return;
}

void Checker::setEmptyChecker() 
{ 
	this->color = ColorChecker::empty;
	this->isQueen = false;
}

void Game::main_menu_2()
{
	select = 1;
	text_1 = 0;
	text_2 = 15;
	text_3 = 15;
	background_1 = 15;
	background_2 = 0;
	background_3 = 0;
	choice = 0;

	while (1)
	{
		if (select == 1)
		{
			text_1 = 0;
			text_2 = 15;
			text_3 = 15;
			background_1 = 15;
			background_2 = 0;
			background_3 = 0;
		}
		if (select == 2)
		{
			text_1 = 15;
			text_2 = 0;
			text_3 = 15;
			background_1 = 0;
			background_2 = 15;
			background_3 = 0;
		}
		if (select == 3)
		{
			text_1 = 15;
			text_2 = 15;
			text_3 = 0;
			background_1 = 0;
			background_2 = 0;
			background_3 = 15;
		}

		system("cls");
		SetColor(15);
		cout << "\n\n\n\n\n\n\n\t\t\t\tКак заполнить поле?" << endl << endl;
		cout << "\t\t\t\t";
		SetColor(text_1, background_1);
		cout << "Дефолтная расстановка" << endl;
		SetColor(15);
		cout << "\t\t\t\t";
		SetColor(text_2, background_2);
		cout << "Загрузить из файла" << endl;
		SetColor(15);
		cout << "\t\t\t\t";
		SetColor(text_3, background_3);
		cout << "Назад" << endl;
		SetColor(15);

		choice = _getch();
		switch (choice)
		{
		case 72: //Вверх
		{
			if (select - 1 == 0) select = 3;
			else select = select - 1;
			break;
		}
		case 80: //Вниз
		{
			if (select + 1 == 4) select = 1;
			else select = select + 1;
			break;
		}
		case 13: //Enter
		{
			switch (select)
			{
			case 1:
			{
				int i = 1;
				while (i != 0)
				{
					system("cls");
					int row;
					int column;
					cout << "\n\n\t\t\t\tВведите размер поля: ";
					cout << "\n Ширина ( не менее 5 ) = ";
					cin >> column;
					cout << "\n Высота ( не менее 8 ) = ";
					cin >> row;
					if ((row < 8) || (column < 5)) continue;
					Field* field = new Field(row, column);
					while (1)
					{
						system("cls");
						field->clearMap();
						field->fillBackground();
						field->print();
						cout << "\n\n Так будет выглядеть ваше игровое поле";
						cout << "\n\n Подтвердить? (Y-Да / N-Нет)";
						int choice = _getch();
						switch (choice)
						{
						case 121:;
						case 89: //Y-Да
						{
							i = 0;
							break;
						}
						case 110:;
						case 78: //N-Нет
						{
							delete field;
							field = NULL;
							cout << "\nDeleted..." << endl;
							break;
						}
						default:
						{
							continue;
						}
						};
						break;
					}
					if (field != NULL) {
						field->fill();
						cout << "\nПоле заполнено!" << endl;
						field->print();
						cout << endl;
						system("pause");
						field->getMap()[0][0].setSide(Side::bgreen);
						field->setGreenCoord(0, 0);
						game(field, row, column);
						break;
					}
				}				
			}
			case 2:
			{
				ifstream fin("./save.json");
				Field* field;
				if (fin.is_open() && ((fin.peek() != EOF)))
				{
					json j;
					fin >> j;
					field = from_json(j);
				}
				else
				{
					cout << endl << "Сохранений нет :(" << endl;
					system("pause");
					break;
				}
				fin.close();
				game(field, field->getSizeWidth(), field->getSizeHeight());
				system("pause");
			}
			case 3:
				main_menu();
			}
		}
		default: break;
		}
		continue;
	}
}
void Game::main_menu()
{
	select = 1;
	text_1 = 0;
	text_2 = 15;
	background_1 = 15;
	background_2 = 0;
	choice = 0;

	while (1)
	{
		if (select == 1)
		{
			text_1 = 0;
			text_2 = 15;
			background_1 = 15;
			background_2 = 0;
		}
		if (select == 2)
		{
			text_1 = 15;
			text_2 = 0;
			background_1 = 0;
			background_2 = 15;
		}

		system("cls");
		SetColor(15);
		cout << "\n\n\n\n\n\n\n\t\t\t\t     Меню" << endl << endl;
		cout << "\t\t\t\t  ";
		SetColor(text_1, background_1);
		cout << "Начать игру" << endl;
		SetColor(15);
		cout << "\t\t\t\t     ";
		SetColor(text_2, background_2);
		cout << "Выход" << endl;
		SetColor(15);

		choice = _getch();
		switch (choice)
		{
		case 72: //Вверх
		{
			if (select - 1 == 0) select = 2;
			else select = select - 1;
			break;
		}
		case 80: //Вниз
		{
			if (select + 1 == 3) select = 1;
			else select = select + 1;
			break;
		}
		case 13: //Enter
		{
			switch (select)
			{
			case 1:
			{
				main_menu_2();
			}
			case 2:
			{
				exit(0);
			}
			}
		}
		default: break;
		}
		continue;
	}
}

int Game::game(Field *field, int width, int height) //todo
{
	while (1)
	{
		if (this->checkWin(field) == 1)
		{
			cout << endl << endl << "\t>>>>>>Победил игрок с белыми фишками(1)<<<<<<";
			system("pause");
			//delete field;
			this->main_menu();
		}
		else
		{
			if (this->checkWin(field) == 2)
			{
				cout << endl << endl << "\t>>>>>>Победил игрок с белыми фишками(2)<<<<<<";
				system("pause");
				//delete field;
				this->main_menu();
			}
		}
		system("cls");
		field->print();
		if (field->getPlayer() == Player::Pwhite)
		{
			cout << endl << "----->Ходит игрок с белыми фишками(1)<-----";
		}
		else
		{
			cout << endl << "----->Ходит игрок с черными фишками(2)<-----";
		}
		fflush(stdin);
		this->choice = _getch();
		switch (choice)
		{
		case 75: //Влево
		{
			this->displacement(field, Direction::left, Side::bgreen); //обычное перемещение курсора по полю
			continue;
		}
		case 77: //Вправо
		{
			this->displacement(field, Direction::right, Side::bgreen); //обычное перемещение курсора по полю
			continue;
		}
		case 72: //Вверх
		{
			this->displacement(field, Direction::up, Side::bgreen); //обычное перемещение курсора по полю
			continue;
		}
		case 80: //Вниз
		{
			this->displacement(field, Direction::down, Side::bgreen); //обычное перемещение курсора по полю
			continue;
		}
		case 13: //Enter
		{
			if (field->getNeedMove() != true) //Нужно ли переместить фишку или рубить?
			{
				cout << endl << "Делаем точку активной" << endl;
				system("pause");
				int x = field->getGreenCoordX();
				int y = field->getGreenCoordY();
				int countActiveCells = field->getcountActiveCells();
				Cell tempCell = field->getMap()[x][y];
				if ((field->getPlayer() == white) && (tempCell.getChecker()->getColorChecker() == ColorChecker::white) && (tempCell.getIsActive() == false))
				{
					if (countActiveCells == 0)
					{
						field->getMap()[x][y].setIsActive(true);
						field->getMap()[x][y].setSide(Side::bblue);
						field->setcountActiveCells(1);
						field->setNeedMove(true);
					}
				}
				else
				{
					if ((field->getPlayer() == black) && (tempCell.getChecker()->getColorChecker() == ColorChecker::black) && (tempCell.getIsActive() == false))
					{
						if (countActiveCells == 0)
						{
							field->getMap()[x][y].setIsActive(true);
							field->getMap()[x][y].setSide(Side::bblue);
							field->setcountActiveCells(1);
							field->setNeedMove(true);
						}
					}
				}
			}
			else
			{
				cout << endl << "Сруб или перемещение" << endl; //Сруб или перемещение
				system("pause");
				int greenX = field->getGreenCoordX();
				int greenY = field->getGreenCoordY();
				vector<string> activeCoords = field->getActiveCellCoord();
				int activeX = stoi(activeCoords[0]);
				int activeY = stoi(activeCoords[1]);
				Checker* activeChecker = field->getMap()[activeX][activeY].getChecker();
				Checker* greenChecker = field->getMap()[greenX][greenY].getChecker();

				if ((field->getMap()[greenX][greenY].getChecker()->getColorChecker() == ColorChecker::empty) && (field->getOriginalColor(greenX, greenY) == Side::bblack))
				{
					field->setPlayer(field->stepChecker(field->getPlayer())); //Перемещение или сруб

					break; //todo
				}
			}
			continue;
		}
		//case 8: //BackSpace
		case 32: //Space
		{
			if (field->getCanChopMore() == false)
			{
				vector<string> activeCoords = field->getActiveCellCoord();
				if ((activeCoords[0] != "NULL") && (activeCoords[1] != "NULL"))
				{
					int x = stoi(activeCoords[0]);
					int y = stoi(activeCoords[1]);
					field->getMap()[x][y].setIsActive(false);
					Side bgr = field->getOriginalColor(x, y);
					field->getMap()[x][y].setSide(bgr);
					field->setcountActiveCells(0);
					field->setNeedMove(false);
				}
			}
			continue;
		}
		case 27: //Esc
		{
			if (field->getCanChopMore() == false)
			{
				if (field->getNeedMove() != true) //Нужно ли переместить фишку или рубить?
				{
					while (1)
					{
						system("cls");
						field->print();
						cout << "\n\t\tСохранить игру перед выходом в меню? / Y - YES / N - NO / C - CANCEL /";
						fflush(stdin);
						this->choice = _getch();
						switch (choice)
						{
						case 121:;
						case 89: //Y-Да
						{
							//Сохранение игры и выход в меню
							ofstream fout("./save.json");
							if (fout.is_open())
							{
								json j;
								to_json(j, *field);
								fout << j;
							}
							fout.close();
							this->main_menu();
						}
						case 110:;
						case 78: //N-Нет
						{
							//Выход в меню игры без сохранения
							this->main_menu();
						}
						case 67: //C-назад
						{
							break;
						}
						default:
						{
							continue;
						}
						}
						break;
					}
				}
			}
			else cout << endl << endl << "\t\t\tСначала закончите ход!";
			continue;
		}
		break;
		}
		continue;
	}
}

void Game::displacement(Field* field, Direction direction, Side side) //Смещение зеленой ячейки
{
	if (side == Side::bgreen)
	{
		int x = field->getGreenCoordX();
		int y = field->getGreenCoordY();
		
		int Xmax = field->getSizeWidth();
		int Ymax = field->getSizeHeight();
		switch (direction)
		{
		case 0: //Вправо
		{
			if ((y + 1) >= Ymax)
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[x][0].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(x, 0);
				return;
			}
			else
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[x][y + 1].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(x, y + 1);
				return;
			}
		}
		case 1: // Влево
		{
			if ((y - 1) < 0)
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[x][Ymax - 1].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(x, Ymax - 1);
				return;
			}
			else
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[x][y - 1].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(x, y - 1);
				return;
			}
		}
		case 2: //Вверх
		{
			if ((x - 1) < 0)
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[Xmax - 1][y].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(Xmax - 1, y);
				return;
			}
			else
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[x - 1][y].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(x - 1, y);
				return;
			}
		}
		case 3: //Вниз
		{
			if ((x + 1) >= Xmax)
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[0][y].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(0, y);
				return;
			}
			else
			{
				Side bgr = field->getOriginalColor(x, y);
				field->getMap()[x + 1][y].setSide(Side::bgreen);
				field->getMap()[x][y].setSide(bgr);
				field->setGreenCoord(x + 1, y);
				return;
			}
		}
		}
	}
}

Player Field::stepChecker(Player color)
{
	int greenX = this->getGreenCoordX();
	int greenY = this->getGreenCoordY();
	vector<string> activeCoords = this->getActiveCellCoord();
	int activeX = stoi(activeCoords[0]);
	int activeY = stoi(activeCoords[1]);
	Checker* activeChecker = this->getMap()[activeX][activeY].getChecker();
	Checker* greenChecker = this->getMap()[greenX][greenY].getChecker();
	if (activeChecker->getIsQueen() == true) //Если шашка - дамка
	{
		if ((abs(greenX - activeX) > 0) && (abs(greenX - activeX) == abs(greenY - activeY))) //Обычное перемещение
		{
			this->swapCells(activeX, activeY, greenX, greenY, activeChecker, greenChecker);
			if (color == Player::Pwhite) { color = Player::Pblack; }
			else { if (color == Player::Pblack) { color = Player::Pwhite; } }
			this->setNeedMove(false);
			return color;
		}
	}
	else //Если обычная шашка
	{
		//this->defaultChop(field, color, activeX, activeY, greenX, greenY, activeChecker, greenChecker);
		if ((abs(activeX - greenX) == abs(activeY - greenY)) && abs(activeX - greenX) == 1) //Обычное перемещение
		{
			if (((color == Player::Pwhite) && (greenX > activeX)) || ((color == Player::Pblack) && (greenX < activeX)))
			{
				this->swapCells(activeX, activeY, greenX, greenY, activeChecker, greenChecker);
				if (((greenX == 0) && (color == Player::Pblack)) || ((greenX == this->getSizeHeight() - 1) && (color == Player::Pwhite))) this->getMap()[greenX][greenY].getChecker()->setIsQueen(true);
				if (color == Player::Pwhite) color = Player::Pblack;
				else color = Player::Pwhite;
				this->setNeedMove(false);
				return color;
			}
		}
		else
		{
			if ((abs(greenX - activeX) == 2) && (abs(greenY - activeY) == 2)) //Сруб
			{
				Point chopChecker = this->coordChop(color, activeX, activeY, greenX, greenY);
				if (((chopChecker.x != NULL) || (chopChecker.y != NULL)) && 
					(((color == Player::Pwhite) && (this->getMap()[chopChecker.x][chopChecker.y].getChecker()->getColorChecker() == ColorChecker::black)) || 
						((color == Player::Pblack) && (this->getMap()[chopChecker.x][chopChecker.y].getChecker()->getColorChecker() == ColorChecker::white))))
				{
					//this->getMap()[chopChecker.x][chopChecker.y].getChecker()->setColorChecker(ColorChecker::empty); //Опустошение данных у срубленной ячейки
					this->getMap()[chopChecker.x][chopChecker.y].getChecker()->setEmptyChecker();

					this->swapCells(activeX, activeY, greenX, greenY, activeChecker, greenChecker);
					if (((greenX == 0) && (color == Player::Pblack)) || ((greenX == this->getSizeHeight() - 1) && (color == Player::Pwhite))) this->getMap()[greenX][greenY].getChecker()->setIsQueen(true);
					if (this->needMoreChop(color, greenX, greenY))
					{
						this->getMap()[greenX][greenY].setIsActive(true);
						this->setcountActiveCells(1);
						this->canChopMore = true;
						return color;
					}
					else
					{
						this->needMove = false;
						this->canChopMore = false;
						if (color == Player::Pwhite) color = Player::Pblack;
						else color = Player::Pwhite;
						return color;
					}
				}
			}
		}
		return color;
	}
}

Point Field::coordChop(Player player, int activeX, int activeY, int greenX, int greenY)
{
	Checker* activeChecker = this->getMap()[activeX][activeY].getChecker();
	if (this->getMap()[activeX][activeY].getChecker()->getIsQueen()) //Если дамка
	{
		int countEnemyChecker = 0;
		int countFriendlyChecker = 0;

		if (((greenX > activeX) && (greenY > activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX + 1][activeY + 1].getChecker()->getColorChecker()))
		{
			return Point{ activeX + 1, activeY + 1 };
		}
		else
		{
			if (((greenX > activeX) && (greenY < activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX + 1][activeY - 1].getChecker()->getColorChecker()))
			{
				return Point{ activeX + 1, activeY - 1 };
			}
			else
			{
				if (((greenX < activeX) && (greenY < activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX - 1][activeY - 1].getChecker()->getColorChecker()))
				{
					return Point{ activeX - 1, activeY - 1 };
				}
				else
				{
					if (((greenX < activeX) && (greenY > activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX - 1][activeY + 1].getChecker()->getColorChecker()))
					{
						return Point{ activeX + -1, activeY + 1 };
					}
				}
			}
		}
	}
	else
	{
		if (((greenX > activeX) && (greenY > activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX + 1][activeY + 1].getChecker()->getColorChecker()))
		{
			return Point { activeX + 1, activeY + 1 };
		}
		else
		{
			if (((greenX > activeX) && (greenY < activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX + 1][activeY - 1].getChecker()->getColorChecker()))
			{
				return Point{ activeX + 1, activeY - 1 };
			}
			else
			{
				if (((greenX < activeX) && (greenY < activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX - 1][activeY - 1].getChecker()->getColorChecker()))
				{
					return Point{ activeX - 1, activeY - 1 };
				}
				else
				{
					if (((greenX < activeX) && (greenY > activeY)) && (activeChecker->getColorChecker() != this->getMap()[activeX - 1][activeY + 1].getChecker()->getColorChecker()))
					{
						return Point{ activeX +- 1, activeY + 1 };
					}
				}
			}
		}
	}
	return Point{ NULL, NULL };
}

void Field::swapCells(int activeX, int activeY, int greenX, int greenY, Checker* activeChecker, Checker* greenChecker)
{
	this->getMap()[greenX][greenY].setChecker(activeChecker);
	this->getMap()[activeX][activeY].setChecker(greenChecker);
	this->getMap()[activeX][activeY].setIsActive(false);
	this->getMap()[activeX][activeY].setSide(Side::bblack);
	this->setcountActiveCells(0);
	this->setNeedMove(true);
}

/*void Field::defaultChop(Player player, int activeX, int activeY, int greenX, int greenY, Checker* activeChecker, Checker* greenChecker)
{
	if (player == Player::Pwhite)
	{
		if ((greenX == activeX + 1) && ((greenY == activeY + 1) || (greenY == activeY - 1)))
		{
			this->swapCells(activeX, activeY, greenX, greenY, activeChecker, greenChecker);
			if (player == Player::Pwhite) { player = Player::Pblack; }
			else { if (player == Player::Pblack) { player = Player::Pwhite; } }
		}
		else
		{
			if ((abs(greenX - activeX) == 2) && (abs(greenY - activeY) == 2))
			{
				Point chopChecker = this->coordChop(player, activeX, activeY, greenX, greenY);
				if (((chopChecker.x != NULL) || (chopChecker.y != NULL)) && (this->getMap()[chopChecker.x][chopChecker.y].getChecker()->getColorChecker() == ColorChecker::black))
				{
					this->getMap()[chopChecker.x][chopChecker.y].setChecker(this->getMap()[0][0].getChecker());
					this->swapCells(activeX, activeY, greenX, greenY, activeChecker, greenChecker);
					if (this->needMoreChop(player, greenX, greenY))
					{
						this->getMap()[greenX][greenY].setIsActive(true);
					}
					else this->needMove = false;
				}
			}
		}
	}
	else
	{
		if ((greenX == activeX - 1) && ((greenY == activeY + 1) || (greenY == activeY - 1)))
		{
			this->swapCells(activeX, activeY, greenX, greenY, activeChecker, greenChecker);
			if (player == Player::Pwhite) { player = Player::Pblack; }
			else { if (player == Player::Pblack) { player = Player::Pwhite; } }
		}
		else
		{
			if ((abs(greenX - activeX) == 2) && (abs(greenY - activeY) == 2))
			{
				Point chopChecker = this->coordChop(player, activeX, activeY, greenX, greenY);
				if (((chopChecker.x != NULL) || (chopChecker.y != NULL)) && (this->getMap()[chopChecker.x][chopChecker.y].getChecker()->getColorChecker() == ColorChecker::white))
				{
					this->getMap()[chopChecker.x][chopChecker.y].setChecker(this->getMap()[0][0].getChecker());
					this->swapCells(activeX, activeY, greenX, greenY, activeChecker, greenChecker);
					if (this->needMoreChop(player, greenX, greenY))
					{
						this->getMap()[greenX][greenY].setIsActive(true);
					}
					else this->needMove = false;
				}
			}
		}
	}
}*/

bool Field::needMoreChop(Player player, int greenX, int greenY, bool isQuin)
{
	ColorChecker colorChecker;
	if (player == Player::Pwhite) colorChecker = ColorChecker::white;
	else colorChecker = ColorChecker::black;
	int checkEmptyX, checkEmptyY, checkCheckerX, checkCheckerY;

	if (isQuin) //Если дамка
	{
		for (int x = greenX, y = greenY; 0 <= x < this->getSizeWidth() - 1, 0 <= y < this->getSizeHeight() - 1; x++, y++)
		{
			if (((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white)) ||		//Если нашлась союзная шашка, прекращаем 
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black))) break;	//поиск в этом направлении
			if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty) continue;									//Если ячейка пуста, пропускаем её
			if ((((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black)) ||		//Если нашлась вражеская шашка
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white))) &&
				((x + 1 <= this->getSizeWidth() - 1) && (y + 1 <= this->getSizeHeight() - 1)))
			{
				if (this->getMap()[x + 1][y + 1].getChecker()->getColorChecker() == ColorChecker::empty) return true;					//Если за вражеской шашкой следует пустая ячейка
			}
				
		}
		for (int x = greenX, y = greenY; 0 <= x < this->getSizeWidth() - 1, 0 <= y < this->getSizeHeight() - 1; x--, y--)
		{
			if (((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white)) ||
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black))) break;
			if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty) continue;
			if ((((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black)) ||
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white))) &&
				((x - 1 >= 0) && (y - 1 >= 0)))
			{
				if (this->getMap()[x - 1][y - 1].getChecker()->getColorChecker() == ColorChecker::empty) return true;
			}

		}
		for (int x = greenX, y = greenY; 0 <= x < this->getSizeWidth() - 1, 0 <= y < this->getSizeHeight() - 1; x++, y--)
		{
			if (((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white)) ||
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black))) break;
			if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty) continue;
			if ((((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black)) ||
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white))) &&
				((x + 1 <= this->getSizeWidth() - 1) && (y - 1 >= 0)))
			{
				if (this->getMap()[x + 1][y - 1].getChecker()->getColorChecker() == ColorChecker::empty) return true;
			}

		}
		for (int x = greenX, y = greenY; 0 <= x < this->getSizeWidth() - 1, 0 <= y < this->getSizeHeight() - 1; x--, y++)
		{
			if (((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white)) ||
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black))) break;
			if (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::empty) continue;
			if ((((player == Player::Pwhite) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black)) ||
				((player == Player::Pblack) && (this->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white))) &&
				((x - 1 >= 0) && (y + 1 <= this->getSizeHeight() - 1)))
			{
				if (this->getMap()[x - 1][y + 1].getChecker()->getColorChecker() == ColorChecker::empty) return true;
			}

		}
		return false;
	}
	else
	{
		for (int i = 4; i != 0; i--)
		{
			switch (i)
			{
			case 4: { checkEmptyX = -2; checkEmptyY = -2; checkCheckerX = -1; checkCheckerY = -1; break; }
			case 3: { checkEmptyX = 2; checkEmptyY = -2; checkCheckerX = 1; checkCheckerY = -1; break; }
			case 2: { checkEmptyX = 2; checkEmptyY = 2; checkCheckerX = 1; checkCheckerY = 1; break; }
			case 1: { checkEmptyX = -2; checkEmptyY = 2; checkCheckerX = -1; checkCheckerY = 1; break; }
			}
			if ((0 <= greenX + checkEmptyX) && (greenX + checkEmptyX < this->getSizeWidth()) && (0 <= greenY + checkEmptyY) && (greenY + checkEmptyY < this->getSizeHeight())
				&& (this->getMap()[greenX + checkCheckerX][greenY + checkCheckerY].getChecker()->getColorChecker() != colorChecker)
				&& (this->getMap()[greenX + checkCheckerX][greenY + checkCheckerY].getChecker()->getColorChecker() != ColorChecker::empty)
				&& (this->getMap()[greenX + checkEmptyX][greenY + checkEmptyY].getChecker()->getColorChecker() == ColorChecker::empty))
			{
				return true;
			}
		}
		return false;
	}
}

int Field::stepQuin(Player player, int activeX, int activeY, int greenX, int greenY) //todo
{
	return 0;
}

void Field::setCanChopMore(bool value) { this->canChopMore = value; }
void Field::setNeedMove(bool value) { this->needMove = value; }

int Game::checkWin(Field* field)
{
	this->numbCheckerWhite = 0;
	this->numbCheckerBlack = 0;
	int rows = field->getSizeWidth();
	int columns = field->getSizeHeight();
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < columns; y++)
		{
			if (field->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::white) numbCheckerWhite++;
			if (field->getMap()[x][y].getChecker()->getColorChecker() == ColorChecker::black) numbCheckerBlack++;
		}
	}
	if (this->numbCheckerWhite <= 1)
	{
		return 2;
	}
	if (this->numbCheckerBlack <= 1)
	{
		return 1;
	}
	return 0;
}