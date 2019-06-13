#pragma once
#ifndef GLEW_STUFF_UTILS_H
#define GLEW_STUFF_UTILS_H
#endif

#include <string>
#include <sys/stat.h>

namespace utils {
    bool file_exists(const std::string&);
    bool is_uint(int);
}