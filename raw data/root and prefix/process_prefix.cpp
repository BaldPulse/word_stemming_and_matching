#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//assert lineInfo is not empty
string strip_key(string lineInfo){
  string word;
  int i = 6;
  if(lineInfo.compare(0, 6, "list \t") == 0){
    //cout<<"is a prefix"<<endl;
    while(lineInfo[i]>122 || lineInfo[i]<97){
      i++;
    }
    while(i<lineInfo.size() && lineInfo[i]!='\t'){
      //cout<<lineInfo[i];
      word.push_back(lineInfo[i]);
      i++;
    }
    cout<<"word is "<<word<<endl;
  }
  return word;
}


int main(){
  fstream data, pdata;
  data.open("prefix_rootRaw.tsv");
  pdata.open("prefixProcess.tsv");
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
