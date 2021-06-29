#pragma once

#include "IObserver.h"

class Subject
{
public:
	void AddObserver(IObserver& observer);
	void RemoveObserver(IObserver& observer);

	static Subject Empty();

protected:
	void Notify(int event);

private:
	std::vector<IObserver*> observers;
};