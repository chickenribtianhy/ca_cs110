#ifndef __RING_BUFFER_I
#define __RING_BUFFER_I

/* Create a new ring buffer, defalut. */
template <typename _Tp>
RingBuffer<_Tp>::RingBuffer()
{
    _M_capacity = RING_BUFFER_INIT_SIZE;
    // _M_read_pos = -1;
    _M_read_pos = 0;  // immediate read
    _M_write_pos = 0; // immediate write
    _M_content = new _Tp[RING_BUFFER_INIT_SIZE];
    // _M_content = (_Tp *)malloc(RING_BUFFER_INIT_SIZE * sizeof(_Tp));
}

/* Destroy the given ring buffer, free all resources allocated.*/
template <typename _Tp>
RingBuffer<_Tp>::~RingBuffer()
{
    delete[] _M_content; // free
}

template <typename _Tp>
size_t RingBuffer<_Tp>::get_capacity() const
{
    return _M_capacity; // return the capacity of the buffer
}

/* Returns true if the given ring buffer is empty, false otherwise */
template <typename _Tp>
bool RingBuffer<_Tp>::is_empty() const
{
    //  since both head and tail are the ready positions,
    // the buffer appears empty as head==tail, just as in the initialization
    return _M_read_pos == _M_write_pos;
}

/* Read an element from the ring buffer.*/
template <typename _Tp>
bool RingBuffer<_Tp>::read(_Tp &data)
{
    /* if the buffer is empty then we can read nothing from it */
    if (is_empty())
        return false;
    data = _M_content[_M_read_pos];
    /* the buffer is a cycle, and we should ensure the position < capacity */
    _M_read_pos = (_M_read_pos + 1) % _M_capacity; // cycle
    return true;
}

/* Read "rdsize" elements from the ring buffer, and fill them to "data".*/
template <typename _Tp>
bool RingBuffer<_Tp>::read_multi(size_t rdsize, std::vector<_Tp> &data)
{
    if (rdsize != data.size())
        data.resize(rdsize);
    if (rdsize > (_M_write_pos - _M_read_pos) % _M_capacity) // cycle
        return false;
    for (size_t i = 0; i < rdsize; ++i)
    {
        if (!read(data[i])) // if fail
            return false;
    }
    return true; // return true
}

/* this is a static function that helps to expand the capacity of the buffer */
/* Grows the ringbuffer _M_capacity according to the growth factor */
template <typename _Tp>
void RingBuffer<_Tp>::grow()
{
    size_t new_capacity;
    if (_M_capacity < 1024)
        new_capacity = _M_capacity * RING_BUFFER_GROW_FACTOR1; // grow by factor1
    else
        new_capacity = _M_capacity * RING_BUFFER_GROW_FACTOR2; // grow by factor2
    _Tp *new_content = new _Tp[new_capacity];                  // start a new
    for (size_t i = 0; i < _M_capacity; ++i)
        new_content[i] = _M_content[(_M_read_pos + i) % _M_capacity]; // cycle
    _M_read_pos = 0;                                                  // re-initialize
    _M_write_pos = _M_capacity;                                       // re-initialize
    delete[] _M_content;                                              // free
    _M_content = new_content;                                         // cover
    _M_capacity = new_capacity;
}

/* Write an element which value is `data` to the ring buffer. */
template <typename _Tp>
bool RingBuffer<_Tp>::write(const _Tp &data)
{
    _M_content[_M_write_pos] = data;
    _M_write_pos = (_M_write_pos + 1) % _M_capacity; // cycle
    if (_M_read_pos == _M_write_pos)
        grow();
    return true; // return, always true indeed
}

/* Write "wrtsize" elements to the ring buffer. The values to write are provided in "data". */
template <typename _Tp>
bool RingBuffer<_Tp>::write_multi(size_t wrtsize, const std::vector<_Tp> &data)
{
    if (wrtsize > data.size())
        return false;                    // the only false case to take care of
    for (size_t i = 0; i < wrtsize; ++i) // traverse
    {
        if (!write(data[i]))
            return false; // fail
    }
    return true; // return true
}

/* Write "wrtsize" elements to the ring buffer. The values to write are provided in "data". */
template <typename _Tp>
bool RingBuffer<_Tp>::map(std::function<_Tp(_Tp)> &&func)
{
    size_t i = _M_read_pos;
    while (i != _M_write_pos) // traverse
    {
        _M_content[i] = func(_M_content[i]);
        i = (i + 1) % _M_capacity; // cycle
    }
    return true; // return, always true indeed
}

// ===============================================================================================================
// iterator
template <typename _Tp>
class __detail::__iterator
{
public:
    __iterator() // default constructor
    {
        _m_ptr = nullptr;
        _m_buffer = nullptr;
    }

    __iterator(const __iterator &other) // copy constructor
    {
        _m_ptr = other._m_ptr;       // take present location
        _m_buffer = other._m_buffer; // take the buffer pointer
    }

    __iterator(_Tp *ptr, RingBuffer<_Tp> *buffer) // init constructor
    {
        _m_ptr = ptr;       // take present location
        _m_buffer = buffer; // take the buffer pointer
    }

    ~__iterator() {} // destructor

    __iterator &operator=(const __iterator &iter) // assignment
    {
        _m_ptr = iter._m_ptr;       // take present location
        _m_buffer = iter._m_buffer; // take the buffer pointer
        return *this;
    }

    _Tp &operator*() const // pointer content
    {
        return *_m_ptr;
    }

    _Tp *operator->() const // dereference
    {
        return _m_ptr;
    }

    bool operator==(const __iterator &iter) const // equal
    {
        return _m_ptr == iter._m_ptr && _m_buffer == _m_buffer;
    }

    bool operator!=(const __iterator &iter) const // not equal
    {
        return _m_ptr != iter._m_ptr || _m_buffer != _m_buffer;
    }

    __iterator operator++(int) // i++
    {
        __iterator tmp = *this;
        _m_ptr++;
        if (_m_ptr >= _m_buffer->_M_content + _m_buffer->_M_capacity)
            _m_ptr = _m_ptr - _m_buffer->_M_capacity;
        return tmp; // return former one
    }
    __iterator &operator++() // ++i
    {
        _m_ptr++;
        if (_m_ptr >= _m_buffer->_M_content + _m_buffer->_M_capacity)
            _m_ptr = _m_ptr - _m_buffer->_M_capacity;
        return *this; // return new
    }

    __iterator operator--(int) // i--
    {
        __iterator tmp = *this;
        _m_ptr--;
        if (_m_ptr < _m_buffer->_M_content)
            _m_ptr = _m_ptr + _m_buffer->_M_capacity;
        return tmp; //return former one
    }
    __iterator &operator--() // --i
    {
        _m_ptr--;
        if (_m_ptr < _m_buffer->_M_content)
            _m_ptr = _m_ptr + _m_buffer->_M_capacity;
        return *this; // return new
    }

    __iterator operator+(const size_t &num) // add
    {
        __iterator tmp = *this;
        for (size_t i = 0; i < num; ++i)
            ++tmp; // use ++ for simplicity
        return tmp;
    }

    __iterator operator-(const size_t &num) // sub
    {
        __iterator tmp = *this;
        for (size_t i = 0; i < num; ++i)
            --tmp; // use -- for simplicity
        return tmp;
    }

    __iterator &operator+=(const size_t &num) // add and assign
    {
        for (size_t i = 0; i < num; ++i)
            ++(*this); // use ++ for simplicity
        return *this;
    }

    __iterator &operator-=(const size_t &num) // sub and assign
    {
        for (size_t i = 0; i < num; ++i)
            --(*this); // use -- for simplicity
        return *this;
    }

    void print()
    {
        std::cout << "iterator:\tptr_" << _m_ptr << "\tbuffer_" << _m_buffer << std::endl;
    }

private:
    _Tp *_m_ptr;                // present location pointed
    RingBuffer<_Tp> *_m_buffer; // denote which buffer
};

// ===============================================================================================================
// const iterator
template <typename _Tp>
class __detail::__const_iterator
{
public:
    __const_iterator() // default constructor
    {
        _m_ptr = nullptr;
        _m_buffer = nullptr;
    }

    __const_iterator(const __const_iterator &other) // copy constructor
    {
        _m_ptr = other._m_ptr;       // take present location
        _m_buffer = other._m_buffer; // take the buffer pointer
    }

    __const_iterator(_Tp *ptr, RingBuffer<_Tp> *buffer) // init constructor
    {
        _m_ptr = ptr;       // take present location
        _m_buffer = buffer; // take the buffer pointer
    }

    ~__const_iterator() {} // destructor

    __const_iterator &operator=(const __const_iterator &iter) // assignment
    {
        _m_ptr = iter._m_ptr;       // take present location
        _m_buffer = iter._m_buffer; // take the buffer pointer
        return *this;
    }

    _Tp &operator*() const // pointer content
    {
        return *_m_ptr;
    }

    _Tp *operator->() const // dereference
    {
        return _m_ptr;
    }

    bool operator==(const __const_iterator &iter) const // equal
    {
        return _m_ptr == iter._m_ptr && _m_buffer == _m_buffer;
    }

    bool operator!=(const __const_iterator &iter) const // not equal
    {
        return _m_ptr != iter._m_ptr || _m_buffer != _m_buffer;
    }

    __const_iterator operator++(int) // i++
    {
        __const_iterator tmp = *this;
        _m_ptr++;
        if (_m_ptr >= _m_buffer->_M_content + _m_buffer->_M_capacity)
            _m_ptr = _m_ptr - _m_buffer->_M_capacity;
        return tmp; // return former one
    }
    __const_iterator &operator++() // ++i
    {
        _m_ptr++;
        if (_m_ptr >= _m_buffer->_M_content + _m_buffer->_M_capacity)
            _m_ptr = _m_ptr - _m_buffer->_M_capacity;
        return *this; // return new
    }

    __const_iterator operator--(int) // i--
    {
        __const_iterator tmp = *this;
        _m_ptr--;
        if (_m_ptr < _m_buffer->_M_content)
            _m_ptr = _m_ptr + _m_buffer->_M_capacity;
        return tmp; //return former one
    }
    __const_iterator &operator--() // --i
    {
        _m_ptr--;
        if (_m_ptr < _m_buffer->_M_content)
            _m_ptr = _m_ptr + _m_buffer->_M_capacity;
        return *this; // return new
    }

    __const_iterator operator+(const size_t &num) // add
    {
        __const_iterator tmp = *this;
        for (size_t i = 0; i < num; ++i)
            ++tmp; // use ++ for simplicity
        return tmp;
    }

    __const_iterator operator-(const size_t &num) // sub
    {
        __const_iterator tmp = *this;
        for (size_t i = 0; i < num; ++i)
            --tmp; // use -- for simplicity
        return tmp;
    }

    __const_iterator &operator+=(const size_t &num) // add and assign
    {
        for (size_t i = 0; i < num; ++i)
            ++(*this); // use ++ for simplicity
        return *this;
    }

    __const_iterator &operator-=(const size_t &num) // sub and assign
    {
        for (size_t i = 0; i < num; ++i)
            --(*this); // use -- for simplicity
        return *this;
    }

    // void print() const
    // {
    //     std::cout << "iterator:\tptr_" << _m_ptr << "\tbuffer_" << _m_buffer << std::endl;
    // }

    // private:
    _Tp *_m_ptr;                      // present location pointed
    const RingBuffer<_Tp> *_m_buffer; // denote which buffer
};

// ===============================================================================================================
/* The iterator is used to interate through the ringbuffer. By iterating through the ring buffer, it means start from the oldest element in the ring buffer (i.e. the element pointed by "_M_read_pos"), to the latest one. end() should return the slot after the last element. You can refer to standart library for more info  */
template <typename _Tp>
typename RingBuffer<_Tp>::iterator RingBuffer<_Tp>::begin()
{
    iterator tmp(_M_content + _M_read_pos, this); // init constructor, with readpos
    return tmp;
}

/* The iterator is used to interate through the ringbuffer. By iterating through the ring buffer, it means start from the oldest element in the ring buffer (i.e. the element pointed by "_M_read_pos"), to the latest one. end() should return the slot after the last element. You can refer to standart library for more info  */
template <typename _Tp>
typename RingBuffer<_Tp>::iterator RingBuffer<_Tp>::end()
{
    iterator tmp(_M_content + _M_write_pos, this); // init constructor, with writepos
    return tmp;
}

// Const iterators
template <typename _Tp>
typename RingBuffer<_Tp>::const_iterator RingBuffer<_Tp>::cbegin() const
{
    // const_iterator tmp(_M_content + _M_read_pos, this); // init constructor, with readpos
    const_iterator tmp; // init constructor, with readpos
    tmp._m_ptr = _M_content + _M_read_pos;
    tmp._m_buffer = this; // const to const
    return tmp;
}

// Const iterators
template <typename _Tp>
typename RingBuffer<_Tp>::const_iterator RingBuffer<_Tp>::cend() const
{
    // const_iterator tmp(_M_content + _M_write_pos, this); // init constructor, with writepos
    const_iterator tmp; // init constructor, with readpos
    tmp._m_ptr = _M_content + _M_write_pos;
    tmp._m_buffer = this; // const to const
    return tmp;
}

#endif
