class Shell;
#ifndef _MYGAME_H
#define _MYGAME_H

#include<iostream>
#include<stdio.h>
#include<stdint.h>
#include "Player.h"
using namespace std;
#define MAX_PLAYER_NUM 4
//用作shell,用于游戏与人的互动
class Shell{
public:
	Shell();
	~Shell();
	uint8_t gameStart();//游戏开始//返回0代表游戏结束
private:
	uint32_t playernumber;//游戏玩家个数
	Player* playerlist[MAX_PLAYER_NUM];//游戏玩家列表


	uint8_t gameInit();//游戏初始化，创建玩家，玩家选择角色//被构造函数调用
	uint8_t gameOver();//删除游戏中产生的变量，安全返回//被析构函数调用
	uint8_t ListInfo(uint32_t);
	uint8_t TakeAction(uint32_t);

	uint8_t ShowTitle();
	int32_t MenuChoose(int32_t,int32_t);

	void DispLevel(Level);
	uint8_t Action_Attack(uint32_t i);
	uint8_t Action_Buy(uint32_t i);
	uint8_t Action_UsePotion(uint32_t i);

	uint8_t BUWea(uint32_t i);
	uint8_t BUArm(uint32_t i);
};


#endif