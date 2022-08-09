#include <iostream>
#include "common/util/bitmap.h"

int main() {
    cppnet::Bitmap b;
    b.Init(1000);
    b.Insert(0);
    b.Insert(1);
    b.Insert(64);
    b.Insert(500);
    std::cout << b.GetMinAfter(0) << '\n';
    std::cout << b.GetMinAfter(1) << '\n';
    std::cout << b.GetMinAfter(63) << '\n';
    std::cout << b.GetMinAfter(64) << '\n';
    std::cout << b.GetMinAfter(65) << '\n';
    std::cout << b.GetMinAfter(200) << '\n';
    std::cout << b.GetMinAfter(600) << '\n';
    std::cout << b.GetMinAfter(200) << '\n';
    b.Remove(500);
    std::cout << b.GetMinAfter(200) << '\n';

    return 0;
}

// There are some problem in BitMap class, Or I misunderstand the design.