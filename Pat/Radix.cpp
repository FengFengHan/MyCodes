#include <iostream>
#include <string>
using namespace std;
int getCharValue(char char_){
	return  ((char_ >= 'a' && char_ <= 'z')?(char_ - 'a' + 10): (char_ - '0'));
}

long long int getValue(string digits, long long int radix){
	long long int res = getCharValue(digits[0]);
	for(size_t i = 1;i < digits.size();++i){
		res = res * radix + getCharValue(digits[i]);
	}
	return res;
}

int main()
{
	string N1,N2;
	int tag;
	long long int radix;
	cin >> N1 >> N2 >> tag >> radix;
	if(tag == 2){
		string tmp = N1;
		N1 = N2;
		N2 = tmp;
	}
	long long int value = getValue(N1,radix);
	long long int radixLow = getCharValue(N2[0]);
	//如果N2只有一位数则与进制无关
	if(N2.size() == 1){
		if(radixLow == value){
			cout << (radixLow + 1) << endl;
		}else{
			cout << "Impossible" << endl;
		}
		return 0;
	}
	for(size_t i = 1; i < N2.size();++i){
		if(getCharValue(N2[i]) > radixLow){
			radixLow = getCharValue(N2[i]);
		}
	}
	radixLow += 1;
	long long int radixHigh = value + 1;//是value + 1，而不是value
	long long int mid,value2;
	bool findRadix = false;
	while(radixLow <= radixHigh){
		mid = (radixHigh + radixLow)/2;
		value2 = getValue(N2,mid);
		if(value2 > value){
			radixHigh = mid - 1;
		}else if(value2 < value){
			radixLow = mid + 1;
		}else{
			findRadix = true;
			break;
		}
	}
	if(findRadix){
		cout << mid << endl;
	}else{
		cout << "Impossible" << endl;
	}
	return 0;
}

