#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

int main() {
    glm::vec3 v {1, 2, 3};
    std::cout << glm::to_string(v) << std::endl;
    return 0;
}
