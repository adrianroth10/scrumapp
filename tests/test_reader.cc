#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"reader.h"
#include<iostream>

using namespace std;

void test_constructor();
void test_get_filename();
void test_all();
void test_done();

int main ()
{
	test_constructor();
	test_get_filename();
	test_all();
	test_done();
	return 0;
}

void test_constructor()
{
	Reader r("test/functioning");
	assert(r.get_error() == 0);

	Reader r2("../error");
	assert(r2.get_error() == 1);

	Reader r3("test/error/");
	assert(r3.get_error() == 1);
}

void test_get_filename()
{
	Reader r("test/functioning");
	assert(r.get_filename().compare("test/functioning") == 0);

	Reader r2("../error");
	assert(r2.get_filename().compare("") == 0);

	string change = "first";
	Reader r3(change);
	change = "second";
	assert(r3.get_filename().compare("first") == 0);

	Reader r4("manipulating");
	string man = r4.get_filename();
	man = "not_working";
	assert(r4.get_filename().compare("manipulating") == 0);
}

void test_all()
{
	Reader read("tests/sprint_2016_03_18");
	string result, correct;
	result = read.all();
	correct = "\
plugg\n\
	kurs 1\n\
		övning\n\
			uppgift 1, uppgift 2, uppgift 3\n\
	kurs 2\n\
		laboration\n\
			(done) förbredelser\n\
			utförande\n\
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

	assert(result.compare(correct) == 0);
}

void test_done()
{
	Reader read("tests/sprint_2016_03_18");
	string result, correct;
	result = read.done();
	correct = "\
plugg\n\
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

	assert(result.compare(correct) == 0);
}

void test_undone()
{
	Reader read("tests/sprint_2016_03_18");
	string result, correct;
	result = read.undone();
	correct = "\
plugg\n\
	kurs 1\n\
		övning\n\
			uppgift 1, uppgift 2, uppgift 3\n\
	kurs 2\n\
		laboration\n\
			utförande\n\
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

	assert(result.compare(correct) == 0);
}
