#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

using namespace std;

void cleanFile(string fileName, int& posCount, string& com, map<string, int>& words);
string RemoveSpecials(string str, map<string, int>& words);
void printTop100(map<string, int> words);

bool sortByVal(const pair<string, int> &a,
               const pair<string, int> &b)
{
    return (a.second > b.second);
}

bool in_array(const string &value, const vector<string> &array)
{
    return find(array.begin(), array.end(), value) != array.end();
}

int main() {
  DIR *dir;
  struct dirent *ent;
  string filename;
  int positiveReviews = 0;
  map<string, int> wordList;
  string com;
  if ((dir = opendir ("reviews")) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      filename = ent->d_name;
      cleanFile(filename, positiveReviews, com, wordList);
      // addToDict(com, wordList);
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }
  cout << "\nTop 100 Words Used in Positive Reviews" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  printTop100(wordList);
  cout << "\n" << endl;
  return 0;
}

void cleanFile(string fileName, int& posCount, string& com, map<string, int>& words) {
  if (fileName[fileName.length()-5] - 48 >= 6 || fileName[fileName.length()-5] - 48 == 0) {
    ifstream inFile;
    string line;
    inFile.open("reviews/" + fileName);
    while(getline(inFile, line)) {
        com = com += line;
    }
    com = RemoveSpecials(com, words);
    posCount++;
  }
}

string RemoveSpecials(string str, map<string, int>& words)
{
	int i = 0;
  int len = str.length();
	while(i < len)
	{
		char c = str[i];
		if(((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || c == ' ')
		{
			if((c>='A')&&(c<='Z')) str[i]+=32; //Assuming dictionary contains small letters only.
			++i;
		}
		else
		{
      int eR = 1;
      if (c == '<') {
        size_t pos = str.find('>', i);
        size_t pos2 = str.find('>', pos+1);
        str.insert(pos2+1, " ");
        eR = pos2-i;
      }
			str.erase(i,eR);
			len-=eR;
		}
	}
  regex rgx("\\b\\w{4,}\\b");
  smatch match;
  // if (regex_search(str, match, rgx)) {
  //   cout << "match: " << match[0] << endl;
  // }
  while (regex_search (str,match,rgx)) {
   for (string x:match) {
     if (words.count(x) == 0) {
             words[x] = 1;
           } else{
             words[x] += 1;
           }
   }
   str = match.suffix().str();
 }
  // istringstream buf(str);
  // istream_iterator<std::string> beg(buf), end;
  // vector<string> tokens(beg, end);
  // vector<string>::iterator it = tokens.begin();
  // for(it; it != tokens.end(); it++) {
  //       if ((*it).length() < 4) {
  //         tokens.erase(it);
  //       }
  //   }
	return str;
}

void printTop100(map<string, int> words) {
  	vector<pair<string, int> > vec;
    map<string, int> :: iterator it2;
    string vv[27] = {"this", "that", "take", "want", "which", "then", "than", "will", "with", "have", "after", "such", "when", "some", "them", "could", "make", "through", "from", "were", "also", "into", "they", "their", "there", "and", "because"};
    vector<string> unwanted(&vv[0], &vv[0]+27);
    for (it2=words.begin(); it2!=words.end(); it2++)
    {
      if (!in_array(it2->first, unwanted)) {
        vec.push_back(make_pair(it2->first, it2->second));
      }
    }
    sort(vec.begin(), vec.end(), sortByVal);
    for (int i = 0; i < 100; i++)
    {
      if (i%10 == 0) {
        cout << endl;
      }
      cout << vec[i].first << " ";
    }
}
