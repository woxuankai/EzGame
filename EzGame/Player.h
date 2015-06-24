#ifndef PLAYER_H
#define PLAYER_H
/////////////////////////////////////////////////////////////////////
class Player;








////////////////////////////////////////////////////////////////////






#include <string>

#include "Role.h"
#include "Item.h"

using namespace std;

class Player{
	friend class Role;
	friend class Repertory;

private:
	string playername;

	//一个玩家所拥有的选项
	//一个选项只能被一个玩家绑定
	Role* role;//人物//考虑到玩家的人物可能死亡等等，所以使用指针类型
//	Repertory repertory;//玩家所拥有的物品，可以给人物配备
public:
	//得到这些值
	Role* getRole(void);
//	const Repertory* getRepertory(void);

	//如果要添加的选项以已经被绑定在别的玩家或者未被绑定，都无法被添加
	uint8_t addRole(Role*);//成功返回0

	//试图删除未被添加的选项时会返回错误
	uint8_t deleteRole(void);//成功返回0

	//返回name
	string getPlayername(void);



	//构造函数
	Player(string name);
	Player(void);
	//析构函数
	~Player(void);
};




#endif