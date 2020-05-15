#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool isLetter(char l){
  if(l<=122 && l>=97){
    return true;
  }
  else
    return false;
}

bool doContain(string S, string s){
  for(int i = 0; i<S.size()-s.size(); i++){
    if(S.compare(i,s.size(),s) == 0)
      return true;
  }
  return false;
}

int main(){
  fstream data, pdata;
  data.open("irregular_verbProcess.tsv");
  pdata.open("irregular_verb.tsv");
  string linedata;
  string first, word;
  string outTuple;
  int i;
  bool isMorph;
  while(getline(data, linedata)){
    //cout<<linedata<<endl;
    isMorph = false;
    for(i = 0; i<linedata.size(); i++){
      if(isLetter(linedata[i])){
	//cout<<"~";
	if(!isMorph)
	  first.push_back(linedata[i]);
	else
	  word.push_back(linedata[i]);
      }
      if((i == (linedata.size()-1) && !word.empty())|| !isLetter(linedata[i])){
	//cout<<'*';
	if(!isMorph){
	  isMorph = true;
	  outTuple.append(first);
	  //cout<<first<<": ";
	}
	else{
	  if(word.size() >= outTuple.size()){
	    //cout<< word;
	    if(word.find(outTuple)==string::npos){
	      outTuple.push_back('\t');
	      outTuple.append(word);
	      //cout<<word<<' ';
	    }
	  }
	  else if(outTuple.find(word) == string::npos){
	     outTuple.push_back('\t');
	     outTuple.append(word);
	     //cout<<word<<' ';
	  }
	  word.clear();
	}
      }
    }
    if(outTuple != first){
      pdata<<outTuple<<endl;
    }
    else
      cout<<"ignored: "<<linedata<<endl;
    outTuple.clear();
    first.clear();
    word.clear();
  }
  return 0;
}
