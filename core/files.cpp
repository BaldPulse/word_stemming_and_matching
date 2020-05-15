#include "files.h"

using namespace std;

int loadSuffix(string* suffix, string filename){
  ifstream suffixfile;
  string linedata;
  int size=0;
  suffixfile.open(filename);
  if(!suffixfile)
    throw system_error(errno, system_category(), "failed to open" + filename);
  while(getline(suffixfile,linedata)){
    suffix[size] = linedata;
    size++;
  }
  if(size == 0)
    cout<<"file found but no entries added";
  else
    cout<<"loadSuffix Success, "<<size<<" entries loaded"<<endl;
  return size;
}

int loadPrefix(Wordmap* prefix, string filename){
  ifstream prefixfile;
  string linedata;
  int size=0;
  prefixfile.open(filename);
  if(!prefixfile)
    throw system_error(errno, system_category(), "failed to open" + filename);
  while(getline(prefixfile,linedata)){
    prefix->insert(linedata);
    size++;
  }
  if(size == 0)
    cout<<"file found but o entries added";
  else
    cout<<"loadPrefix Success, "<<size<<" entries loaded"<<endl;
  return size;
}

int loadNoun(Wordgraph* noun, string filename){
  ifstream nounfile;
  string linedata;
  string word[2];
  int size=0;
  size_t i, j;
  wordUnit* buff[2];
  nounfile.open(filename);
  if(!nounfile)
    throw system_error(errno, system_category(), "failed to open" + filename);
  while(getline(nounfile,linedata)){
    j=0;
    for(i=0; i<2; i++){
      buff[i] = NULL;
      word[i].clear();
    }
    for(i=0; i<linedata.size(); i++){
      if(linedata[i] == '\t'||linedata[i] == ' '){
	j++;
      }
      else{
	word[j].push_back(linedata[i]);
      }
      if(i == linedata.size()-1){
	buff[0] = noun->insert(word[0], NULL, 0);
	buff[1] = noun->insert(word[1], buff[0], 1);
	noun->insert(word[0], buff[1], 0);
      }
    }
    size++;
  }
  if(size == 0)
    cout<<"file found but o entries added";
  else
    cout<<"loadNoun Success, "<<size<<" entries loaded"<<endl;
  return size;
}

int loadVerb(Wordgraph* verb, string filename){
  ifstream verbfile;
  string linedata;
  size_t i, j;
  string word[3];
  wordUnit* buff[3];
  int size = 0;
  verbfile.open(filename);
  if(!verbfile)
    throw system_error(errno, system_category(), "failed to open" + filename);
  while(getline(verbfile,linedata)){
    j = 0;
    for(i=0; i<3; i++){
      word[i].clear();
      buff[i] = NULL;
    }
    //cout<<"init complete"<<endl;
    for(i=0; i<linedata.size(); i++){
      if(linedata[i] =='\t' || linedata[i] == ' '){
	j++;
      }
      else{
	word[j].push_back(linedata[i]);
      }
    }
    size+=(j+1);
    for(i=0; i<(j+1); i++){
      buff[i] = verb->insert(word[i], NULL, i);
    }
    for(i=0; i<(j+1); i++){
      if(!(i==0))
	verb->insert(word[i], buff[0], i);
      if(!(i==1))
	verb->insert(word[i], buff[1], i);
      if(!(i==2)&&j==2)
	verb->insert(word[i], buff[2], i);
    }
  }
  if(size == 0)
    cout<<"file found but o entries added";
  else
    cout<<"loadVerb Success, "<<size<<" entries loaded"<<endl;
  return size;
}

int loadWords(vector<string>& word, string filename){
  ifstream wordfile;
  string linedata;
  int size = 0;
  wordfile.open(filename);
  if(!wordfile)
    throw system_error(errno, system_category(), "failed to open" + filename);
  while(getline(wordfile,linedata)){
    if(linedata[0]<=122 && linedata[0]>=97){
      word.push_back(linedata);
      size++;
    }
  }
  return size;
}

void outputMeta(){
  ifstream input;
  fstream output;
  string linedata;
  input.open("/home/ztang/Documents/words_barron/core/Meta/matches.meta");
  output.open("/home/ztang/Documents/words_barron/output_Matches", ofstream::out | ofstream::trunc);

  while(getline(input, linedata)){
    if(linedata[0]>=48 && linedata[0]<=57){
      int wbuff, lbuff;
      output<<endl;
      lbuff = stoi(linedata);
      wbuff = lbuff/30;
      lbuff = lbuff%30;
      output<<'G'<<wbuff+2;
      wbuff = lbuff/5;
      lbuff = lbuff%5;
      output<<"Unit"<<wbuff+1<<"Week"<<lbuff+1<<endl;
    }
    else
      output<<linedata<<endl;
  }
}
