#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    string str1 = "223";
    string str2 = "223";

    int len1 = str1.length();
    int len2 = str2.length();
    int t0 = 0;
    int dp[1000] = {0};

    for (int i = 0; i <= len2; ++i)
    {
        dp[i] = 0;
    }
    int save = 0;
    for (int i = 1; i <= len1; ++i)
    {
        for (int j = 1; j <= len2; ++j)
        {
            int tmp = save + 1;
            save = dp[j];
            if (str1[i - 1] == str2[j - 1])
            { // save before change dp[j]

                dp[j] = tmp;
                if (dp[j] > t0)
                {
                    t0 = dp[j];
                }
            }
            else
            {
                dp[j] = 0;
            }
        }
        for (int j = 1; j <= len2; ++j)
            cout << dp[j] << " ";
        cout << endl;
    }
    cout << t0 << endl;

    return 0;
}