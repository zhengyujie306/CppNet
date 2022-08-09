#include <string>
#include <vector>
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

void ConnectFunc(const Handle& handle, uint32_t err) {
    if (err == CEC_SUCCESS) {
        SetNoDelay(handle->GetSocket());
        std::string msg("it is a test message.");
        handle->Write(msg.c_str(), (uint32_t)msg.length());
        handle->Close();

    } else {
        std::cout << " [ConnectFunc] some thing error : " << err << std::endl;
    }
}

void ReadFunc(const Handle& handle, const cppnet::BufferPtr& data, uint32_t len) {
    // print
    char buf[1024] = {0};
    data->Read(buf, 1024);
    std::cout << buf << std::endl;
    cppnet::Sleep(100);
    //handle->Write(buf, len);
}


int main() {

    cppnet::CppNet net;
    net.Init(1);
    net.SetConnectionCallback(ConnectFunc);
    net.SetReadCallback(ReadFunc);

    net.Connection("127.0.0.1", 8921);
    net.Connection("127.0.0.1", 8922);

    Sleep(2000);
}