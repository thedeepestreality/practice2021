#include <iostream>

// void foo(int x){
//     std::cout << "foo by value \n";
// }

// void foo(int& x){
//     std::cout << "foo by reference \n";
// }

class Dummy{
    int* m_arr;
    size_t m_sz;
public:
    Dummy(int* arr, size_t sz) : m_sz(sz) {
        m_arr = new int [sz];
        for (size_t idx = 0; idx < sz; ++idx)
            m_arr[idx] = arr[idx];
    }

    Dummy(Dummy const& val) : Dummy(val.m_arr, val.m_sz) {
        std::cout << "Copy constructor\n";
    }

    Dummy(Dummy&& val){
        std::cout << "Move constructor\n";
    }

    Dummy& operator=(Dummy const& val){
        std::cout << "Copy assignment\n";
        delete[] m_arr;
        m_sz = val.m_sz;
        m_arr = new int [m_sz];
        for (size_t idx = 0; idx < m_sz; ++idx)
            m_arr[idx] = val.m_arr[idx];
        return *this;
    }

    Dummy& operator=(Dummy&& val){
        std::cout << "Move assignment\n";
        delete[] m_arr;
        m_sz = val.m_sz;
        m_arr = val.m_arr;
        val.m_arr = nullptr;
        return *this;
    }

    ~Dummy(){
        if (m_arr)
            delete[] m_arr;
    }
};

Dummy generate_dummy(){
    int arr[3] = {1,2,3};
    return Dummy(arr, 3);
}

void foo(int const& x){
    std::cout << "foo by const reference \n";
}

void foo(int&& x){
    std::cout << "foo by rvalue reference \n";
}

int main(){
    int x = 0;
    int& rx = x;
    int const& crx = x;
    //int& ry = 1; //error: cant bint reference to unnamed tmp object
    int const& cry = 1;
    // cry = 2; // error: cant change constant

    //int&& rz = x; // error: cant bind rvalue to lvalue
    int&& rz = std::move(x);
    //int&& rr = rz; // error: rz has name now
    int&& z = 1;
    z = 2; // valid operations

    foo(1);
    int arr[3] = {1,2,3};
    Dummy manual_d(arr, 3);
    Dummy manual_d_copy = manual_d;

    manual_d_copy = generate_dummy();

    Dummy&& test = Dummy(arr,3);
    //manual_d_copy = std::move(manual_d); //(int&&)manual_d
    manual_d_copy = static_cast<std::remove_reference<Dummy>::type&&>(manual_d);

    return 0;
}