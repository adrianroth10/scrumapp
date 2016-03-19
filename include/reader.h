#ifndef READER_H
#define READER_H

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

class Reader
{
	private:
		char *filename;
		char *path = "../files/";
	public:
		Reader (const char *file);
		~Reader ();
		char *all ();
		char *get_filename();
};

#endif
