#ifndef READER_H
#define READER_H

#include<fstream>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<string.h>

using std::string;
using std::ifstream;

class Reader
{
	private:
		string filename;
		static const string path;
		int errortype;
		void error(int type);
		string read_file(ifstream *s);
		int done_check(char *s);
	public:
		Reader(string file);
		~Reader();
		int get_error();
		string get_filename();
		string all();
		string done();
		string undone();
};

#endif
