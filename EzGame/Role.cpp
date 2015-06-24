#include "Role.h"


Weapon* Role::getweapon()
{
	return weapon;
}

Armour* Role::getarmour()
{
	return armour;
}


Potion** Role::getpotion()
{
	return potion;
}


bool Role::ifDead(void) const
{
	return ifdead;
}

const Player* Role::getBoundPlayer(void)
{
	return player;
}

uint8_t Role::bindPlayer(Player* player2bind)
{
	if (player != NULL)
		return 1;	//角色已经被绑定

	if (player2bind->role != this)
		return 1;	//玩家已经被绑定

	player = player2bind;
//	player2bind->role = this;
	return 0;
	//在玩家中绑定角色
}

//uint8_t Role::unbindPlayer(void)
//{
//	if (player == NULL)
//		return 1;	//角色已未被绑定
//
//	if (player->role != this)
//		return 1;	//玩家未经被正确绑定
//
//	player->role = NULL;
//	player = NULL;
//	return 0;
//	//在玩家中绑定角色
//}


Role::Role() :Rolename("default role"), player(NULL), HP(MAX_HP), ATK(0), DEF(0), Wealth(1000), weapon(NULL), armour(NULL), ifdead(false)
{
	for (uint8_t i = 0; i < MAX_POTIONmun; i++)
		potion[i] = NULL;
}



Role::~Role()
{
//	unbindPlayer();//delete class之前需先解绑
//	delete player;
	if (weapon != NULL)
		delete weapon;
	if (armour != NULL)
		delete armour;
	for (uint8_t i = 0; i < MAX_POTIONmun; i++)
		delete potion[i];
}




//查询名字
string Role::getRolename(void)
{
	return Rolename;
}
//查看各项属性
RoleAttributeType Role::getHP(void)//生命值
{
	return (HP >= 0) ? HP : 0;
}
RoleAttributeType Role::getATK(void)//攻击力（由所持武器决定）
{
	return (ATK >= 0) ? ATK : 0;
}
RoleAttributeType Role::getDEF(void)//防御力（由所穿盔甲决定）
{
	return (DEF >= 0) ? DEF : 0;
}
RoleAttributeType Role::getWealth(void)// 金钱（可以用于升级武器、盔甲）
{
	return (Wealth >= 0) ? Wealth  : 0;
}

//改变各项属性，输入的数为变化量
RoleAttributeType Role::addHP(RoleAttributeType change)//生命值
{
	HP += change;
	if (HP <= 0)
		ifdead = true;
	return getHP();
}
RoleAttributeType Role::addATK(RoleAttributeType change)//攻击力（由所持武器决定）
{
	ATK += change;
	return getATK();
}
RoleAttributeType Role::addDEF(RoleAttributeType change)//防御力（由所穿盔甲决定）
{
	DEF += change;
	return getDEF();
}
RoleAttributeType Role::addWealth(RoleAttributeType change)// 金钱（可以用于升级武器、盔甲）
{
	Wealth += change;
	return getHP();
}




uint8_t Role::EquipWeapon(Weapon* eq)
{
	RemoveWeapon();
	this->addATK(eq->getaddATK());
	this->addDEF(eq->getaddDEF());
	this->addHP(eq->getaddHP());
	weapon = eq;
	return 0;
}
uint8_t Role::EquipArmour(Armour* eq)
{
	RemoveArmour();
	this->addATK(eq->getaddATK());
	this->addDEF(eq->getaddDEF());
	this->addHP(eq->getaddHP());
	armour = eq;
	return 0;
}

uint8_t Role::RemoveWeapon()
{
	if (weapon != NULL)
	{
		this->addATK(-(weapon->getaddATK()));
		this->addDEF(-(weapon->getaddDEF()));
		this->addHP(-(weapon->getaddHP()));
		delete weapon;
	}
	weapon = NULL;
	return 0;
}
uint8_t Role::RemoveArmour()
{
	if (armour != NULL)
	{
		this->addATK(-(armour->getaddATK()));
		this->addDEF(-(armour->getaddDEF()));
		this->addHP(-(armour->getaddHP()));
		delete armour;
	}
	armour = NULL;
	return 0;
}
uint8_t Role::addPotion(Potion* po)
{
	uint32_t cnt;
	for (cnt = 0; cnt < MAX_POTIONmun; cnt++)
		if ((this->getpotion())[cnt] == NULL)
			break;
	if (cnt >= MAX_POTIONmun)
		return 1;//没地方放了
	else
	{
		(this->getpotion())[cnt] = po;
		return 0;
	}

}
uint8_t Role::UsePotion(uint8_t num)//指定使用哪个药剂
{
	if (num >= MAX_POTIONmun)
		return 1;
	if (potion[num] == NULL)
		return 1;
	//修改属性
	this->addHP(potion[num]->getaddHP());
	delete potion[num];
	potion[num] = NULL;
	return 0;
}


Warrior::Warrior(void)
{
	Rolename = "Warrior";
}

Wizard::Wizard(void)
{
	Rolename = "Wizard";
}
Goblin::Goblin(void)
{
	Rolename = "Goblin";
}
