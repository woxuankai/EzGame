#include "mygame.h"
#include "Player.h"
#include "Item.h"
#include <stdint.h>
#include <conio.h>
#include <time.h>

Shell::Shell(void) :playernumber(0)
{
	gameInit();
}
Shell::~Shell(void)
{
	gameOver();
}

void Shell::DispLevel(Level le)//不值得写运算符重载了，先这样凑合用吧
{
	switch (le)
	{
	case bronze: cout << "bronze"; break;
	case silver: cout << "silver"; break;
	case gold: cout << "gold"; break;
	case diamond: cout << "diamond"; break;
	default: break;
	}
}

int32_t Shell::MenuChoose(int32_t min, int32_t max)
{
	int32_t innum;
	cout << "choose a number to contiune" << endl;
	cin >> innum;
	while ((innum > max) || (innum < min))
	{
		cout << "invalid input, please choose again" << endl;
		cin >> innum;
	}
	return innum;
}



uint8_t Shell::ShowTitle()
{
	system("cls");
	cout << "##################" << endl;
	cout << "##****EzGame****##" << endl;
	cout << "##  Version 1.0 ##" << endl;
	cout << "##  Enjoy It!   ##" << endl;
	cout << "##     +_-      ##" << endl;
	cout << "##################" << endl;
	return 0;
}


uint8_t Shell::gameOver()
{
	for (uint32_t i = 1; i <= playernumber; i++)
		if (playerlist[i - 1] == NULL)
			return 1;
		else
			delete playerlist[i - 1];
	return 0;
}

uint8_t Shell::gameInit()
{
	system("color 7");
	//选取游戏类型
	ShowTitle();
	cout << "****************Mume*********************" << endl;
	cout << "*****************************************" << endl;
	cout << "**choose game type                     **" << endl;
	cout << "**                                     **" << endl;
	cout << "** #1  two   players  game             **" << endl;
	cout << "** #2  three players  game             **" << endl;
	cout << "** #3  four  players  game             **" << endl;
	cout << "*****************************************" << endl;
	playernumber = MenuChoose(1, 3)+1;


	//收集姓名级角色
	for (uint32_t i = 1; i <= playernumber; i++)
	{
		ShowTitle();
		cout << "For Player" << i << endl;
		cout << "Now we need some detail to create your role" << endl;
		cout << "Your Name?";
		string namein;
		cin >> namein;
		playerlist[i - 1] = new Player(namein);
		if (playerlist[i - 1] == NULL)
			return 1;
		ShowTitle();
		cout << "Hello " << namein << endl <<"Please choose your role"<<endl;
		cout << "****************Mume*********************" << endl;
		cout << "*****************************************" << endl;
		cout << "**choose your role                     **" << endl;
		cout << "**                                     **" << endl;
		cout << "** #1  Warrior                         **" << endl;
		cout << "** #2  Wizard                          **" << endl;
		cout << "** #3  Goblin                          **" << endl;
		cout << "*****************************************" << endl;
		switch (MenuChoose(1, 3))
		{
		case 1:if (playerlist[i - 1]->addRole(new Warrior())) return 1;
			break;
		case 2:if (playerlist[i - 1]->addRole(new Wizard())) return 1;
			break;
		case 3:if (playerlist[i - 1]->addRole(new Goblin())) return 1;
			break;
		default: return 1;
		}
	}
	return 0;
}


uint8_t Shell::gameStart()
{
	while (1)
	{
		//检测游戏是否结束
		uint32_t alive = 0;
		uint32_t alivedone = 0;
		for (uint32_t i = 1; i <= playernumber; i++)
		{
			if (playerlist[i-1]->getRole()->ifDead() == false)//还有玩家的角色活着
			{
				alive++;
				alivedone = i;
			}
		}
		if (alive <= 1)
		{
			if (alive == 0)
				return 1;//哪儿不对
			cout <<endl<< "Game Over" << endl;
			cout << "Player:" << playerlist[alivedone-1]->getPlayername()<<"WIN!!!"<<endl;
			cout << "Press any key to exit" << endl;
			_getch();
			return 0;
		}
		for (uint32_t i = 1; i <= playernumber; i++)
		{
			if (playerlist[i-1]->getRole()->ifDead() == false)//玩家还活着
			{
				ShowTitle();
				cout << "Player " << i << "  is taking actions" << endl;
				if(ListInfo(i))
					return 1;
				if (TakeAction(i))
					return 1;
			}
		}
	}
}

uint8_t Shell::ListInfo(uint32_t i)
{
	cout << "*-*-*-*-*-*-*-Player "<<i<<"\t :"<<playerlist[i-1]->getPlayername() << endl;
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "*-*-*-*-*-Role info:*-*-*-*-*-*-*-*-*" << endl;
	cout << "*-*-ATK: " << playerlist[i - 1]->getRole()->getATK() <<endl;
	cout << "*-*-DEF: " << playerlist[i - 1]->getRole()->getDEF() <<endl;
	cout << "*-*-HP: " << playerlist[i - 1]->getRole()->getHP() <<endl;
//	if (playerlist[i - 1]->getRole()->getHP() > MAX_HP / 2)
	if (i == 1)
		system("color A");//淡绿色字
//	else if (playerlist[i - 1]->getRole()->getHP() > MAX_HP / 5)
	else if (i == 2)
		system("color 9");//淡蓝色字
	else
		system("color C");//淡红色字
	cout << "*-*-$$: " << playerlist[i - 1]->getRole()->getWealth();
	cout << endl;

	cout << "*-*-My Items:" << endl;
	if (playerlist[i - 1]->getRole()->getarmour() != NULL)
	{ 
		cout << "*-*-name:\t" << playerlist[i - 1]->getRole()->getarmour()->getitemname() << endl;
		cout << "*-*-*-*-level:\t"; DispLevel(playerlist[i - 1]->getRole()->getarmour()->getlevel()); cout << endl;
		cout << "*-*-*-*-DEF(add):\t" << playerlist[i - 1]->getRole()->getarmour()->getaddDEF() << endl;
		cout << "*-*-*-*-Cost:\t" << playerlist[i - 1]->getRole()->getarmour()->getCost() << endl;
	}
	if (playerlist[i - 1]->getRole()->getweapon() != NULL)
	{
		cout << "*-*-name:\t" << playerlist[i - 1]->getRole()->getweapon()->getitemname()<<endl;
		cout << "*-*-*-*-level:\t"; DispLevel(playerlist[i - 1]->getRole()->getweapon()->getlevel()); cout << endl;
		cout << "*-*-*-*-ATK(add):\t" << playerlist[i - 1]->getRole()->getweapon()->getaddATK() << endl;
		cout << "*-*-*-*-Cost:\t" << playerlist[i - 1]->getRole()->getweapon()->getCost() << endl;
	}

	cout << "*-*-name:\t";
	for (uint32_t num = 0; num < MAX_POTIONmun; num++)
		if (playerlist[i - 1]->getRole()->getpotion()[num] !=NULL)
			cout << playerlist[i - 1]->getRole()->getpotion()[num]->getitemname() << "\t";
	cout <<endl<< "*-*-level\t";
	for (uint32_t num = 0; num < MAX_POTIONmun; num++)
		if (playerlist[i - 1]->getRole()->getpotion()[num] != NULL)
			cout << playerlist[i - 1]->getRole()->getpotion()[num]->getlevel() << "\t";
	cout <<endl<< "*-*-HP(add)\t";
	for (uint32_t num = 0; num < MAX_POTIONmun; num++)
		if (playerlist[i - 1]->getRole()->getpotion()[num] != NULL)
			cout << playerlist[i - 1]->getRole()->getpotion()[num]->getaddHP() << "\t";
	cout <<endl << "*-*-Cost\t";
	for (uint32_t num = 0; num < MAX_POTIONmun; num++)
		if (playerlist[i - 1]->getRole()->getpotion()[num] != NULL)
			cout << playerlist[i - 1]->getRole()->getpotion()[num]->getCost() << "\t";
	cout << endl;

	cout << endl << endl;
	cout << ">>";
	return 0;
}

uint8_t Shell::TakeAction(uint32_t i)
{
	cout << endl;
	cout << "****************Mume*********************" << endl;
	cout << "*****************************************" << endl;
	cout << "**Choose one action                    **" << endl;
	cout << "**                                     **" << endl;
	cout << "** #1  Attack                          **" << endl;
	cout << "** #2  Buy                             **" << endl;
	cout << "** #3  Use Potion                      **" << endl;
	cout << "*****************************************" << endl;
	switch (MenuChoose(1, 3))
	{
	case 1: Action_Attack(i); break;
	case 2: Action_Buy(i); break;
	case 3: Action_UsePotion(i); break;
	default: return 1;
	}
	cout << "Press any key to continue";
	_getch();
	return 0;
}



uint8_t Shell::Action_Attack(uint32_t i)
{
	ShowTitle();
	cout << "Player " << i << "  is taking actions" << endl;
	if (ListInfo(i))
		return 1;
	cout << "you choose to attack" << endl;
	cout << endl;
	cout << "****************Mume*********************" << endl;
	cout << "*****************************************" << endl;
	cout << "**Choose one player to attack          **" << endl;
	cout << "**                                     **" << endl;
	for (uint32_t cnt = 1; cnt <= playernumber; cnt++)
		cout << "** #" << cnt << "   " <<playerlist[cnt -1]->getPlayername()<<endl;//可以攻击自己，但是似乎也没有什么不对
	cout << "*****************************************" << endl;
	int32_t target = MenuChoose(1, playernumber);
	int32_t hurt = playerlist[i - 1]->getRole()->getATK() - playerlist[target - 1]->getRole()->getDEF();
	if (hurt <= 0)
		hurt = 0;
	playerlist[target - 1]->getRole()->addHP(-hurt);
#define random(x) (rand()%x)
#define MAX_GETWEALTH 100//一次最多随机得到100
	srand((int)time(0));
	int32_t mg= abs(random(MAX_GETWEALTH));
	playerlist[i - 1]->getRole()->addWealth(mg);

	ShowTitle();
	cout << "Player " << i << "  is taking actions" << endl;
	if (ListInfo(i))
		return 1;

	cout << "****************Result*******************" << endl;
	cout << "*****************************************" << endl;
	cout << "*****You get $$" << mg << endl;
	cout << "*****caused " << playerlist[target - 1]->getPlayername() << "   " << hurt << "  Point(s) hurt" << endl;
	cout << "*****************************************" << endl;
	return 0;
}


uint8_t Shell::BUWea(uint32_t i)
{
	Level nextle;
	if (playerlist[i - 1]->getRole()->getweapon() != NULL)
	{
		nextle = playerlist[i - 1]->getRole()->getweapon()->getlevel();

		if (nextle == bronze)
			nextle = silver;
		else if (nextle == silver)
			nextle = gold;
		else if (nextle == gold)
			nextle = diamond;
	}
	else nextle = bronze;

	Weapon* tempwe = new Weapon(playerlist[i - 1]->getRole(), nextle);
	int32_t needmoney;
	if (nextle == bronze)
		needmoney = tempwe->getCost();
	else
		needmoney = tempwe->getCost() - playerlist[i - 1]->getRole()->getweapon()->getCost();
	if (needmoney > playerlist[i - 1]->getRole()->getWealth())
	{
		ShowTitle();
		cout << "Player " << i << "  is taking actions" << endl;
		if (ListInfo(i))
			return 1;
		cout << "not enough money to buy or update weapon" << endl;
	}
	else
	{
		playerlist[i - 1]->getRole()->addWealth(-needmoney);
		playerlist[i - 1]->getRole()->RemoveWeapon();
		playerlist[i - 1]->getRole()->EquipWeapon(tempwe);
		
		ShowTitle();
		cout << "Player " << i << "  is taking actions" << endl;
		if (ListInfo(i))
			return 1;
		
		cout << "Buy/Upgrade Weapon successfully" << endl;
	}
	return 0;
}


uint8_t Shell::BUArm(uint32_t i)
{
	Level nextle;
	if (playerlist[i - 1]->getRole()->getarmour() != NULL)
	{
		nextle = playerlist[i - 1]->getRole()->getarmour()->getlevel();

		if (nextle == bronze)
			nextle = silver;
		else if (nextle == silver)
			nextle = gold;
		else if (nextle == gold)
			nextle = diamond;
	}
	else nextle = bronze;

	Armour* tempar = new Armour(playerlist[i - 1]->getRole(), nextle);
	int32_t needmoney;
	if (nextle == bronze)
		needmoney = tempar->getCost();
	else
		needmoney = tempar->getCost() - playerlist[i - 1]->getRole()->getarmour()->getCost();
	if (needmoney > playerlist[i - 1]->getRole()->getWealth())
	{
		ShowTitle();
		cout << "Player " << i << "  is taking actions" << endl;
		if (ListInfo(i))
			return 1;
		
		cout << "not enough money to buy or update armour" << endl;
		delete tempar;
	}
	else
	{
		playerlist[i - 1]->getRole()->addWealth(needmoney);
		playerlist[i - 1]->getRole()->RemoveArmour();
		playerlist[i - 1]->getRole()->EquipArmour(tempar);


		ShowTitle();
		cout << "Player " << i << "  is taking actions" << endl;
		if (ListInfo(i))
			return 1;


		cout << "Buy/Upgrade Armour successfully" << endl;
	}
	return 0;
}
uint8_t Shell::Action_Buy(uint32_t i)
{
	while (1)
	{
		cout << "****************Mume*********************" << endl;
		cout << "*****************************************" << endl;
		cout << "**Choose one Item to buy/upgrade       **" << endl;
		cout << "**#1 Buy/Upgrade Weapon                **" << endl;
		cout << "**#2 Buy/Upgrade Armour                **" << endl;
		cout << "**#3 Buy Potion                        **" << endl;
		cout << "**#4 Exit                              **" << endl;
		cout << "*****************************************" << endl;
		switch (MenuChoose(1, 4))
		{ 
		case 1:
			BUWea(i);
			break;
		case 2:
			BUArm(i);
			break;
		case 3:
			uint32_t cnt;
			for (cnt = 0; cnt < MAX_POTIONmun; cnt++)
				if ((playerlist[i - 1]->getRole()->getpotion())[cnt] == NULL)
					break;
			if (cnt >= MAX_POTIONmun)
			{
				ShowTitle();
				cout << "Player " << i << "  is taking actions" << endl;
				if (ListInfo(i))
					return 1;

				cout << "Not Enough Space" << endl;
			}
			else
			{
				Potion *temp = new Potion(playerlist[i - 1]->getRole(), bronze);
				if (temp->getCost() > playerlist[i - 1]->getRole()->getWealth())
				{
					ShowTitle();
					cout << "Player " << i << "  is taking actions" << endl;
					if (ListInfo(i))
						return 1;

					cout << "Not enough Wealth" << endl;
					delete temp;
				}
				else
				{
					playerlist[i - 1]->getRole()->addPotion(temp);
					playerlist[i - 1]->getRole()->addWealth(-(temp->getCost()));
					ShowTitle();
					cout << "Player " << i << "  is taking actions" << endl;
					if (ListInfo(i))
						return 1;
					cout << "Buy Potion Successfully" << endl;
				}
			}
			break;
		case 4:return 0;
		}
	}
}


uint8_t Shell::Action_UsePotion(uint32_t i)
{
	uint32_t cnt;
	for (cnt = 0; cnt < MAX_POTIONmun; cnt++)
		if ((playerlist[i - 1]->getRole()->getpotion())[cnt] != NULL)
			break;
	if (cnt >= MAX_POTIONmun)
	{
		ShowTitle();
		cout << "Player " << i << "  is taking actions" << endl;
		if (ListInfo(i))
			return 1;
		cout << "Not enough Potion left" << endl;
	}
	else
		playerlist[i - 1]->getRole()->UsePotion(cnt);
	return 0;
}