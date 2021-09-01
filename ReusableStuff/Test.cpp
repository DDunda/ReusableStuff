#include <iostream>
#include "MakeEnum.h"
#include "LSM.h"

#define EX_STATES(x) x(STATE1) x(STATE2) x(STATE3)
MAKE_ENUM_CLASS(exStates, EX_STATES)
#undef EX_STATES

int main()
{
	LSM counter((size_t)exStates::STATE1, (size_t)exStates::STATE3);
	
	counter.Advance();
	counter.Advance();
	counter.Reset();
	counter.Advance();

	std::cout << to_string((exStates)counter.GetState()) << std::endl;
}