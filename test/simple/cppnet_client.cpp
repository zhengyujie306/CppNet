#include <string>
#include <thread>
#include <iostream>

#include "include/cppnet.h"
#include "common/util/time.h"

using namespace cppnet;

int msg_index = 0;
std::string msg = "test msg => ";

std::string GetMsg() {
    msg_index++;
    return (msg + std::to_string(msg_index));
}

void WriteFunc(const Handle& handle, uint32_t len) {
    std::cout << " [WriteFunc]  length : " << len << std::endl;
}


void ReadFunc(const Handle& handle, const std::shared_ptr<Buffer>& data, uint32_t len) {
    std::cout << " [ReadFunc]" << std::endl;

    char buf[1024] = {0};
    data->Read(buf, 1024);
    std::cout << " recv :"<< buf << std::endl;
    data->Clear();

    std::cout << " Thread ID : " << std::this_thread::get_id() << std::endl;
    std::cout << " Read size : " << len << std::endl << std::endl;
    
    Sleep(1000);

    if (msg_index >= 1) {
        //Sleep(1000);
        //handle->Close();
        return;
    }

    auto message = GetMsg();
    handle->Write(message.c_str(), (uint32_t)message.length());
}

void ConnectFunc(const Handle& handle, uint32_t err) {
    if (err == CEC_SUCCESS) {
        std::string ip;
        uint16_t port;
        handle->GetAddress(ip, port);
        std::cout << " [ConnectFunc] : ip : " << ip << "port : " << port << std::endl;
        auto message = GetMsg();
        handle->Write(message.c_str(), (uint32_t)message.length());

    } else {
        std::cout << " [ConnectFunc] some thing error : " << err << std::endl;
    }
}

void DisConnectionFunc(const Handle& handle, uint32_t err) {
    std::cout << " [DisConnectionFunc] : " << err << std::endl;
}

void TimeCallBack(void*) {
    std::cout << "time out!!!\n";
}

int main() {

    cppnet::CppNet net;
    net.Init(1);
    net.SetConnectionCallback(ConnectFunc);
    net.SetWriteCallback(WriteFunc);
    net.SetReadCallback(ReadFunc);
    net.SetDisconnectionCallback(DisConnectionFunc);

    net.Connection("127.0.0.1", 8999);
    //Sleep(8000);
    net.Destory();
}