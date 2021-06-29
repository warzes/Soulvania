#pragma once

#include "Stopwatch.h"

class Health
{
public:
	Health();
	Health(int value);

	int Value() const;
	bool IsEmpty();
	void Add(int value);
	void Set(int value);
	void Update();

private:
	int currentHealth;
	int addedHealth;
	int maxHealth;
	std::stack<int> healthStack;
	Stopwatch updateTimer;
};