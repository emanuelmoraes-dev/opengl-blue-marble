#include "fs.hh"

#include <fstream>

int readFile(const char* path, std::string& content) {
    if (std::ifstream fileStream { path, std::ios::in }) {
        content.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
        return 0;
    } else {
        return 1;
    }
}
