#ifndef ROLE_H
#define ROLE_H
////////////////////////////////////////////////////////////////////////////
class Role;

class Warrior;//战士
class Wizard;//法师
class Goblin;//妖怪
#define RoleAttributeType int32_t
#define MAX_POTIONmun 8//角色可携带的最大补药个数

/////////////////////////////////////////////////////////////////////////////////


#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdexcept>
#include <stdexcpt.h>
#include <stdio.h>
#include <string>

#include "Player.h"
#include "Item.h"



using namespace std;


class Role{

public:
	//角色绑定//一个role只能被一个player绑定
	uint8_t bindPlayer(Player*);//绑定角色所属的玩家（已经被绑定时就无法继续被绑定）
//	uint8_t unbindPlayer(void);//解绑
	const Player* getBoundPlayer(void);//查看角色所绑定的玩家（没有被绑定是返回空）//禁止用从角色处得到的指针修改拥有着，故用const

	//角色是否死亡
	bool ifDead() const;
	//查询名字
	string getRolename(void);
	//查看各项属性//可以考虑封装成一个新的class//不想改了...不值得...
	RoleAttributeType getHP(void);//生命值
	RoleAttributeType getATK(void);//攻击力（由所持武器决定）
	RoleAttributeType getDEF(void);//防御力（由所穿盔甲决定）
	RoleAttributeType getWealth(void);// 金钱（可以用于升级武器、盔甲）

	//改变各项属性，输入的数为变化量,最小为0
	RoleAttributeType addHP(RoleAttributeType);//生命值
	RoleAttributeType addATK(RoleAttributeType);//攻击力（由所持武器决定）
	RoleAttributeType addDEF(RoleAttributeType);//防御力（由所穿盔甲决定）
	RoleAttributeType addWealth(RoleAttributeType);// 金钱（可以用于升级武器、盔甲）



	uint8_t EquipWeapon(Weapon*);
	uint8_t EquipArmour(Armour*);
	uint8_t RemoveWeapon();
	uint8_t RemoveArmour();
	uint8_t addPotion(Potion*);
	uint8_t UsePotion(uint8_t);//指定使用哪个药剂

	Weapon* getweapon();
	Armour* getarmour();
	Potion** getpotion();
	//构造函数
	Role();
	//析构函数
	~Role();

protected:
	//角色名字
	string Rolename;

	
private:
	bool ifdead;//角色是否死亡
	//角色所属的玩家（必须在进行任何操作前绑定）
	Player * player;
	//属性
#define MAX_HP 1000
#define MAX_ATK 100
#define MAX_DEF 100
	RoleAttributeType HP;//生命值
	RoleAttributeType ATK;//攻击力（由所持武器决定）
	RoleAttributeType DEF;//防御力（由所穿盔甲决定）
	RoleAttributeType Wealth;// 金钱（可以用于升级武器、盔甲）

	Weapon* weapon;
	Armour* armour;
	Potion* potion[MAX_POTIONmun];
	
};

class Warrior :public Role{//战士
public:
	Warrior();
};
class Wizard :public Role{//法师
public:
	Wizard();
};
class Goblin :public Role{//妖怪
public:
	Goblin();
};

#endif
