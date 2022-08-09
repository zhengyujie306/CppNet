#include <iostream>

#include "common/timer/timer.h"
#include "common/util/time.h"
#include "sys/epoll.h"

#include <unistd.h>

int main() {
    auto timer = cppnet::MakeTimer1Min();
    std::cout << timer->CurrentTimer() << '\n';
    std::cout << timer->MinTime() << '\n';
    timer->TimerRun(65);
    std::cout << timer->CurrentTimer() << '\n';
    std::cout << cppnet::UTCTimeMsec() << '\n';

    int ep = epoll_create(1024);
    if(ep == -1){
        printf("create epoll error!\n"); exit(-1);
    }

    for(int i = 0; i < 2 * 60 * 60 * 1000; i += 1000){
        auto start = cppnet::UTCTimeMsec();

        epoll_event events[1];
        if(epoll_wait(ep, events, 1, i) == -1){
            std::cout <<"wait epoll error!\n";
        }

        auto end = cppnet::UTCTimeMsec();
        std::cout << "epoll wait timeout = " << end - start << "(ms)\n";
    }

    close(ep);




    return 0;
}

// There are some problem in BitMap class, Or I misunderstand the design.