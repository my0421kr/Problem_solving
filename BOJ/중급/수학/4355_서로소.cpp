#include <iostream>
#include <vector>
using namespace std;

int n;
int sieve[40000];
vector<int> prime;

void MakeSieve()
{
    for(int i=2; i<40000; i++) {
        if(sieve[i] == 0) {
            for(int j=i*2; j<40000; j+=i) {
                sieve[j] = 1;
            }
        }
    }
}

int main()
{
    MakeSieve();

    while(1) {
        scanf("%d", &n);
        if(n == 0) {
            break;
        }
        prime.clear();
        int answer = 1;
        int start = n;
        for(int i=2; i*i<=start; i++) {
            if(sieve[i] == 0 && start % i == 0) {
                prime.push_back(i);
                while(start % i == 0) {
                    start /= i;
                }
            }
        }
        if(start != 1) {
            prime.push_back(start);
        }
        int len = prime.size();
        for(int i=0; i<len; i++) {
            answer *= (prime[i] - 1);
            n /= prime[i];
        }
        printf("%d\n", answer*n);
    }
}