#pragma once

class IReceiver
{
public:
	virtual void Receive(int message) = 0;
	virtual ~IReceiver() {}
};