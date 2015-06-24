#ifndef ITEM_H
#define ITEM_H
//////////////////////////////////////////////////////////////
class Item;
enum Level{bronze, silver, gold, diamond };
class Weapon;
class Armour;
class Potion;



#include <string>
#include "Role.h"


using namespace std;
//////////////////////////////////////////////////////////////

//定义物品项的基类
class Item{
protected:
	//物品名称
	string itemname;
	//适用角色//为空字符串时适用于任何角色
	string role2use;
	//等级
	Level level;
	//所需金钱
	RoleAttributeType Cost;
	//对人物的加成
	RoleAttributeType addHP;//生命值
	RoleAttributeType addATK;//攻击力
	RoleAttributeType addDEF;//防御力
	uint8_t Level2Int(Level le);
public:
	string getitemname();
	Level getlevel();
	RoleAttributeType getCost();
	RoleAttributeType getaddHP();//生命值
	RoleAttributeType getaddATK();//攻击力
	RoleAttributeType getaddDEF();//防御力
	string getRole2ues(void);

	//构造函数
	Item();
};

class Weapon:public Item{//武器
public:Weapon(Role*,Level);
};

class Armour:public Item{//装甲
public:Armour(Role*, Level);
};

class Potion :public Item{//补药
public:Potion(Role*, Level);
};
#endif


