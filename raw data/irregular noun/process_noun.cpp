#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  fstream data, pdata;
  data.open("irregular_nounRaw.ssv");
  pdata.open("irregular_nounProcess.tsv");
  string linedata;
  string word;
  int i = 0;
  while(getline(data, linedata)){
    for(i =0; i < linedata.size(); i++){
      if(linedata[i] == ' ')
	pdata<<'\t';
      else
	pdata<<linedata[i];
    }
    pdata<<endl;
  }
}
