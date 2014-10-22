/*
 * non_copy_circular_buffer.hh
 *
 *  Created on: Oct 13, 2014
 *      Author: amnon
 */

#include <functional>
#include <vector>

namespace osv {

/**
 * A circular buffer implementation that does not uses constructors, nor does it forces
 * assignment to get a new value.
 *
 * It support both const and non const iterator so it can be used with Range-based
 * for loop
 */
template<class T>
class nc_circular_buffer {
public:
    typedef std::vector<T> data_container;
    class iterator;
    class const_iterator;

    nc_circular_buffer(int max, std::function<void(T&)> clear_fun = nullptr) :
        _max(max), _pos(0), _size(0), _data(_max), _clear_fun(clear_fun) {
    }
    T& operator[](int pos) {
        return _data[(_pos - _size + pos) % _max];
    }

    const T& operator[](int pos) const {
        return _data[(_pos - _size + pos) % _max];
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    bool full() const {
        return _size == _max;
    }

    T& pop() {
        T& res = this->operator [](0);
        _size--;
        return res;
    }

    T& next() {
        if (_size < _max) {
            _size++;
        }
        if (_clear_fun != nullptr) {
            _clear_fun(_data[_pos]);
        }
        int pos = _pos;
        _pos++;
        _pos %= _max;

        return _data[pos];
    }

    T& push(const T& val) {
        return (next() = val);
    }

    T& push(const T* val, int len) {
        for (int i = 0; i < len; i++) {
            push(val[i]);
        }
        return this->operator [](0);
    }
    iterator end() {
        return iterator(*this, _max);
    }

    iterator begin() {
        return (_size == 0) ? end() : iterator(*this);
    }

    const_iterator end() const {
        return const_iterator(*this, _max);
    }

    const_iterator begin() const {
        return (_size == 0) ? end() : iterator(*this);
    }

    void foreach(std::function<bool(T&)> f) {
        for (int i = 0; i < _size; i++) {
            if (!f(this->operator [](i))) {
                return;
            }
        }
    }

    class iterator {
        nc_circular_buffer<T>& _data;
        int pos;
    public:
        iterator(nc_circular_buffer<T>& data, int _position = 0) :
            _data(data), pos(_position) {
        }

        T& operator*() {
            return _data[pos];
        }

        iterator& operator++() {
            pos++;
            return *this;
        }

        bool operator!=(const iterator& it) const {
            if (pos >= _data.size() && it.pos >= _data.size()) {
                return false;
            }
            return pos != it.pos;
        }
    };

    class const_iterator {
        const nc_circular_buffer<T>& _data;
        int pos;
    public:
        const_iterator(const nc_circular_buffer<T>& data, int _position = 0) :
            _data(data), pos(_position) {
        }

        const T& operator*() {
            return _data[pos];
        }

        const_iterator& operator++() {
            pos++;
            return *this;
        }

        bool operator!=(const const_iterator& it) const {
            if (pos >= _data.size() && it.pos >= _data.size()) {
                return false;
            }
            return pos != it.pos;
        }
    };
private:
    int _max;
    int _pos;
    int _size;
    data_container _data;
    std::function<void(T&)> _clear_fun;
};

}
