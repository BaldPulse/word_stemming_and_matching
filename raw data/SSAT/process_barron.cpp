#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  fstream data, pdata;
  data.open("SSAT_RAW.txt");
  pdata.open("SSAT_process.txt");
  string linedata;
  string word;
  int i = 0;
  while(getline(data, linedata)){
    word.clear();
    //cout<<linedata<<endl;
    if(linedata[0]<32 || linedata[0]>127){
      //cout<<linedata<<endl;
      //cout<<"not ascii"<<endl;
      continue;
    }
    //cout<<"words: ";
    for(i=0; i<linedata.size(); i++){
      if((linedata[i]<=122 && linedata[i]>=97)||linedata[i] == '-')
	word.push_back(linedata[i]);
      else if(linedata[i]<=90 && linedata[i]>=65)
	word.push_back(linedata[i]+32);
      else if(linedata[i] == ':' ||linedata[i] == ' '){
	pdata<<word<<endl;
	break;
      }
      else{
	cout<<word<<endl;
	cout<<"contains\'"<<linedata[i]<<"\'special character"<<endl;
	break;
      }
    }
  }
}
