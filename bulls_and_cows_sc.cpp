#include<iostream>
#include<conio.h>
#include<time.h>
#define SIZE 4

using namespace std;

void drawIntro(); //Екран заставки
void drawRules(); //Екран правил
void drawMenu(int _arrowPosition); //Відмальовка меню
void MainMenu(); //Менеджер головного меню
void start(int _num[]); //Загадування числа
void input(int _nInput[]); //Ввід числа гравцем
void check(bool *_win, int _num[], int _nInput[]); //Перевірка числа
void game(bool *_win, int _num[], int _nInput[]); //Менеджер гри


int main()
{		
	srand(time(0));
	setlocale(LC_ALL, "RUS");

	int num[SIZE]; //Загадане число
	int nInput[SIZE]; //Число гравця
	bool win = false; //Прапорець перемоги
	bool *pWin = &win; //Вказівник на прапорець перемоги
	
	drawIntro(); //Відмальовка заставки
	game(pWin, num, nInput); //Запуск менеджера гри
	system("pause"); //Пауза перед виходом
	return 0;
}

//Комп'ютер загадує число
void start(int _num[])
{
	for (int i = 0; i < SIZE; i++)
	{
		_num[i] = rand() % 10;
		if (i>0)
			for (int j = 0; j < i; j++)
				if (_num[i] == _num[j])
				{
					start(_num);
					return;
				}
	}
	system("cls");
	cout << "Комп'ютер загадав число\n";
	/*//Debug
	for (int i = 0; i < SIZE; i++)
		cout << _num[i];
	cout << endl;*/
}

//Користувач вводить вiдповiдь
void input(int _nInput[])
{
	for (int i = 0; i < SIZE; i++)
	{
		char ch = -1;
		while (ch < 0 || ch > 9)
		{
			ch = getch() - 48;
		}
		_nInput[i] = (int)ch;
		cout << _nInput[i];
	}
	for (int i = 0; i < SIZE; i++)
		for (int j = SIZE - 1; j > i; j--)
		{
			if (_nInput[i] == _nInput[j])
			{
				cout << "\nЦифри повиннi бути рiзнi\n";
				input(_nInput);
				return;
			}
		}
}

//Порівнюємо числа
void check(bool *_win, int _num[], int _nInput[])
{
	bool skipBulls[SIZE] = { 0,0,0,0 };
	int nBulls = 0;
	for (int i = 0; i < SIZE; i++)
		if (_num[i] == _nInput[i]) // Bull found
		{
			skipBulls[i] = true;
			nBulls++;
		}

	if (nBulls == SIZE)
	{
		cout << "\nВiтаю! Ви перемогли! Муууу...\n\n";
		*_win = 1;
		return;
	}
	int nCows = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (skipBulls[i])
			continue;
		for (int j = 0; j < SIZE; j++)
		{
			if (_num[i] == _nInput[j])
				nCows++;
		}
	}
	cout << "\nЧисло - ";
	for (int i = 0; i < SIZE; i++)
		cout << _nInput[i];
	cout << "  Бикiв - " << nBulls << "  Корiв - " << nCows << endl;

	//Підказки та заохочення
	if (nBulls >= SIZE/2 || nCows >= SIZE/2) //Вгадали половину цифр
		if (nBulls + nCows == SIZE)
			cout << "Прекрасно. Майже готово!\n";
		else
			cout << "Хороший хiд! Продовжуйте!\n";	
	if (nBulls == 0 && nCows == 0)
		cout << "Чудово! Таких цифр у загаданому числi нема\n";
	if (nCows == SIZE)
		cout << "Вау! Ви вгадали всi цифри. Лишилось правильно їх розставити\n";
}

//Менеджер гри
void game(bool *_win, int _num[], int _nInput[])
{
	start(_num);
	while (!*_win)
	{
		input(_nInput);
		check(_win, _num, _nInput);
	}
	char answ = ' ';
	cout << "Зiграємо ще раз?(Y/N) ";
	cin >> answ;
	if (answ == 'y' || answ == 'Y')
	{
		*_win = false;
		game(_win, _num, _nInput);
	}
}

//Менеджер головного меню
void MainMenu()
{
	int arrowPosition = 0;
	drawMenu(arrowPosition);
	char answ = 1;
	while (answ != 13)
	{
		answ = getch();
		if (answ == 72)
			arrowPosition = 0;
		if (answ == 80)
			arrowPosition = 1;
		drawMenu(arrowPosition);
	}

	if (arrowPosition)
		drawRules();	
}

//Вiдмальовка меню меню
void drawMenu(int _arrowPosition)
{
	char _arrow[2] = { ' ',' ' };
	_arrow[_arrowPosition] = '>';
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\t\t\t\t" << _arrow[0] << "Потачи гру\n\t\t\t\t" << _arrow[1] << "Правила" << endl;
}

//Екран заставки
void drawIntro()
{
	_sleep(500);
	cout << "BBBBB   UU  UU  LL      LL      SSSS\nBB BBB  UU  UU  LL      LL     SS\nBBBBB   UU  UU  LL      LL      SSSS\nBB BBB  UU  UU  LL      LL         SS\nBBBBB    UUUU   LLLLLL  LLLLL   SSSS\n";
	_sleep(500);
	cout << "\n\t AAAA   NN   NN  DDDD\n\tAAAAAA  NNN  NN  DD  DD\n\tAA  AA  NNN NNN  DD  DD\n\tAAAAAA  NN  NNN  DD  DD\n\tAA  AA  NN   NN  DDDD\n";
	_sleep(500);
	cout << "\n CCCC    OOOO    WW     WW   SSSS\nCC  CC  OO  OO   WW  W  WW  SS\nCC      OO  OO   WW  W  WW   SSSS\nCC  CC  OO  OO   WW W W WW      SS\n CCCC    OOOO     WW   WW    SSSS\n\n\n";
	_sleep(500);
	cout << ".:Натиснiть будь-яку клавiшу щоб продовжити:." << endl;
	system("pause");
	drawMenu(0); //Вiдмальовуємо меню з позицiєю стрiлки на "Почати гру"
	MainMenu(); //Запускаємо менеджер головного меню 
}

//Екран правил
void drawRules()
{
	system("cls");
	cout << "\t\tПравила гри \"Бики i корови\"\nКомп\'ютер загадує чотиризначне число.\nВсi цифри повиннi бути рiзнi.\nТодi ж, в свою чергу, гравець намагається вгадати число противника,\nпропонуючи свiй варiант, а опонент дає кiлькiсть збiгiв.\nЯкщо збiгається цифра в її правильнi позицiї, то це є \"бик\",\nякщо не в своїй позицiї — це \"корова\".\n\n\n>Назад";
	char backToMenu = ' ';
	while (backToMenu != 13)
	{
		backToMenu = getch();
	}
	MainMenu();
}
