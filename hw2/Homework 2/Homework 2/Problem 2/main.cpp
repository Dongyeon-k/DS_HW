#include <string>

#include "custommap.hpp"

int main() {
    CustomMap<int, std::string> map;
    map.insert(5, "Five");
    map.insert(3, "Three");
    map.insert(8, "Eight");
    map.insert(10, "Ten");
    map.print_map();

    return 0;
}
