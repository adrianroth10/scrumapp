#include"reader.h"
#include<stdio.h>

const string Reader::path = "../files/";

void Reader::error(int type)
{
	errortype = type;
}

Reader::Reader(string file)
{
	int n, i;
	const char *it;
	n = 0;
	i = 0;
	it = file.data();
	while (it[i] != '\0') {
		if (it[i] == '.') {
			n++;
		} else {
			n = 0;
		}
		if (n == 2) {
			error(1);
			return;
		}
		i++;
	}
	if (it[i-1] == '/') {
		error(1);
		return;
	}
	errortype = 0;
	filename = it;
}

Reader::~Reader()
{
}

int Reader::get_error()
{
	return errortype;
}

string Reader::get_filename()
{
	return filename;
}

int Reader::done_check(char *s)
{
	int i, length;
	char done[] = "(done) ";
	char *temp;
	length = strlen(s);

	i = 0;
	while (s[i] == '\t' && s[i] != '\0') {
		i++;
	}

	if (s[i] != '!') {
		return 0;
	}

	temp = (char *)malloc((length - i + 1) * sizeof(char));
	strncpy(temp, s + i + 1, length - i + 1);
	strncpy(s + i, done, 7);
	memcpy(s + i + 7, temp, length - i + 1);
	free(temp);
	return 1;
}


string Reader::read_file(ifstream *s)
{
	string *out;
	char *current;
	out = new string();
	current = (char *)calloc(100, sizeof(char));

	while (!s->eof() && out->size() + 100 < out->max_size()) {
		s->getline(current, 100);
		done_check(current);
		*out += current;
		*out += '\n';
	}

	while (out->back() == '\n') {
		out->pop_back();
	}
	return *out;
}

string Reader::all()
{
	string out;
	ifstream *s;
	s = new ifstream();
	s->open((path + filename).c_str());
	if (s->is_open()) {
		out = read_file(s);
	}
	s->close();
	s->~ifstream();
	return out;
}

string Reader::done()
{
	string out;
	return out;
}

string Reader::undone()
{
	string out;
	return out;
}
