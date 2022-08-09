#include <string>
#include <thread>
#include <string>
#include <iostream>

#include "include/cppnet.h"
#include "common/util/time.h"

using namespace cppnet;

#ifdef __win__
#include <winsock2.h>
void SetNoDelay(const uint64_t& sock) {
    int opt = 1;
    int ret = setsockopt(sock, SOL_SOCKET, TCP_NODELAY, (const char*)&opt, sizeof(opt));
}
#else
#include <netinet/tcp.h>
#include <netinet/in.h>
void SetNoDelay(const uint64_t& sock) {
    int optval = 1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
               &optval, static_cast<socklen_t>(sizeof(optval)));
}
#endif


void ReadFunc(const Handle& handle, const cppnet::BufferPtr& data, uint32_t len) {
    // print
    char buf[1024] = {0};
    data->Read(buf, 1024);
    cppnet::Sleep(100);
    handle->Write(buf, len);
    std::cout << "get message: " << buf << " listen port is: " << handle->GetListenPort() << std::endl;
}

void ConnectFunc(const Handle& handle, uint32_t err) {
    if (err == CEC_SUCCESS) {
        SetNoDelay(handle->GetSocket());
        std::cout << handle->GetListenPort() << " port get connect socket: " << handle->GetSocket() << std::endl;

    } else {
        std::cout << "[ConnectFunc] some thing error : " << err << std::endl;
    }
}


int main() {

    cppnet::CppNet net;
    net.Init(1);

    net.SetAcceptCallback(ConnectFunc);
    net.SetReadCallback(ReadFunc);

    net.ListenAndAccept("0.0.0.0", 8921);
    net.ListenAndAccept("0.0.0.0", 8922);

    net.Join();
}