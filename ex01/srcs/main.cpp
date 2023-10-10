#include "Serializer.hpp"

int main(void) {
    Data obj = {.x = 123, .y = "Hello"};
    Data *ptr = &obj;
    uintptr_t serialized = Serializer::serialize(ptr);
    Data *deserialized = Serializer::deserialize(serialized);
    if (ptr == deserialized) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Fail!" << std::endl;
    }
}
