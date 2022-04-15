#include <iostream>

template <class Type>
bool is_ptr(Type x)
{
	return false;
}

template <class Type>
bool is_ptr(Type* x)
{
	return true;
}

template <class T>
struct remove_ptr
{
	typedef T type;
};

template <class T>
struct remove_ptr<T*>
{
	using type = typename remove_ptr<T>::type;
};

// ------ 

// what will be generated if Type == int***

// struct remove_ptr<(int**)*>
// {
// 	typedef remove_ptr<int**>::type type;
// };

// struct remove_ptr<(int*)*>
// {
// 	typedef remove_ptr<int*>::type type;
// };

// struct remove_ptr<(int)*>
// {
// 	typedef remove_ptr<int>::type type;
// };

// struct remove_ptr<int>
// {
// 	typedef int type;
// };

template <class T>
using remove_ptr_t = typename remove_ptr<T>::type;

template <class Type>
void foo(Type val)
{
	std::cout << is_ptr(val) << '\n';
	//remove_ptr<Type>::type another_val = 42;
	remove_ptr_t<Type> val1 = 0;
	std::cout << is_ptr(val1) << '\n';
	remove_ptr_t<Type> val2 = 0;
	remove_ptr_t<Type> sum = val1 + val2;
}

int main()
{
	int x = 45;
	int* ptr = &x;
	int** pptr = &ptr;
	int*** ppptr = &pptr;
	foo(x);
	foo(ptr);

	return 0;
}