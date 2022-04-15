#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#ifdef MSC_VER
	#define LIB_API extern "C" __declspec(dllexport)
#else
	#define LIB_API extern "C"
#endif

LIB_API int return42();

struct Dummy
{
	Dummy(int x);
	int sum(int a, int b);
private:
	int m_x;
};

LIB_API Dummy* create_dummy(int x);

#endif