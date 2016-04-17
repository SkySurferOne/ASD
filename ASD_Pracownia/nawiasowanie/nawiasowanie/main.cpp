#include <iostream>
using namespace std;

bool validate(string s) {
	int count = 0;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ')' && count == 0)
			return false;
		if (s[i] == '(')
			count++;
		else
			count--;
	}

	if (count > 0)
		return false;
	return true;
}

int main() {
	string s1 = "(())()(()())";
	string s2 = "(())()(()";
	string s3 = "(())()(())(";
	cout << s1.c_str() << " " << (int) validate(s1) << endl;
	cout << s2.c_str() << " " << (int) validate(s2) << endl;
	cout << s3.c_str() << " " << (int) validate(s3) << endl;

	system("pause");
	return 0;
}