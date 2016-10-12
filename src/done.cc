#include<iostream>
#include"reader.h"

using namespace std;

int main(int argc, char *argv[])
{
	char in[50];
	string *result;

	if (argc == 2) {
		snprintf(in, 50, "./%s", argv[1]);
		Reader r(in, 0);
		result = r.done();
		cout << *result << '\n';
		delete result;
	} else {
		cout << "Error, need file name";
	}
	return 0;
}
