// Use of this source code is governed by a BSD 3-Clause License
// that can be found in the LICENSE file.

// Author: caozhiyi (caozhiyi5@gmail.com)

#ifndef COMMON_ALLOTER_NORMAL_ALLOTER
#define COMMON_ALLOTER_NORMAL_ALLOTER

#include "alloter_interface.h"

namespace cppnet {

class NormalAlloter : public Alloter {
public:
    NormalAlloter();
    ~NormalAlloter() override;

    void* Malloc(uint32_t size) override;
    void* MallocAlign(uint32_t size) override;
    void* MallocZero(uint32_t size) override;

    void Free(void* &data, uint32_t len = 0);
};

std::shared_ptr<NormalAlloter> MakeNormalAlloterPtr();

}

#endif 