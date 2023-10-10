#include "Base.hpp"

int main(void) {
    for (int i = 0; i < 10; i++) {
        std::cout << "i = " << i << std::endl;
        Base *p = generate();
        identify(p);
        identify(*p);
        delete p;
    }
}
