// Use of this source code is governed by a BSD 3-Clause License
// that can be found in the LICENSE file.

// Author: caozhiyi (caozhiyi5@gmail.com)

#ifndef CPPNET_CPPNET_CONFIGE
#define CPPNET_CPPNET_CONFIGE

#include <string>
#include <cstdint>

namespace cppnet {

// on Linux, we have two ways to avoid thundering herd:
// 1. use TCP flag reuse port flag, multi socket listen to one same port.
// 2. only use one socket but set EPOLLEXCLUSIVE flag when add to EPOLL.(require Linux Kernal > 4.5)

// use reuse port TCP flag. must set true on windows and macOS.
static const bool __reuse_port             = true;
// use EPOLLEXCLUSIVE flag. must set false on windows and macOS.
static const bool __epoll_exclusive        = !__reuse_port;

// size of block memory in block memory pool.
static const uint16_t __mem_block_size     = 1024;
// how many block memory will be add to block memory pool.
static const uint16_t __mem_block_add_step = 5;
// max number of blocks in memory pool. If block memory more than this number, will reduce to half.
static const uint16_t __max_block_num      = 20;
// max data to write when net is busy.
static const uint32_t __max_write_cache    = 1024 * 1024 * 4;

// log level. 
static const uint16_t __log_level          = 31; // info level
// log file name.
static const std::string __log_file_name   = "cppnet_log";
// open log print.
static const bool __print_log              = true;

// EPOLL use et model.
static const bool __epoll_use_et                   = true;
// the start extend size of read buff while buff isn't enough. 
static const uint16_t __linux_read_buff_expand_len = 4096;
// max extend size of read buff while buff isn't enough. 
static const uint32_t __linux_read_buff_expand_max = 65536;
// max size of buffer will get from buffer. Be careful IOV_MAX.
static const uint16_t __linux_write_buff_get       = 4096;
// waiting time to re detect the connection status when connecting
static const uint16_t __connect_recheck_time_ms    = 2000;

// IOCP buffer length.
static const uint16_t __iocp_buff_size        = 1024*4;
// number of IOCP accept event post when first call accept
static const uint16_t __iocp_accept_event_num = 20;


}

#endif
