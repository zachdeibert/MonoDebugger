#ifndef LOG_H
#define LOG_H
#ifdef DEBUG
#include <iostream>

#define LOG(x) std::cout << x;
#define LOG_LINE std::cout << std::endl;

#else
#define LOG(x)
#define LOG_LINE
#endif
#endif
