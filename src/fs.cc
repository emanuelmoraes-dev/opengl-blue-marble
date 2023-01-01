#include "fs.hh"
#include "errors.hh"
#include "os.hh"

#include <fstream>

int readFile(const char* path, std::string& content) {
    if (std::ifstream fileStream { path, std::ios::in }) {
        content.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
        return 0;
    } else {
        return BM_ERR_FILE_NOT_FOUND;
    }
}

std::string dir(const char* file) {
    const std::string path(file);
    const size_t pos = path.find_last_of(BM_SLASH);
    return path.substr(0, pos);
}

std::string join(const char* path1, const char* path2) {
    return std::string(path1) + BM_SLASH + std::string(path2);
}
