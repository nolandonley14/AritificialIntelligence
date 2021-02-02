#include <iostream>
//#include "Dialog.h"
#include <fstream>
#include <sstream>
#include <map>
#include <time.h>
#include <vector>

using namespace std;

vector<string> spaceSeparatedRespone(string resp); //used to check for known words in database
void readDatabase(ifstream& inFile, map< string, vector<string> >& Database); //puts database into a map of single (String) keys
                                                                              // which could have multiple (vector<string>) values
vector<string> getKeys(map< string, vector<string> > Database); // returns all of the keys in the database
void conversation(map< string, vector<string> > Database, vector<string>& userResponse, string& originalUserResponse, string& usersName);
                                                                // method that controls all conversation logic for generating Eliza's response

int main() {
  // Used to seed the randomness of Eliza's responses
  srand(time(0));

  // Data Structure used for Eliza's "Brain"
  map< string, vector<string> > Database;

  // Reading the database.txt file into Eliza's "Brain"
  ifstream inFile;
  readDatabase(inFile, Database);

  // Obtaining the users name and starting the conversation.
  string usersName;
  string userResponse;
  cout << "\nThe Doctor is in.\n" << endl;
  cout << "Hey, my name is Eliza, What's your name?" << endl;
  cout << " - ";
  cin >> usersName;
  cout << "Hey there " + usersName + "! What's on your mind?" << endl;
  cout << " - ";
  cin.ignore();
  getline(cin, userResponse);
  vector<string> r = spaceSeparatedRespone(userResponse);

  // While the users response doesn't contain "bye" keep going
  while(find(r.begin(), r.end(), "bye") == r.end()) {

    // Generate Eliza's response based on what the user said.
    conversation(Database, r, userResponse, usersName);

    // Promt user to respond
    cout << " - ";

    // Get users response, transform it to lowercase, and see if it contains "bye", if not, send it back to Eliza.
    getline(cin, userResponse);
    transform(userResponse.begin(), userResponse.end(), userResponse.begin(), ::tolower);
    r = spaceSeparatedRespone(userResponse);
  }

  // After the user says "bye", end the conversation
  cout << "\n" << usersName << ", I hope I have made you feel better today. If\nyou need to speak some more, you know where to find me. :)\n" << endl;
  return 0;
}

// method that controls all conversation logic for generating Eliza's response
void conversation(map< string, vector<string> > Database, vector<string>& userResponse, string& originalUserResponse, string& usersName) {

    // Get a iterator for Eliza's Database
    map<string, vector<string> >::iterator it;

    // Get a list of the keys in the database
    vector<string> keys = getKeys(Database);

    // For all of the words in the users response, check if they are in the Database
    // This way, when a match is found, it is gaurenteed to be the first match of the response.
    for (int i = 0; i < userResponse.size(); i++) {
      it = Database.find(userResponse[i]);
      if (it != Database.end()) {

        // get a random number response from the database
        int random = rand() % Database[userResponse[i]].size();
        string elizaResponse = Database[userResponse[i]][random];

        // if the response contains '*', then get the rest of the input an add it to the response.
        size_t found = elizaResponse.find('*');
        if (found != string::npos) {
          string restOfUserInput = "";
          i++;
          while (i < userResponse.size()) {
            restOfUserInput = restOfUserInput + userResponse[i] + " ";
            i++;
          }
          elizaResponse.replace(found, 1, restOfUserInput);
        }

        // if the response contains '_', then replace the _ with the users Name.
        size_t found2 = elizaResponse.find('_');
        if (found2 != string::npos) {
          elizaResponse.replace(found2, 1, usersName);
        }

        // respond and return to main method
        cout << elizaResponse << endl;
        return;
      }

      // if none of the words from the user input match, check the phrases from the Database
      // against the user input. This test for the phrases like "i am", "i feel", etc.
      // This if statements works just like the above one.
      else if (i == userResponse.size() - 1)
      {
        for (int j = 0; j < keys.size(); j++) {
          size_t found = originalUserResponse.find(keys[j]);
          if (found != string::npos) {
            int random = rand() % Database[keys[j]].size();
            string elizaResponse = Database[keys[j]][random];
            size_t found2 = elizaResponse.find('*');
            if (found2 != string::npos) {
              string restOfUserInput = "";
              restOfUserInput = restOfUserInput + originalUserResponse.substr(found + keys[j].length());
              elizaResponse.replace(found2-1, 2, restOfUserInput);
            }
            size_t found3 = elizaResponse.find('_');
            if (found3 != string::npos) {
              elizaResponse.replace(found3, 1, usersName);
            }
            cout << elizaResponse << endl;
            return;
          }
          else if (j == keys.size() - 1) {
            int random = rand() % Database["^~`"].size();
            string elizaResponse = Database["^~`"][random];
            size_t found = elizaResponse.find('_');
            if (found != string::npos) {
              elizaResponse.replace(found, 1, usersName);
            }
            cout << elizaResponse << endl;
            return;
          }
        }
      }
    }
}

// Method to return all of the keys in the database
vector<string> getKeys(map< string, vector<string> > Database) {
  map<string, vector<string> >::iterator it;
  vector<string> keys;
  for (it = Database.begin(); it != Database.end(); ++it) {
    keys.push_back(it->first);
  }
  return keys;
}


//puts database into a map of single (String) keys
// which could have multiple (vector<string>) values

void readDatabase(ifstream& inFile, map< string, vector<string> >& Database) {
  string line;
  inFile.open("database.txt");

  /* for every entry in database.txt, save it in line and do the following:
  - save the word/phrase before the ":" as a string keyword.
  - save the strings, seperated by "," as vector<string> responses.
  - insert the keyword, responses pair into the database.
  ex: i feel: Tell me more about such feelings., Do you often feel *?, Do you enjoy feeling *?
  keyword -> "i feel"
  responses -> "Tell me more about such feelings."
                "Do you often feel *?"
                "Do you enjoy feeling *?"
  */
  while(getline(inFile, line)) {
    string keyWord;
    vector<string> responses;
    stringstream s(line);
    string answer;
    getline(s, keyWord, ':');
    string temp = "";
    while(getline(s, answer, ',')) {
      if (temp != "") {
        answer = temp + "," + answer;
        temp = answer;
        if (answer[answer.length() -1] == '"') {
          answer = answer.substr(0, (int) answer.length() - 1);
          responses.push_back(answer);
          temp = "";
        }
      } else {
        if (answer[1] == '"') {
          temp = answer.substr(2);
        } else {
          temp = "";
          answer = answer.substr(1);
          responses.push_back(answer);
        }
      }
    }
    Database.insert(pair<string, vector<string> >(keyWord, responses));
  }
}

// method to put all space separeted words of the user response into vector<string>
// used to check for known words in database
vector<string> spaceSeparatedRespone(string resp) {
  vector<string> v;
  string word = "";
  int num = 0;
  resp = resp + ' ';
  int length = resp.size();

  for (int i = 0; i < length; i++) {
    if (resp[i] != ' ' && resp[i] != ',' && resp[i] != '.' && resp[i] != '!' && resp[i] != '?' && resp[i] != ';')
      word = word + resp[i];
    else {
      if ((int) word.size() != 0)
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        v.push_back(word);
      word = "";
    }
  }
  return v;
}
