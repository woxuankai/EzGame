#include "Item.h"

uint8_t Item::Level2Int(Level le)
{
	switch (le)
	{
	case bronze:return 1; break;
	case silver:return 2; break;
	case gold: return 3; break;
	case diamond: return 4; break;
	default:return 0;
	}
}


Item::Item()
{
	itemname = "none";
	level = bronze;
	Cost = 0;
	addHP = 0;//生命值
	addATK = 0;//攻击力
	addDEF = 0;//防御力
}

Weapon::Weapon(Role* rin, Level lin)
{
	itemname = rin->getRolename() + "'s Weapon";
	level = lin;
	addDEF = 0;//防御力
	addHP = 0;//生命值

	Cost = 100 * Level2Int(lin);
	if (rin->getRolename() == "Warrior")
		addATK = 300 * Level2Int(lin);
	else if (rin->getRolename() == "Wizard")//攻击力//////////////////////////////////////////////////
		addATK = 100 * Level2Int(lin);
	else if (rin->getRolename() == "Goblin")//攻击力//////////////////////////////////////////////////
		addATK = 200 * Level2Int(lin);
}

Armour::Armour(Role* rin, Level lin)
{
	itemname = rin->getRolename() + "'s Armour";
	level = lin;

	addHP = 0;//生命值
	addATK = 0;//攻击力
	Cost = 100 * Level2Int(lin);
	if (rin->getRolename() == "Warrior")
		addDEF = 50 * Level2Int(lin);
	else if (rin->getRolename() == "Wizard")
		addDEF = 150 * Level2Int(lin);
	else if (rin->getRolename() == "Goblin")
		addDEF = 100 * Level2Int(lin);
}

Potion::Potion(Role* rin, Level lin)//补药不分角色
{
		itemname = "Potion";
		level = bronze;
		Cost = 500;
		addHP = 500;//生命值
		addATK = 0;//攻击力
		addDEF = 0;//防御力
}

string Item::getitemname(void)
{
	return itemname;
}

Level Item::getlevel(void)
{
	return level;
}

RoleAttributeType Item::getCost(void)
{
	return Cost;
}

RoleAttributeType Item::getaddHP(void)
{
	return addHP;
}

RoleAttributeType Item::getaddATK(void)
{
	return addATK;
}

RoleAttributeType Item::getaddDEF(void)
{
	return addDEF;
}