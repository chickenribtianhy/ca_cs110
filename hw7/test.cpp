#include "ringbuffer.hpp"
#include <iostream>
#include <vector>
using namespace __detail;
using namespace std;

int main()
{
    RingBuffer<int> mbuffer;
    std::vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // buffer.print();
    /*buffer.write(b[0]);
    buffer.print();*/
    std::vector<int> a(10);
    mbuffer.write_multi(10, b);
    mbuffer.print();
    // std::cout << buffer.get_capacity() << std::endl;
    // buffer.read_multi(3, a);
    // buffer.write(c[0]);
    // buffer.print();
    /* buffer.print();
    buffer.write(b[0]);
    buffer.print();
    /*size_t cap = buffer.get_capacity();
    std::cout << cap << std::endl;

    std::vector<int> a(7);
    bool flag = buffer.read_multi(10, a);
    // buffer.print();
    std::cout << flag << std::endl;
    /*for (int i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << std::endl;
    }
    std::cout << a.size() << std::endl;*/

    /*bool empty = buffer.is_empty();
    std::cout << empty << std::endl;*/

    // auto i = buffer.begin();
    // cout << "begin:\t";
    // i.print();
    // cout << "end:\t";
    // buffer.end().print();
    // cout << "i++\t";
    // (i++).print();
    // cout << "++i\t";
    // (++i).print();
    // cout << "i\t";
    // i.print();
    // cout << "i+1\t";
    // (i + 1).print();

    for (auto i = mbuffer.begin(); i != mbuffer.end(); i++)
    {
        std::cout << *i << " ";
        i.print();
    }
    std::cout << std::endl;
    /*for (__iterator<int> i = buffer.end() - 1; i != buffer.begin() - 1; --i)
    {
        std::cout << *i << "\n";
    }*/

    __detail::__iterator<int> ring2 = mbuffer.begin();
    ring2.print();
    ring2++;
    ring2.print();
    mbuffer.end().print();
    return 0;
}