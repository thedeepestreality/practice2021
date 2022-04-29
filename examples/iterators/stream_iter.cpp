// ostream_iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <numeric>
#include <sstream>

int main () {
    std::vector<int> myvector;
    for (int i=1; i<=10; ++i) 
    myvector.push_back(i*10);
    std::cout << "Manual output: \n";
    for (int val: myvector)
        std::cout << val << ", ";
    std::cout << "\n";

    std::cout << "Output through ostream_iterator: \n";
    std::ostream_iterator<int> out_it (std::cout,", ");
    std::copy ( myvector.begin(), myvector.end(), out_it );
    std::cout << "\n";

    // std::ostream_iterator<double> out_it_double (std::cout,", ");
    // std::istringstream str("0.1 0.2 0.3 0.4");
    // std::partial_sum(std::istream_iterator<double>(str),
    //                  std::istream_iterator<double>(),
    //                  out_it_double);

    std::cout << "Partial sum: \n";
    std::vector<int> result(10);
    std::partial_sum(myvector.begin(), myvector.end(), result.begin());
    std::copy ( result.begin(), result.end(), out_it );
    std::cout << "\n";

    std::string str = "10 20 30 40 50 60 70 80 90 100";

    std::cout << "Partial sum form stringstream to vector: \n";
    std::istringstream str_stream1(str);
    std::partial_sum(std::istream_iterator<int>(str_stream1), std::istream_iterator<int>(), result.begin());
    std::copy ( result.begin(), result.end(), out_it );
    std::cout << "\n";

    std::cout << "Partial sum form stringstream to ostream_iterator: \n";
    std::istringstream str_stream2(str);
    std::partial_sum(std::istream_iterator<int>(str_stream2), std::istream_iterator<int>(), out_it);
    std::cout << "\n";

    std::cout << "String parsed to vector: \n";
    std::istringstream str_stream3(str);
    std::copy ( std::istream_iterator<int>(str_stream3), std::istream_iterator<int>(), result.begin() );
    std::copy ( result.begin(), result.end(), out_it );
    std::cout << "\n";

    std::vector<std::string> vec_str(10);
    std::istringstream str_stream4(str);
    std::copy ( std::istream_iterator<std::string>(str_stream4), std::istream_iterator<std::string>(), vec_str.begin() );
    std::copy ( vec_str.begin(), vec_str.end(), std::ostream_iterator<std::string>(std::cout, ", ") );
    std::cout << "\n";

    return 0;
}