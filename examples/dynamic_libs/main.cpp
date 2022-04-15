#include <iostream>
#include "functions.h"

int main()
{
	std::cout << "Hello world!\n";
	std::cout << "Return42: " << return42() << "\n";

	Dummy* d = create_dummy(2);
	std::cout << d->sum(1,2) << "\n";
	delete d;

	return 0;
}