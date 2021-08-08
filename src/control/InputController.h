#pragma once

class UserInput	{
public:
	enum Type {
		TYPE_7 = 7,
		TYPE_8
	};
};

class InputController {
public:
	char _pad[80];

	void DoBullyDialog(int, char *, char *, UserInput::Type, UserInput::Type);
};