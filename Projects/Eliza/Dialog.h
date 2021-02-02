#include <vector>
#include <string>

using namespace std;

class Dialog {

  public :
    Dialog(int numKeywords, int numResponses);

    // Adds the specified keyword
    void addKeyword(string keyword);

    // Adds the specified response
    void addResponse(string response);

    // Searches input for a matching keyword. If one is found,
    // returns a randomly chosen response. If no keyword is found,
    // returns null.
    string getResponse(string input);

  private :
    vector<string> keywordsArray; // A dynamic array
    vector<string> responsesArray;// A dynamic array
    int keywordCount = 0;
    int responseCount = 0;

  };
