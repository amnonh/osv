/*
 * memory-console.cc
 *
 *  Created on: Oct 12, 2014
 *      Author: amnon
 */

#include "memory-console.hh"

using namespace std;

namespace console {

memory_console::memory_console() :
    pos(0), size(0), max_out(10000), max_in_chars(10000), out(
        max_out), input(max_in_chars) {
}

void memory_console::write(const char *str, size_t len) {
    WITH_LOCK(lock) {
        out.push(str, len);
    }
}

void memory_console::flush() {
}

bool memory_console::input_ready() {
    return !input.empty();
}

char memory_console::readch() {
    if (input.empty()) {
        return 0;
    }
    return input.pop();
}

std::string memory_console::get_output() {
    stringstream res;
    WITH_LOCK(lock) {
        while (!out.empty()) {
            res << out.pop();
        }
    }
    return res.str();
}

void memory_console::add_input(const std::string& str) {
    WITH_LOCK(lock) {
        for (char c: str) {
            input.push(c);
        }
    }
    _thread->wake();

}


}

