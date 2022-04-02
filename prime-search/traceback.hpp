#ifndef ___TRACE_BACK_HPP
#define ___TRACE_BACK_HPP

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

class traceback_c : public std::exception {
private:
    /* data */
public:
    template <typename T>
    void invarid_num(const std::string& name, const T& num);
};

#endif