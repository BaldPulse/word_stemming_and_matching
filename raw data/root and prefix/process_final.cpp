#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
   fstream data, pdata;
  data.open("prefixProcess.tsv");
  pdata.open("prefix.tsv");
  cout<<"open file success!"<<endl;
  string linedata;
  string word, poss;
  bool isPoss;
  int i = 0;
  while(getline(data, linedata)){
    word.clear();
    poss.clear();
    isPoss = false;
    for(i=0;i<linedata.size();i++){
      if(linedata[i] == ','||linedata[i]==' '){
        if(!word.empty())
	  pdata<<word+poss<<endl;
	isPoss = false;
	word.clear();
	poss.clear();
      }
      else if(linedata[i] == '/'){
	  pdata<<(word+poss)<<endl;
	  poss.clear();
	  isPoss = true;
      }
      else{
	if(!isPoss)
	  word.push_back(linedata[i]);
	else
	  poss.push_back(linedata[i]);
	if(i == linedata.size()-1)
	  pdata<<word+poss<<endl;
      }
    }
  }
  return 0;
}
