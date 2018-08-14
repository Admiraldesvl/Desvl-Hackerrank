// problem: https://www.hackerrank.com/contests/projecteuler/challenges/euler218/
// Only case #0,1,2,3 passed, while other cases return wrong answers except #9.10, which are timeout.
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

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
    shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) {
            unsigned long long t = v;
            v = u;
            u = t;
        }
        v -= u;
    } while (v != 0);
    return u << shift;
}

void add_perfect(vector<unsigned long long> &nP,vector<unsigned long long> &sP, unsigned long long n){
    decltype(n) begin = nP.empty() ? 5 : nP[nP.size() - 1];
    for (decltype(n) i = begin; i * i <= n; i++) {
        decltype(n) apprSqr = approSquare(i * i - 1);
        decltype(n) restSqr = approSquare(i * i - apprSqr);
        if (!((apprSqr + restSqr == i * i) && GCD(apprSqr, restSqr) == 1 && GCD(restSqr, i * i) == 1)) {
            continue;
        }
        nP.push_back(i * i);
        auto area = static_cast<decltype(n)>((apprSqr - restSqr) * sqrt(apprSqr * restSqr));
        if (area % 84 == 0) {
            sP.push_back(i * i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    unsigned long q;
    unsigned long long n;
    cin >> q;
    vector<decltype(n)> normal_perfect;
    vector<decltype(n)> super_perfect;
    while (q--) {
        cin >> n;
        unsigned long perfect;
        unsigned long superPerfect;
        if(normal_perfect.empty()){
            add_perfect(normal_perfect, super_perfect, n);
            perfect = normal_perfect.size();
            superPerfect = super_perfect.size();
        }else{
            if (approSquare(n) > normal_perfect[normal_perfect.size() - 1]) {
                add_perfect(normal_perfect, super_perfect, n);
                perfect = normal_perfect.size();
                superPerfect = super_perfect.size();
            } else {
                auto nP = lower_bound(normal_perfect.begin(), normal_perfect.end(), n);
                auto sP = lower_bound(super_perfect.begin(), super_perfect.end(), n);
                perfect = static_cast<decltype(perfect)>(distance(normal_perfect.begin(), nP));
                superPerfect = static_cast<decltype(superPerfect)>(distance(super_perfect.begin(), sP));
            }
        }
        cout << perfect - superPerfect << endl;

    }
    return 0;
}
