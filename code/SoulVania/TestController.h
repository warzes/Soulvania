#pragma once

class Mario;

class TestController
{
public:
	TestController(Mario& player);

	void OnKeyStateChanged();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

private:
	Mario& player;
};