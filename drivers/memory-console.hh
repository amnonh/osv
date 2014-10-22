/*
 * Copyright (C) 2014 Cloudius Systems, Ltd.
 *
 * This work is open source software, licensed under the terms of the
 * BSD license as described in the LICENSE file in the top-level directory.
 */

#ifndef MEMORY_CONSOLE_DRIVER_HH
#define MEMORY_CONSOLE_DRIVER_HH

#include <functional>
#include <osv/sched.hh>
#include <string>
#include <sstream>
#include <osv/mutex.h>
#include "non_copy_circular_buffer.hh"
#include "console-driver.hh"

namespace console {

class memory_console : public console_driver {
public:
    memory_console();
    virtual ~memory_console() = default;
    virtual void write(const char *str, size_t len);
    virtual void flush();
    virtual bool input_ready();
    virtual char readch();
    std::string get_output();
    void add_input(const std::string& str);
private:
    virtual void dev_start() {};
    virtual const char *thread_name() {
        return "memory";
    };
    int pos;
    int size;
    int max_out;
    int max_in_chars;
    osv::nc_circular_buffer<char> out;
    osv::nc_circular_buffer<char> input;
    std::mutex lock;
};

};

#endif
