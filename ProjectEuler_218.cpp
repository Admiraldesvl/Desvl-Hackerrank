#include <iostream>
#include <cmath>
// Not finished yet. This code can only pass case #0,#1,#2,#3
using namespace std;

inline unsigned long long approSquare(const unsigned long long &num){
    auto root = static_cast<unsigned long long>(sqrt(num));
    return root * root;
}

// https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/
unsigned long long GCD(unsigned long long u, unsigned long long v)
{
    unsigned long long shift;
    if(u==0) return v;
    if(v==0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            unsigned long long t = v;
            v = u;
            u = t;
        }
        v -= u;
    } while (v != 0);
    return u << shift;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    unsigned long q;
    unsigned long long n;
    cin >> q;
    while (q--) {
        cin >> n;
        auto perfect = 0;
        auto superPerfect = 0;
        for (unsigned long long i = 5; i * i <= n; i++) {
            unsigned long long apprSqr = approSquare(i * i - 1);
            unsigned long long restSqr = approSquare(i * i - apprSqr);
            if (!(apprSqr + restSqr == i * i && GCD(apprSqr, restSqr) == 1 && GCD(restSqr, i * i) == 1)) {
                continue;
            }
            perfect++;
            auto Area = static_cast<unsigned long long >((apprSqr - restSqr)  * sqrt(apprSqr * restSqr));
            if (Area % 84 == 0) {
                superPerfect++;
            }
        }
        cout << perfect - superPerfect << endl;

    }
    return 0;
}
