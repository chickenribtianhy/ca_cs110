#include <iostream>
using namespace std;
int main()
{
    bool ans = 1 ? 0 : 0 ? 0
                         : 1; // =0
    cout << ans << endl;
    return 0;
}