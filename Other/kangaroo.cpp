#include <iostream>

using namespace std;

typedef  long long LL;

int main() {
    int N;
    while(cin >> N) {
        LL a[11];//a[i]: i岁母袋鼠的个数
        for (int i = 1; i <= 10; ++i) {
            a[i] = 0;
        }
        a[5] = 1;

        LL num = 1;//母袋鼠的个数
        LL valid_num = 1;//可生育的母袋鼠的个数
        LL num_next_year;//下一年母袋鼠的个数
        LL valid_num_next_year;//下一年可生育的母袋鼠的个数
        for (int i = 1; i <= N; ++i) {
            num_next_year = num + valid_num;
            //年龄增长1
            for (int j = 10; j > 1; --j) {
                a[j] = a[j - 1];
            }
            a[1] = valid_num;
            valid_num_next_year = valid_num + (a[4] - a[10]);

            num = num_next_year;
            valid_num = valid_num_next_year;
        }
        cout << num << endl;
    }
    return 0;
}