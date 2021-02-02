#include "Dialog.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Dialog::Dialog(int numKeywords, int numResponses) {

}

// Adds the specified keyword
void Dialog::addKeyword(string keyword) {
  keywordsArray.push_back(keyword);
  keywordCount++;
}

// Adds the specified response
void Dialog::addResponse(string response) {
  responsesArray.push_back(response);
  responseCount++;
}

// Searches input for a matching keyword. If one is found,
// returns a randomly chosen response. If no keyword is found,
// returns null.
string Dialog::getResponse(string input) {
  return "";
}
