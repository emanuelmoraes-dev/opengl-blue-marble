#ifndef _BLUE_MARBLE_FS_HH_INCLUDED_
#define _BLUE_MARBLE_FS_HH_INCLUDED_

#include <string>

int readFile(const char* path, std::string& content);
std::string dir(const char* file);
std::string join(const char* path1, const char* path2);

#endif
