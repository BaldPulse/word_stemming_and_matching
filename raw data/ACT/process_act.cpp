#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "colors.h"


using namespace std;

int main(){
  fstream data, pdata;
  data.open("ACT_Raw.txt");
  pdata.open("ACT_process.txt");
  string linedata;
  string word;
  string buff;
  bool isWord = false;
  int i;
  while(getline(data, linedata)){
    //cout<<linedata<<endl;
    isWord = false;
    //if(linedata.find("Practice Test"))
    word.clear();
    i = 0;
    while(!isalpha(linedata[i])){
      i++;
      if(!(i<linedata.size())){
	//cout<<"reached end"<<endl;
	break;
      }
    }
    if(!(i<linedata.size()))
	continue;
    for(i; i<linedata.size(); i++){
      if((linedata[i]<=122 && linedata[i]>=97)||linedata[i] == '-')
	word.push_back(linedata[i]);
      else if(linedata[i]<=90 && linedata[i]>=65)
	word.push_back(linedata[i]+32);
      else if(linedata[i] == ' '){
	break;
      }
      else{
	if(linedata[i] != '[')
	  cout<<KGRN<<linedata<<RST<<endl;
	break;
      }
    }
    
    while(linedata[i]==' '){
      i++;
    }
    
    if(isalpha(linedata[i])){ //followed by word, either abbr. or word
      while(isalpha(linedata[i]))
	i++;
      if(linedata[i] == '.'){ //is abbr. 
	cout<<KRED<<linedata<<RST<<endl;
	isWord = true;
      }
      else //is not abbr.
	isWord = false;
    }
    else if(linedata[i] == '[' || linedata[i] == '\n') //followed by phonetics
      isWord = true;
    else if(linedata[i]>127){//followed by non ASCII char, print for checking
      cout<<KRED<<linedata<<RST<<endl;
      isWord = true;
    }
    else
      isWord = false;

    
    if(isWord)
      pdata<<word<<endl;
  }
  
}
