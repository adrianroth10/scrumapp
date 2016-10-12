#ifndef READER_H
#define READER_H

#include<fstream>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<string.h>

using std::string;
using std::ifstream;

enum errorcodes {
	ERROR = -1,
	NO_ERROR,
	WRONG_FILENAME,
	OPEN_FILE_ERROR
};

class Reader
{
	private:
		string filename;
		static const string path;
		int type;
	public:
		Reader(string file, int type);
		~Reader();
		int get_error();
		string get_filename();
		string *all();
		string *undone();
		string *done();
};

#endif
