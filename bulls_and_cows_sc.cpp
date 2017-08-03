#include<iostream>
#include<conio.h>
#include<time.h>
#define SIZE 4

using namespace std;

void drawIntro(); //����� ��������
void drawRules(); //����� ������
void drawMenu(int _arrowPosition); //³��������� ����
void MainMenu(); //�������� ��������� ����
void start(int _num[]); //����������� �����
void input(int _nInput[]); //��� ����� �������
void check(bool *_win, int _num[], int _nInput[]); //�������� �����
void game(bool *_win, int _num[], int _nInput[]); //�������� ���


int main()
{		
	srand(time(0));
	setlocale(LC_ALL, "RUS");

	int num[SIZE]; //�������� �����
	int nInput[SIZE]; //����� ������
	bool win = false; //��������� ��������
	bool *pWin = &win; //�������� �� ��������� ��������
	
	drawIntro(); //³��������� ��������
	game(pWin, num, nInput); //������ ��������� ���
	system("pause"); //����� ����� �������
	return 0;
}

//����'���� ������ �����
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
	cout << "����'���� ������� �����\n";
	/*//Debug
	for (int i = 0; i < SIZE; i++)
		cout << _num[i];
	cout << endl;*/
}

//���������� ������� �i����i��
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
				cout << "\n����� ������i ���� �i��i\n";
				input(_nInput);
				return;
			}
		}
}

//��i����� �����
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
		cout << "\n�i���! �� ���������! �����...\n\n";
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
	cout << "\n����� - ";
	for (int i = 0; i < SIZE; i++)
		cout << _nInput[i];
	cout << "  ���i� - " << nBulls << "  ���i� - " << nCows << endl;

	//ϳ������ �� ����������
	if (nBulls >= SIZE/2 || nCows >= SIZE/2) //������� �������� ����
		if (nBulls + nCows == SIZE)
			cout << "���������. ����� ������!\n";
		else
			cout << "������� �i�! �����������!\n";	
	if (nBulls == 0 && nCows == 0)
		cout << "������! ����� ���� � ���������� ����i ����\n";
	if (nCows == SIZE)
		cout << "���! �� ������� ��i �����. �������� ��������� �� ����������\n";
}

//�������� ���
void game(bool *_win, int _num[], int _nInput[])
{
	start(_num);
	while (!*_win)
	{
		input(_nInput);
		check(_win, _num, _nInput);
	}
	char answ = ' ';
	cout << "�i����� �� ���?(Y/N) ";
	cin >> answ;
	if (answ == 'y' || answ == 'Y')
	{
		*_win = false;
		game(_win, _num, _nInput);
	}
}

//�������� ��������� ����
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

//�i��������� ���� ����
void drawMenu(int _arrowPosition)
{
	char _arrow[2] = { ' ',' ' };
	_arrow[_arrowPosition] = '>';
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\t\t\t\t" << _arrow[0] << "������ ���\n\t\t\t\t" << _arrow[1] << "�������" << endl;
}

//����� ��������
void drawIntro()
{
	_sleep(500);
	cout << "BBBBB   UU  UU  LL      LL      SSSS\nBB BBB  UU  UU  LL      LL     SS\nBBBBB   UU  UU  LL      LL      SSSS\nBB BBB  UU  UU  LL      LL         SS\nBBBBB    UUUU   LLLLLL  LLLLL   SSSS\n";
	_sleep(500);
	cout << "\n\t AAAA   NN   NN  DDDD\n\tAAAAAA  NNN  NN  DD  DD\n\tAA  AA  NNN NNN  DD  DD\n\tAAAAAA  NN  NNN  DD  DD\n\tAA  AA  NN   NN  DDDD\n";
	_sleep(500);
	cout << "\n CCCC    OOOO    WW     WW   SSSS\nCC  CC  OO  OO   WW  W  WW  SS\nCC      OO  OO   WW  W  WW   SSSS\nCC  CC  OO  OO   WW W W WW      SS\n CCCC    OOOO     WW   WW    SSSS\n\n\n";
	_sleep(500);
	cout << ".:������i�� ����-��� ����i�� ��� ����������:." << endl;
	system("pause");
	drawMenu(0); //�i���������� ���� � �����i�� ���i��� �� "������ ���"
	MainMenu(); //��������� �������� ��������� ���� 
}

//����� ������
void drawRules()
{
	system("cls");
	cout << "\t\t������� ��� \"���� i ������\"\n����\'���� ������ ������������ �����.\n��i ����� ������i ���� �i��i.\n���i �, � ���� �����, ������� ���������� ������� ����� ����������,\n���������� ��i� ���i���, � ������� �� �i���i��� ��i�i�.\n���� ��i������ ����� � �� ��������i �����i�, �� �� � \"���\",\n���� �� � ���� �����i� � �� \"������\".\n\n\n>�����";
	char backToMenu = ' ';
	while (backToMenu != 13)
	{
		backToMenu = getch();
	}
	MainMenu();
}