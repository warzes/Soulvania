#pragma once

#include "Powerup.h"

class MoneyBag : public Powerup
{
public:
	MoneyBag(int money, ObjectId type);

	int GetMoney();

private:
	int money;
};