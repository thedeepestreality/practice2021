#include "functions.h"

int return42()
{
	return 43;
}

int Dummy::sum(int a, int b)
{
	return a + b + m_x;
}

Dummy::Dummy(int x) : m_x(x) 
{

}

Dummy* create_dummy(int x)
{
	return new Dummy(x);
}