#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool isLetter(char l){
  if(char<=122 && char>=97)
    return true;
  else
    return false;
}

int main(){
  fstream data, pdata;
  data.open("irregular_nounProcess.tsv");
  pdata.open("irregular_noun.tsv");
  string linedata;
  string first, word;
  string outTuple;
  int i;
  bool isMorph;
  while(getline(data, linedata)){
    cout<<linedata<<endl;
    isMorph = false;
    for(i = 0; i<linedata.size(); i++){
      if(linedata[i]!='\t'){
	if(!isMorph)
	  first.push_back(linedata[i]);
	else
	  word.push_back(linedata[i]);
      }
      if(i == (linedata.size()-1)||linedata[i] == '\t'){
	if(!isMorph){
	  isMorph = true;
	  outTuple.append(first);
	  cout<<first<<": ";
	}
	else{
	  if(word.size() > first.size()){
	    //cout<< word;
	    if(word.compare(0,first.size(),first) != 0){
	      outTuple.push_back('\t');
	      outTuple.append(word);
	      cout<<word<<' ';
	    }
	  }
	  else{
	     outTuple.push_back('\t');
	     outTuple.append(word);
	     cout<<word<<' ';
	  }
	  word.clear();
	}
      }
    }
    cout<<endl;
    if(outTuple != first){
      pdata<<outTuple<<endl;
    }
    outTuple.clear();
    first.clear();
    word.clear();
  }
  return 0;
}
