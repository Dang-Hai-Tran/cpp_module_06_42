#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>
#include <stdint.h>

struct Data {
    int x;
    std::string y;
};

class Serializer {
  public:
    Serializer(void);
    Serializer(Serializer &other);
    ~Serializer(void);
    Serializer &operator=(Serializer &other);

    static uintptr_t serialize(Data *ptr);
    static Data *deserialize(uintptr_t raw);
};

#endif
