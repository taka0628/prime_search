#include "traceback.hpp"

traceback_c::traceback_c()
{
    std::cout << "Traceback" << std::endl;
}

traceback_c::~traceback_c()
{
    std::cout << std::setw(10) << std::setfill('-') << std::endl;
}

template <typename T>
void traceback_c::invarid_num(const std::string& name, const T& num)
{
    using namespace std;
    cout << name << ": " << num << endl;
}