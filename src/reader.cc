#include"reader.h"
using namespace std;

Reader::Reader(const char *file)
{
	int n, i;
	n = 0;
	i = 0;
	while (file[i] != '\0') {
		if (file[i] == '.') {
			n++;
		} else {
			n = 0;
		}
		if (n == 2) {
			filename = (char *)calloc(1, sizeof(char));
			*filename = '\0';
			return;
		}
		i++;
	}
	int length;
	length = strlen(file);
	filename = (char *)calloc(length, sizeof(char));
	strcpy(filename, file);
}

Reader::~Reader()
{
	free(filename);
}

char *Reader::all()
{
	fstream s;
	s.open(filename);
	char *ret;
	ret = (char *)malloc(1);
	*ret = '\0';
	return ret;
}
