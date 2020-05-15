#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

string check_then_add(string str){
  string words;
  for(int i=0; i<str.size(); i++){
    if(str[i]>=97 && str[i]<=122)
      words.push_back(str[i]);
    else if(str[i]>=65 && str[i]<=90)
      words.push_back(str[i]+32);
    else{
      if(str[i] == '\''){
	cout<<str<<endl;
	if(str[i+1] == 't'){
	  words.pop_back();
	}
      }
      if(!words.empty() && words.back() != ',')
	words.push_back(',');
    }
  }
  if(words.empty())
    return words;
  if(words.back() == ',')
    words.pop_back();
  return words;
}

int main(){
  fstream data, pdata, excluded;
  data.open("wondersRaw.txt");
  pdata.open("wondersProcess.csv");
  excluded.open("excluded.csv");
  string linedata;
  string word;
  int i, j;
  bool isText = false;
  j = 0;
  while(getline(data, linedata)){
    if(linedata.empty())
      continue;
    if(linedata.size() >= 10){
      if(linedata.compare(0,9,"Wonders G") == 0){
	pdata<<endl;
	pdata<<'['<<linedata<<']'<<endl;
	excluded<<linedata<<endl;
	continue;
      }
    }
    if(linedata.size() >= 12){
      if(linedata.compare(0,4,"Unit") == 0 && linedata.compare(7,4,"Week")==0){
	pdata<<"  "<<linedata<<endl;
	isText = true;
	j++;
	continue;
      }
    }
    if(linedata.size()>=5){
      if(linedata.compare(0,5,"TOEFL")==0){
	pdata<<endl;
	excluded<<linedata<<endl;
	isText = false;
	continue;
      }
    }
    if(linedata.size() >= 15){
      if(linedata.compare(1,3,"ake") == 0 && linedata.compare(6,9,"onnection")==0){
	pdata<<endl;
	excluded<<linedata<<endl;
	isText = false;
	//j++;
	continue;
      }
    }
    if(isText){
      //cout<<linedata<<endl;
      pdata<<"    ";
      pdata<<check_then_add(linedata)<<endl;
    }
    else
      excluded<<check_then_add(linedata)<<endl;
    /*if(j>=10 && isText == false){
      cout<<"last line is: "<<linedata<<endl;
      break;
      }*/
  }
  cout<<"number of texts: "<<j<<endl;
  data.close();
  pdata.close();
  return 0;
}
