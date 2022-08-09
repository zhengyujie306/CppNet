// Use of this source code is governed by a BSD 3-Clause License
// that can be found in the LICENSE file.

// Author: caozhiyi (caozhiyi5@gmail.com)

#include <ostream>
#include <utility>
#include "address.h"

namespace cppnet {

Address::Address():
    Address(AT_IPV6) {

}

Address::Address(AddressType at):
    _address_type(at),    
    _ip(""),           
    _port(0) {
    
}

Address::Address(AddressType at, std::string ip, uint16_t port):
    _address_type(at),
    _ip(std::move(ip)),
    _port(port) {

}

Address::Address(const Address& addr)= default;

Address::~Address() = default;

void Address::SetIp(const std::string& ip) {
    if (_address_type == AT_IPV6) {
        _ip = ToIpv6(ip);
    
    } else {
        _ip = ToIpv4(ip);
    }
}

std::string Address::AsString() {
    if (_address_type == AT_IPV6) {
        return "[" + _ip + "]:" + std::to_string(_port);

    } else {
        return _ip + ":" + std::to_string(_port);
    }
}

std::ostream& operator<< (std::ostream &out, Address &addr) {
    const std::string str = addr.AsString();
    out.write(str.c_str(), str.length());
    return out;
}

bool operator==(const Address &addr1, const Address &addr2) {
    return addr1._ip == addr2._ip && addr1._port == addr2._port && addr1._port != 0;
}

bool Address::IsIpv4(const std::string& ip) {
    if (ip.find(':') == std::string::npos) {
        return true;
    }
    
    return false;
}

std::string Address::ToIpv6(const std::string& ip) {
    if (!IsIpv4(ip)) {
        return ip;
    }
    
    std::string ret("::FFFF:");
    ret.append(ip);
    return ret;
}

std::string Address::ToIpv4(const std::string& ip) {
    if (IsIpv4(ip)) {
        return ip;
    }
    std::size_t pos = ip.rfind(':');

    return {&ip[pos], ip.length() - pos};
}

}