#include"reader.h"
#include<dirent.h>
#include<errno.h>
#include<iostream>
#include<string>
#include<sys/types.h>
#include<vector>

using namespace std;

int getdir (string dir, vector<string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp  = opendir(dir.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

int main(int argc, char *argv[])
{
	char in[50];
	string *result;


	if (argc == 2) {
		snprintf(in, 50, "./%s", argv[1]);
	} else if (argc == 1) {
		// If there are no arguments assume to look at the "usual" file
		vector<string> dir;
		getdir("/home/rotharen/scrum", dir);
		for (unsigned int i = 0; i < dir.size(); i++) {
			string temp = dir[i];
			if (temp.substr(0, 7).compare("sprintb") == 0){
				snprintf(in,
					 50,
					 "/home/rotharen/scrum/%s",
					 temp.c_str());
			}
		}
	} else {
		cout << "Error, unexpected number of parameters\n";
		return 1;
	}

	Reader r(in, 0);
	result = r.undone();
	if (result != NULL) {
		cout << *result << '\n';
		delete result;
	} else {
		cout << "Error\n";
	}
	return 0;
}
