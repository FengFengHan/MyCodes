#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int K;
	int A[10000];
	cin >> K;
	for(int i = 0;i <K;++i){
		cin >> A[i];
	}
	int dp[10000];
	for(int i = 0; i < K;++i){
		dp[i] = A[i];
	}
	int maxSum = dp[0];
	int maxSumPos = 0;
	for(int i = 1;i <K;++i){
		if(dp[i-1] > 0){
			dp[i] += dp[i-1];
		}
		if(dp[i] > maxSum){
			maxSum = dp[i];
			maxSumPos = i;
		}
	}
	if(maxSum < 0){
		cout << 0 << " " << A[0] << " " << A[K - 1];
	}else{
		int startPos = 0;
		for(int i = maxSumPos;i >= 0;--i){
			if(dp[i] < 0){
				startPos = i + 1;
				break;
			}
		}
		cout << maxSum << " " << A[startPos] << " " << A[maxSumPos];
	}
}