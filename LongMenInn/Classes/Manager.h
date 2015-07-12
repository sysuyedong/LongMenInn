#pragma once
#include "Staff.h"
class Manager :
	public Staff
{
public:
	Manager(void);
	~Manager(void);
	Manager(int com, int care, int sa);
	int getComputation();
	int getCarefulness();
	void train();
private:
	int computation;
	int carefulness;
};

