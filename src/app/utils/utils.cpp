#include "utils.h"

namespace utils {
    bool file_exists(const std::string& file_name) {
        struct stat buf{};
        return (stat(file_name.c_str(), &buf) == 0);
    }
    bool is_uint(const int n) {
        return n > 0;
    }
}
