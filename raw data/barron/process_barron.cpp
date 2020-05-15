#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  fstream data, pdata;
  data.open("barron_wordRaw.tsv");
  pdata.open("barron_wordProcess.tsv");
  string linedata;
  string word;
  int i = 0;
  while(getline(data, linedata)){
    //cout<<linedata<<endl;
    if(linedata[0]<32 || linedata[0]>127){
      //cout<<linedata<<endl;
      //cout<<"not ascii"<<endl;
      continue;
    }
    //cout<<"words: ";
    for(i=0; i<linedata.size(); i++){
      if((linedata[i]>122 || linedata[i]<97) && word.size()>1){
	pdata<<word<<endl;
	//cout<<word<<' ';
	word.clear();
      }
      else{
	if(linedata[i]<=123 && linedata[i]>=97)
	  word.push_back(linedata[i]);
	else if(linedata[i]<=90 && linedata[i]>=65)
	  word.push_back(linedata[i]+32);
	else
	  cout<<linedata<<endl<<"special character"<<endl;
      }
    }
    if(word.size()>0){
      pdata<<word<<endl;
      //cout<<word<<' ';
      word.clear();
    }
    //cout<<endl;
  }
}
