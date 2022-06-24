#include <iostream>
#include <vector>
#include "ringbuffer.hpp"
int main()
{
    RingBuffer<int> buffer;
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    std::vector<int> vec2 = {0, 0, 0, 0, 0, 0};
    buffer.write_multi(6, vec);
    buffer.print();
    buffer.read_multi(4, vec2);
    for (int i = 0; i < vec2.size(); ++i)
        std::cout << vec2[i] << " ";
    std::cout << std::endl;
    buffer.print();
    return 0;
}