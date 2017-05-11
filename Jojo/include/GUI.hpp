#pragma once

enum Input;

typedef float DeltaTime;

class GUI
{
public:
	GUI();
	~GUI();

	virtual void update(DeltaTime, Input);


private:

};