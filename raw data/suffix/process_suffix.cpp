#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//assert lineInfo is not empty
string strip_key(string lineInfo){
  string word;
  int i = 0;
  while(lineInfo[i]!='-'){
    i++;
    if(i == lineInfo.size())
      return word;
  }
  i++;
  while(i<lineInfo.size() && lineInfo[i]!='\t'){
    //cout<<lineInfo[i];
    word.push_back(lineInfo[i]);
    i++;
  }
  //cout<<"word is "<<word<<endl;
  return word;
}


int main(){
  fstream data, pdata;
  data.open("suffixRaw.tsv");
  pdata.open("suffixProcess.tsv");
  cout<<"open file success!"<<endl;
  string linedata;
  string name;
  //int i = 0;
  while(getline(data, linedata)){
    cout<<linedata<<endl;
    //if(i>100000)
    //  break;
    if(linedata.size() != 0){
      name = strip_key(linedata);
      if(name.size()!=0){
	pdata<<name<<endl;
	cout<<"name = "<<name<<endl;
      }
    }
    //i++;
  }
}
