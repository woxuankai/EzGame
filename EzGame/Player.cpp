#include "Player.h"


Player::Player() : playername("default name")
{
}
Player::~Player()
{
	if (role != NULL)
		delete role;
}
Player::Player(string name) : playername(name)
{
}

string Player::getPlayername(void)
{
	return playername;
}
uint8_t Player::addRole(Role* newrole)
{
	if ((newrole->getBoundPlayer()) != NULL)
		return 1;//该role未被正确绑定(绑定到别处或)，无法添加
	role = newrole;
	if (newrole->bindPlayer(this))
		return 1;
	return 0;
}

Role* Player::getRole(void)
{
	return role;
}