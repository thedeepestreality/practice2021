#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Wrong input\n";
        std::cout << "Usage: UpperLowerTxt.exe infile_name outfile_name\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if(!in.is_open())
    {
        std::cout << "Input file open error\n";
        return 2;
    }
    std::cout << "Input file successfully opened\n";
    std::ofstream out(argv[2]);
    if (!out.is_open())
    {
        std::cout << "Output file open error\n";
        return 3;
    }
    std::cout << "Output file successfully opened\n";

    char c;
    while ((c = in.get()) != EOF)
    {
        /*in >> c;*/
        if (c >= 'A' && c <= 'Z')
            c += 32;
        else if (c >= 'a' && c <= 'z')
            c -= 32;
        out << c;
    }
    std::cout << "Successfully written data\n";
    out.close();
    in.close();
    std::cout << "Both files are closed\n";
    return 0;
}
