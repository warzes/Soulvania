#pragma once

class Subject;

class IObserver
{
public:
	virtual void OnNotify(Subject& subject, int event) = 0;
	virtual ~IObserver() {};
};