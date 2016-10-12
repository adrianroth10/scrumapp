#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"reader.h"
#include<iostream>

using namespace std;

void constructor_test();
void get_filename_test();
void all_test();
void undone_test();
void done_test();

int main ()
{
	constructor_test();
	get_filename_test();
	all_test();
	undone_test();
	done_test();
	return 0;
}

void constructor_test()
{
	Reader r("test/functioning", 1);
	assert(r.get_error() == NO_ERROR);

	Reader r2("/test/../error", 1);
	assert(r2.get_error() == WRONG_FILENAME);

	Reader r3("test/error/", 1);
	assert(r3.get_error() == WRONG_FILENAME);
}

void get_filename_test()
{
	Reader r("test/functioning", 1);
	assert(r.get_filename().compare("test/functioning") == 0);

	Reader r2("../error", 1);
	assert(r2.get_filename().compare("") == 0);

	string change = "first";
	Reader r3(change, 1);
	change = "second";
	assert(r3.get_filename().compare("first") == 0);

	Reader r4("manipulating", 1);
	string man = r4.get_filename();
	man = "not_working";
	assert(r4.get_filename().compare("manipulating") == 0);
}

void all_test()
{
	Reader read("tests/sprint_2016_03_18", 1);
	string *result, correct;
	result = read.all();
	correct = "\
plugg\n\
	kurs 1\n\
		laboration\n\
			(done) förbredelser\n\
			utförande\n\
		övning\n\
			uppgift 1, uppgift 2, uppgift 3\n\
	kurs 2\n\
		övning\n\
			uppgift 1\n\
mat\n\
	vilka måltider\n\
		1\n\
		2\n\
		3\n\
	handla\n\
	laga\n\
		1\n\
		2\n\
		3\n\
programmering\n\
	projekt 1\n\
		(done) del 1\n\
		del 2\n\
		del 3\n\
	(done) projekt 2\n\
		(done) finish it\n\
(done) roligt\n\
	(done) party\n\
	(done) party2\n\
	(done) party37\
";

	assert(result->compare(correct) == 0);
	delete result;
}

void undone_test()
{
	Reader read("tests/sprint_2016_03_18", 1);
	string *result, correct;
	result = read.undone();
	correct = "\
plugg\n\
	kurs 1\n\
		laboration\n\
			utförande\n\
		övning\n\
			uppgift 1, uppgift 2, uppgift 3\n\
	kurs 2\n\
		övning\n\
			uppgift 1\n\
mat\n\
	vilka måltider\n\
		1\n\
		2\n\
		3\n\
	handla\n\
	laga\n\
		1\n\
		2\n\
		3\n\
programmering\n\
	projekt 1\n\
		del 2\n\
		del 3\
";

	assert(result->compare(correct) == 0);
	delete result;
}

void done_test()
{
	Reader read("tests/sprint_2016_03_18", 1);
	string *result, correct;
	result = read.done();
	correct = "\
plugg\n\
	kurs 1\n\
		laboration\n\
			(done) förbredelser\n\
programmering\n\
	projekt 1\n\
		(done) del 1\n\
	(done) projekt 2\n\
		(done) finish it\n\
(done) roligt\n\
	(done) party\n\
	(done) party2\n\
	(done) party37\
";

	assert(result->compare(correct) == 0);
	delete result;
}
