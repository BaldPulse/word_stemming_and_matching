#include <fstream>
#include <ctime>
#include <cstdio>
#include <iostream>
#include "language.h"
#include "files.h"
#include "Wordmap.h"
#include "Wordgraph.h"
#include "Worddata.h"
#include "colors.h"
using namespace std;

int main(){
  Worddata data;
  string argument;
  cout<<"enter full path of [word] file, blank means default"<<endl;
  getline(cin, argument);
  if(argument == "")
    argument =  "/home/ztang/Documents/words_barron/processeddata/barron.tsv";
  cout<<"enter full path of [text] file, blank means default"<<endl;
  string textFile;
  getline(cin, textFile);
  if(textFile == "")
    textFile =  "/home/ztang/Documents/words_barron/processeddata/wonders.csv";
  data.fetchdata(false, argument, textFile);
  cout<<"what would you like to do?"<<endl;
  cout<<FGRN("1.match new texts and words\t2.review existing matches:  ");
  
  getline(cin, argument);
  if(argument == ""){
    cout<<"no argument provided, program terminated"<<endl;
    return 1;
  }
  if(argument[0]>57 || argument[0]<48){
    cout<<"invalid argument, program terminated"<<endl;
    return 1;
  }
    
  switch(stoi(argument)){
  case 1:
    cout<<"matching all words and texts..."<<endl;
    clock_t start;
    double duration;
    start = clock();
    data.findmatch();
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"lapsed time: "<< duration <<"seconds\n";
    cout<<endl;
    data.reviewMatch();
    cout<<"warning: overwrite existing meta files? "<<FGRN("yes/no:  ");
    while(1){
      getline(cin, argument);
      if(argument == "yes"){
        data.storemeta();
	break;
      }
      else if(argument == "no")
	break;
      else
	cout<<"invalid argument, enter "<<FGRN("yes/no:  ");
    }
    break;
  case 2:
    data.fetchmeta();
    data.reviewMatch();
    cout<<"warning: overwrite existing meta files? "<<FGRN("yes/no:  ");
    while(1){
      getline(cin, argument);
      if(argument == "yes"){
        data.storemeta();
	break;
      }
      else if(argument == "no")
	break;
      else
	cout<<"invalid argument, enter "<<FGRN("yes/no");
    }
    break;
  default:
    cout<<"invalid argument, program terminated"<<endl;
    return 1;
    break;
  }
  if(argument == "yes"){
    cout<<FRED("output meta? ")<< FGRN("y/n:  ");
    getline(cin, argument);
    if(argument == "y"){
      cout<<"meta outputted to \"output_Matches\""<<endl;
      outputMeta();
    }
    else if(argument != "n")
      cout<<"invalid input, no output generated"<<endl;
  }
  return 0;
}
