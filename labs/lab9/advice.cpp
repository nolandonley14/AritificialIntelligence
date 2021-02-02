#include <fstream>
#include <cctype>
#include <iostream>
using namespace std;

#include <string>
#include "stack.h"

struct AdviceNode
{
  string QorA;      // a question or an answer
  AdviceNode * yes;   // yes branch
  AdviceNode * no;    // no branch

  AdviceNode(const string & s);  // constructor
};

AdviceNode::AdviceNode(const string & s)
: QorA(s),
  yes(NULL),
  no(NULL)
{}

void ReadTree(istream & in, AdviceNode * & T);

bool IsQuestionNode(AdviceNode * T);
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false

void GiveAdvice(AdviceNode * T);
// precondition: T is not NULL

bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack);
// precondition:  T is not NULL

void ShowPath(const Stack<string> & pathStack);

int main()
{
  string fname;
  cout << "\nEnter filename of advice knowledge base: ";
  cin  >> fname; cin.ignore();

  ifstream treeIn(fname.c_str());

  AdviceNode * T;
  ReadTree(treeIn, T);

  GiveAdvice(T);

  string movie = "";
  Stack<string> path;


  cin.ignore();
  while(movie != "q"){
    cout << "\nEnter the name of a movie from tree to see path (q to quit): ";
    getline(cin, movie);
    if(movie != "q"){
      path.makeEmpty();
      TracePath(T, movie, path);
      ShowPath(path);
    }
  }


  return 0;
}

void ReadTree(istream & in, AdviceNode * & T)
{
  string QA;

  getline(in, QA);
  T = new AdviceNode(QA);
  if(QA[QA.length()-1] != '?'){
    T->yes = NULL;
    T->no  = NULL;
  }
  else{
    ReadTree(in, T->yes);
    ReadTree(in, T->no);
  }
}

bool IsQuestionNode(AdviceNode * T)
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false
{
  return (T->QorA[(T->QorA).length()-1] == '?');
}

void GiveAdvice(AdviceNode * T)
{
  if (!IsQuestionNode(T)) {
    cout << T->QorA << endl;
  }
  else {
    string ans = "";
    cout << T->QorA << " ";
    cin >> ans;
    if (ans == "Y") {
      GiveAdvice(T->yes);
    }
    else {
      GiveAdvice(T->no);
    }
  }
}

bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack)
{
  if (T->QorA == movie) {
    return true;
  } else {
    pathStack.push(T->QorA + " yes");
    if (T->yes != NULL) {
      if (TracePath(T->yes, movie, pathStack)) {
        return true;
      } else {
        pathStack.pop();
        pathStack.push(T->QorA + " no");
        if (TracePath(T->no, movie, pathStack)) {
          return true;
        } else {
          pathStack.pop();
        }
      }
    } else {
      pathStack.pop();
    }
  }
}

void ShowPath(const Stack<string> & pathStack)
{
  Stack<string> path(pathStack);

  while(!path.isEmpty()){
    cout << path.top() << endl;
    path.pop();
  }
}
