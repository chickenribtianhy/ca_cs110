#include <math.h>
template <typename _Tp>
class __detail::__iterator
{
public:
    _Tp *tp;         // interator
    _Tp *end_edge;   // the edge address of the ringbuffer
    _Tp *begin_edge; // the head address of the ringbuffer
    // constructor
    __iterator()
    {
        // initialize all the pointer to nullptr
        tp = nullptr;
        begin_edge = nullptr; // the begin address of the edge
        end_edge = nullptr;   // the edge address of the ringbuffer
    }
    __iterator(const __iterator &other) // constructor
    {
        tp = other.tp;
        begin_edge = other.begin_edge; // the begin address of the edge
        end_edge = other.end_edge;
    }
    __iterator(_Tp *ptr, RingBuffer<_Tp> *buffer) // constructor
    {
        tp = ptr;
        end_edge = buffer->_M_content + buffer->get_capacity(); // get the edge address
        begin_edge = buffer->_M_content;                        // the begin address of the edge
    }
    ~__iterator() {}                             // destructor
    __iterator &operator=(const __iterator &tp1) //= equal
    {
        tp = tp1.tp; // tp=tp
        begin_edge = tp1.begin_edge;
        end_edge = tp1.end_edge; // begin_edge=begin_edge
        return *this;
    }
    _Tp &operator*() //* pointer
    {
        return *tp;
    }
    _Tp *operator->() // dereference
    {
        return tp;
    }
    bool operator==(const __iterator &tp1) const //== equal
    {
        if (tp == tp1.tp) // if tp==tp1
            return true;
        else
            return false; // else return false
    }
    bool operator!=(const __iterator &tp1) const //!= unequal
    {
        if (tp != tp1.tp) // if tp!=tp1
            return true;
        else
            return false; // else return false
    }
    __iterator &operator++() //++ pre_increment
    {
        ++tp;
        if (tp == end_edge)
            tp = begin_edge; // if the iterator is at the edge
        return *this;
    }
    __iterator operator++(int) //++ post_increment
    {
        __iterator temp = *this; // temp=*this
        ++tp;
        if (tp == end_edge)
            tp = begin_edge; // if the iterator is at the edge
        return temp;
    }
    __iterator &operator--() //-- pre_decrement
    {
        --tp;                // tp=tp-1
        if (tp < begin_edge) // if the iterator is at the edge
        {
            tp = end_edge - 1;
        }
        return *this;
    }
    __iterator operator--(int) //-- post_decrement
    {
        __iterator temp = *this; //
        --tp;                    // tp=tp-1
        if (tp < begin_edge)     // if the iterator is at the edge
        {
            tp = end_edge - 1;
        }
        return temp;
    }
    __iterator operator+(const size_t &num) // + add int
    {
        __iterator temp = *this;
        for (size_t i = 0; i < num; i++) // for loop to add int times
        {
            ++temp; //++ implementation
        }
        return temp;
    }
    __iterator operator-(const size_t &num) // - minus int
    {
        __iterator temp = *this;
        for (size_t i = 0; i < num; i++) // for loop to minus int times
        {
            --temp; //-- implementation
        }
        return temp;
    }
    __iterator &operator+=(size_t num) //+= add int to own
    {
        for (size_t i = 0; i < num; i++) // for loop to add
        {
            tp = tp + 1;        //++ implementationS
            if (tp == end_edge) // if the iterator is at the edge
            {
                tp = begin_edge;
            }
        }
        return *this; // return to own pointer
    }
    __iterator &operator-=(size_t num) //-= minus int to own
    {
        for (size_t i = 0; i < num; i++) // for loop to minus
        {
            tp = tp - 1;         //-- implementation
            if (tp < begin_edge) // if the iterator is at the edge
            {
                tp = end_edge - 1;
            }
        }
        return *this; // return to own pointer
    }
};

template <typename _Tp>
class __detail::__const_iterator
{
public:
    _Tp *tp;           // interator
    _Tp *begin_edge;   // the begin address of the edge
    _Tp *end_edge;     // the end address of the edge
    __const_iterator() // constructor
    {
        // initialize all the pointer to nullptr
        tp = nullptr;
        begin_edge = nullptr; // the begin address of the edge
        end_edge = nullptr;
    }
    __const_iterator(const __const_iterator &other) // constructor
    {
        tp = other.tp;
        begin_edge = other.begin_edge;
        end_edge = other.end_edge; // copy the other's pointer
    }
    __const_iterator(_Tp *ptr, RingBuffer<_Tp> *buffer) // constructor
    {
        tp = ptr;
        begin_edge = buffer->_M_content;                       // get the begin address of the edge
        end_edge = buffer->_M_content + (buffer->_M_capacity); // get the end address of the edge
    }
    ~__const_iterator() {}                                   // destructor
    __const_iterator &operator=(const __const_iterator &tp1) //= equal
    {
        tp = tp1.tp; // tp=tp
        begin_edge = tp1.begin_edge;
        end_edge = tp1.end_edge; // begin_edge=begin_edge
        return *this;            // return to own pointer
    }

    const _Tp &operator*() //* pointer
    {
        return *tp;
    }
    const _Tp *operator->() // dereference
    {
        return tp;
    }
    bool operator==(const __const_iterator &tp1) const //== equal
    {
        if (tp == tp1.tp)
            return true;
        else
            return false; // else return false
    }
    bool operator!=(const __const_iterator &tp1) const //!= unequal
    {
        if (tp != tp1.tp) // if the address is unequal
            return true;
        else
            return false;
    }
    __const_iterator &operator++() //++ pre_increment
    {
        ++tp;
        if (tp == end_edge)
            tp = begin_edge; // if the address is out of range
        return *this;
    }
    __const_iterator operator++(int) //++ post_increment
    {
        __const_iterator temp = *this;
        ++tp;
        if (tp == end_edge)
            tp = begin_edge; // if the iterator is at the edge
        return temp;
    }
    __const_iterator &operator--() //-- pre_decrement
    {
        --tp;                // tp=tp-1
        if (tp < begin_edge) // if the iterator is at the edge
        {
            tp = end_edge - 1;
        }
        return *this; // return to own pointer
    }
    __const_iterator operator--(int) //-- post_decrement
    {
        __const_iterator temp = *this; //
        --tp;                          // tp=tp-1
        if (tp < begin_edge)           // if the iterator is at the edge
        {
            tp = end_edge - 1;
        }
        return temp;
    }
    __const_iterator operator+(const size_t &num) // + add int
    {
        __const_iterator temp = *this;
        for (size_t i = 0; i < num; i++) // for loop to add int times
        {
            ++temp; //++ implementation
        }
        return temp;
    }
    __const_iterator operator-(const size_t &num) // - minus int
    {
        __const_iterator temp = *this;
        for (size_t i = 0; i < num; i++) // for loop to minus int times
        {
            --temp; //-- implementation
        }
        return temp;
    }
    __const_iterator &operator+=(size_t num) //+= add int to own
    {
        for (size_t i = 0; i < num; i++) // for loop to add
        {
            tp = tp + 1; //++ implementation
            if (tp == end_edge)
            {
                tp = begin_edge; // if the address is out of range
            }
        }
        return *this; // return to own pointer
    }
    __const_iterator &operator-=(size_t num) //-= minus int to own
    {
        for (size_t i = 0; i < num; i++) // for loop to minus
        {
            tp = tp - 1; //-- implementation
            if (tp == begin_edge)
            {
                tp = end_edge; // if the address is out of range
            }
        }
        return *this; // return to own pointer
    }
};

template <typename _Tp>
RingBuffer<_Tp>::RingBuffer() // constructor for ringbuffer
{
    _M_capacity = RING_BUFFER_INIT_SIZE; // initialize capacity to 8
    _M_content = new _Tp[_M_capacity];   // apply for new space
    _M_read_pos = 0;                     // initialize the read pos to 0
    _M_write_pos = 0;                    // initialize the write pos to 0
}

template <typename _Tp>
RingBuffer<_Tp>::~RingBuffer() // destructor for ringbuffer
{
    _M_capacity = 0;   // capacity=0
    _M_read_pos = 0;   // read pos=0
    _M_write_pos = 0;  // write pos=0
    delete _M_content; // delete the content stored in ringbuffer
}

template <typename _Tp>
size_t RingBuffer<_Tp>::get_capacity() const // get the capacity of the ringbuffer
{
    return _M_capacity;
}

template <typename _Tp>
bool RingBuffer<_Tp>::is_empty() const // get if the ringbuffer is empty
{
    if ((_M_read_pos % _M_capacity) == (_M_write_pos % _M_capacity)) // if the content is null or the read pos is equal to the write pos
        return true;
    else
        return false; // return false
}

template <typename _Tp>
void RingBuffer<_Tp>::grow()
{
    size_t can; /*can is the fact capacitiy after expansion*/
    if ((_M_write_pos + 1) % _M_capacity == _M_read_pos)
    {
        if (_M_capacity >= 1024)
            can = _M_capacity * RING_BUFFER_GROW_FACTOR2; /*As the problem we will expand the capacity 1.5 times if it is bigger than or equal to 1024*/
        else
            can = _M_capacity * RING_BUFFER_GROW_FACTOR1; /*If the capacity is smaller than 1024 then its expansion becomes 2 times*/
        _Tp *copy_content, *temp;
        copy_content = new _Tp[can]; // apply for new space
        for (size_t i = 0; i < _M_capacity; i++)
        {
            copy_content[i] = _M_content[(_M_read_pos + i) % _M_capacity]; // copy the content
        }
        temp = _M_content;         // temp is the content before expansion
        _M_content = copy_content; // content is the content after expansion
        _M_read_pos = 0;           /*set the read_pos of the buffer*/
        _M_write_pos = _M_capacity;
        _M_capacity = can;
        delete[] temp; /*Finally we free the space of temp*/
    }
    else
    {
        _M_write_pos = (_M_write_pos + 1) % _M_capacity; /*This condition is that we don't need to expand the capacity*/
    }
}

template <typename _Tp>
bool RingBuffer<_Tp>::read(_Tp &data) // the read implementation
{
    if (is_empty() == true) // if the buffer is empty
        return false;       /*when the read and write are same,there is nothing to read*/
    data = _M_content[_M_read_pos];
    if (_M_read_pos + 1 == _M_capacity) // if the read pos is at the end of the buffer
        _M_read_pos = 0;
    else
    {
        _M_read_pos = _M_read_pos + 1; /*When it add 1 it is also in the same loop*/
    }
    return true;
}

template <typename _Tp>
bool RingBuffer<_Tp>::write(const _Tp &data) // the write implementation
{
    _M_content[_M_write_pos] = data;
    // std::cout << data << "faq" << std::endl;
    grow(); // grow the capacity
    return true;
}

template <typename _Tp>
bool RingBuffer<_Tp>::read_multi(size_t rdsize, std::vector<_Tp> &data) // the read multi implementation
{
    if (rdsize != data.size())
        data.resize(rdsize); // resize the vector
    if (rdsize == 0)         // if the data is empty or the rdsize is 0
        return false;        // if the data is empty,return false
    if ((_M_read_pos <= _M_write_pos) && (_M_read_pos + rdsize > _M_write_pos))
        return false; //
    if ((_M_read_pos > _M_write_pos) && ((_M_read_pos + rdsize) % _M_capacity > _M_write_pos))
        return false;
    for (size_t i = 0; i < rdsize; i++)
    {
        data[i] = _M_content[(_M_read_pos + i) % _M_capacity]; // copy the content to the vector
    }
    _M_read_pos = (_M_read_pos + rdsize) % _M_capacity; // set the read pos
    return true;
}

template <typename _Tp>
bool RingBuffer<_Tp>::write_multi(size_t wrtsize, const std::vector<_Tp> &data) // the write multi implementation
{
    /*if (data.empty() == true)
        return false;*/
    if (wrtsize > data.size())
        return false;
    for (size_t i = 0; i < wrtsize; i++) // for loop to copy the content to the buffer
    {
        write(data[i]); // write the content to the buffer
        // print();
        // std::cout<<"\n";
    }
    return true;
}

template <typename _Tp>
bool RingBuffer<_Tp>::map(std::function<_Tp(_Tp)> &&func) // the map implementation
{
    if (is_empty() == true)
        return false;               // if the buffer is empty,return false
    if (_M_write_pos < _M_read_pos) // if the write pos is smaller than the read pos
    {
        for (size_t i = 0; i < _M_write_pos - _M_read_pos + _M_capacity; i++) // loop through the content
        {
            _M_content[(_M_read_pos + i) % _M_capacity] = func((_M_content[_M_read_pos + i]) % _M_capacity); // apply the function to the content
        }
    }
    else if (_M_write_pos >= _M_read_pos) // if the write pos is bigger than or equal to the read pos
    {
        for (size_t i = 0; i < _M_write_pos - _M_read_pos; i++) // loop through the content
        {
            _M_content[_M_read_pos + i] = func(_M_content[_M_read_pos + i]); // apply the function to the content
        }
    }
    return true;
}

template <typename _Tp>
typename RingBuffer<_Tp>::iterator RingBuffer<_Tp>::begin() // the begin implementation
{
    iterator temp;
    temp.tp = &_M_content[_M_read_pos]; // set the iterator to the content
    temp.begin_edge = _M_content;
    temp.end_edge = _M_content + _M_capacity; // set the begin and end edge
    return temp;
}

template <typename _Tp>
typename RingBuffer<_Tp>::iterator RingBuffer<_Tp>::end() // the end implementation
{
    iterator temp;
    temp.tp = &_M_content[_M_write_pos]; // set the iterator to the content
    temp.begin_edge = _M_content;
    temp.end_edge = _M_content + _M_capacity; // set the begin and end edge
    return temp;
}

template <typename _Tp>
typename RingBuffer<_Tp>::const_iterator RingBuffer<_Tp>::cbegin() const // the cbegin implementation
{
    const_iterator temp;
    temp.tp = &_M_content[_M_read_pos]; // set the iterator to the content
    temp.begin_edge = _M_content;
    temp.end_edge = _M_content + _M_capacity; // set the begin and end edge
    return temp;
}

template <typename _Tp>
typename RingBuffer<_Tp>::const_iterator RingBuffer<_Tp>::cend() const //
{
    const_iterator temp;
    temp.tp = &_M_content[_M_write_pos]; // set the iterator to the content
    temp.begin_edge = _M_content;
    temp.end_edge = _M_content + _M_capacity; // set the begin and end edge
    return temp;
}