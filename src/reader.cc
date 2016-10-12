#include"reader.h"
#include<stdio.h>

const string Reader::path = "../files/";

static int errorcode;

enum read_file_type {
	UNDONE,
	DONE,
	ALL
};

void error(int code)
{
	errorcode = code;
}

static int has_dotdot(string filename)
{
	const char *it;
	int n;

	n = 0;
	it = filename.data();
	while (*it != '\0') {
		if (*it == '.') {
			n++;
		} else {
			n = 0;
		}
		if (n == 2) {
			return true;
		}
		it += sizeof(char);
	}
	return false;
}


Reader::Reader(string file, int type)
{
	if ((file.back() == '/' || has_dotdot(file)) && type) {
		error(WRONG_FILENAME);
	} else {
		errorcode = NO_ERROR;
		filename = file;
	}
	this->type = type;
}

Reader::~Reader()
{
}

int Reader::get_error()
{
	return errorcode;
}

string Reader::get_filename()
{
	return filename;
}

static int get_tabs(string s)
{
	int i;
	i = 0;
	while (s[i] == '\t' && s[i] != '\0') {
		i++;
	}
	return i;
}


static int is_done(string *s)
{
	int i;
	i = get_tabs(*s);

	if ((*s)[i] != '!') {
		return UNDONE;
	}

	s->erase(i,1);
	s->insert(i, "(done) ");

	return DONE;
}

static void remove_enters(string *out)
{
	while (out->back() == '\n') {
		out->pop_back();
	}
}

static void read_lines(ifstream *s, string *out, int type)
{
	int done;
	string current;

	while (!s->eof() && out->size() + 100 < out->max_size()) {
		std::getline(*s, current);
		done = is_done(&current);
		if (done == type || type == ALL) {
			*out += current + '\n';
		}
	}
}

static string read_lines_recursive(ifstream *s, string *last,
		int tabs)
{
	int next_tabs;
	string current, str_this, str_title, temp;

	current = *last;

	while (!s->eof() &&
			(next_tabs = get_tabs(current)) >= tabs) {
		if (next_tabs > tabs) {
			*last = current;
			temp = read_lines_recursive(s, last,
					next_tabs);
			if (temp.size() != 0) {
				str_this += str_title +
					temp;
			}
			current = *last;
		}
		else if (next_tabs == tabs) {
			if (is_done(&current)) {
				str_this += current + '\n';
				str_title = "";
			} else {
				str_title = current + '\n';
			}
			std::getline(*s, current);
		}
	}

	*last = current;
	return str_this;
}

static ifstream *open_file(string file)
{
	ifstream *s;
	s = new ifstream();
	s->open(file.c_str());
	return s;
}

static string *read_file(string file, int type)
{
	string *current;
	string *out;
	ifstream *s;

	s = open_file(file);

	if (!s->is_open()) {
		error(OPEN_FILE_ERROR);
		return NULL;
	}

	out = new string();
	current = new string();

	if (type == DONE) {
		std::getline(*s, *current);
		*out = read_lines_recursive(s, current, 0);
	} else if (type == UNDONE || type == ALL) {
		read_lines(s, out, type);
	}

	remove_enters(out);

	s->close();
	delete s;
	delete current;
	return out;
}

string *Reader::all()
{
	if (type == 0) {
		return read_file(filename, ALL);
	} else {
		return read_file(path + filename, ALL);
	}
}

string *Reader::undone()
{
	if (type == 0) {
		return read_file(filename, UNDONE);
	} else {
		return read_file(path + filename, UNDONE);
	}
}

string *Reader::done()
{
	if (type == 0) {
		return read_file(filename, DONE);
	} else {
		return read_file(path + filename, DONE);
	}
}
