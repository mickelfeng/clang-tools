#include<iostream>
#include<functional>
#include<algorithm>
#include<numeric>
#include<vector>
#include<iterator>


//´óÊıÔËËã

using namespace std;

typedef vector<int> BigInt;
int carry(int curr, int prev)
{
	return curr + (prev / 10);
}

BigInt & operator*=(BigInt& bi, int m)
{
	transform(bi.begin(), bi.end(), bi.begin(), bind2nd(multiplies<int>(), m));
	if(bi.back() > 9)
		bi.push_back(0);

	adjacent_difference(bi.begin(), bi.end(), bi.begin(), ptr_fun(&carry));
	transform(bi.begin(), bi.end(), bi.begin(), bind2nd(modulus<int>(), 10));
	return bi;
}

int main(int argc, char * argv[])
{

	BigInt bigInteger;
	int base =2;
	int powNum = 10000;
	bigInteger.push_back(base);

	int loop = {1};
	while(loop++ < powNum)
		bigInteger *= 2;

	int sum_of_digits = accumulate(bigInteger.begin(), bigInteger.end(), 0);

	std::cout  << base << "**" << powNum << "= " << std::endl;
	copy(bigInteger.rbegin(), bigInteger.rend(), ostream_iterator<int>(cout, ""));
	puts("");
	cout << "\nThe sum of the digits is " << sum_of_digits << "\n";

	return 0;
}
