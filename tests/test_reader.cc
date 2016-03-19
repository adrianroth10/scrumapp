#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"reader.h"

void test_all ();

int main ()
{
	test_all();
	return 0;
}

void test_all ()
{
	Reader read("tests/sprint_2016_03_18");
	char *result, *correct;
	result = read.all();
	correct = (char *)calloc(512, sizeof(char));
	strcpy(correct, "\
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
");

	assert(strcmp(result, correct) == 0);
	free(result);
	free(correct);
}
