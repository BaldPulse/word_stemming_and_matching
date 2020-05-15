#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  fstream data, pdata;
  data.open("irregular_verbRaw.tsv");
  pdata.open("irregular_verbProcess.tsv");
  string linedata;
  string word;
  int i = 0;
  while(getline(data, linedata)){
    cout<<linedata<<endl;
    for(i =0; i < linedata.size(); i++){
      if(linedata[i] == ' ')
        linedata.erase(linedata.begin()+i);
    }
    pdata<<linedata;
    pdata<<endl;
  }
}
