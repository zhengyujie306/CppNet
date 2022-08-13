//
// Created by 郑育杰 on 2022/8/9.
//
#include <iostream>
#include "common/alloter/pool_block.h"


int main() {
    auto poolblock = cppnet::MakeBlockMemoryPoolPtr(1024, 10);
    std::cout << "pool block size(): \t" << poolblock->GetSize() << '\n';
    std::cout << "pool block length(): \t" << poolblock->GetBlockLength() << '\n';
    auto ptr = poolblock->PoolLargeMalloc();
    std::cout << "the " << 0 << " th memory locate at : " << ptr << '\n';
    free(ptr);
    std::cout << "pool block size(): \t" << poolblock->GetSize() << '\n';
    std::cout << "pool block length(): \t" << poolblock->GetBlockLength() << '\n';

    for(int i = 0; i < 10; ++i) {
        ptr = poolblock->PoolLargeMalloc();
        std::cout << "the " << i + 1 << " th memory locate at : " << ptr << '\n';
        free(ptr);
    }
    std::cout << "pool block size(): \t" << poolblock->GetSize() << '\n';
    ptr = poolblock->PoolLargeMalloc();
    std::cout << "the 12 th memory locate at : " << ptr << '\n';
    free(ptr);

    std::cout << "pool block size(): \t" << poolblock->GetSize() << '\n';
    std::cout << "pool block length(): \t" << poolblock->GetBlockLength() << '\n';

    poolblock->ReleaseHalf();

    std::cout << "pool block size(): \t" << poolblock->GetSize() << '\n';
    std::cout << "pool block length(): \t" << poolblock->GetBlockLength() << '\n';

    return 0;
}