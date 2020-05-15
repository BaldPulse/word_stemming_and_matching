#include "language.h"

using namespace std;

language::language(){
  this->suffix = new string[150];
  this->suffixSize = 0;
  this->prefix = new Wordmap;
  this->noun   = new Wordgraph;
  this->verb   = new Wordgraph;
}

language::~language(){
  delete[] suffix;
  delete prefix;
  delete noun;
  delete verb;
}

string language::stripsuffix(const string& word){
  if(word.size()<=4)
    return word;
  string product = word;
  //int tempSuffix = -1;
  for(int i=0; i<this->suffixSize; i++){
    if(this->suffix[i].size()<(product.size())){
      if(product.compare(product.size()-this->suffix[i].size(),\
			 this->suffix[i].size(), this->suffix[i]) == 0){
	if(product.size()-this->suffix[i].size()>3){
	  product.erase(product.size()-this->suffix[i].size(),
			this->suffix[i].size());
	  if(this->suffix[i] == "ness"||this->suffix[i] == "ed"){
	    if(product.back() == 'i')
	      product.back()='y';
	    product = this->stripsuffix(product);
	  }
	  return product;
	}
	/*else if(product.size()-this->suffix[i].size()==3){
	  tempSuffix = i;
	  }*/
      }
    }
  }
  /*if(tempSuffix >= 0){
    product.erase(product.size()-this->suffix[tempSuffix].size(),
		  this->suffix[tempSuffix].size());
    if(this->suffix[tempSuffix] == "ness"||this->suffix[tempSuffix] == "ed"){
      if(product.back() == 'i')
	product.back()='y';
      product = this->stripsuffix(product);
    }
  }*/  
  return product;
}

bool language::isprefix(const string&word){
  return this->prefix->lookup(word);
}

string language::processnoun(const string&word){
  wordUnit* fword;
  wordUnit* sword;
  fword = this->noun->lookup(word,0);
  if(!fword){
    fword = this->noun->lookup(word,1);
  }
  if(!fword)
    return word;
  sword = static_cast<wordUnit*>(fword->second.back());
  return sword->first;
}
string language::processverb(const string&word){
  wordUnit* fword;
  wordUnit* sword;
  string verbs;
  fword = this->verb->lookup(word,0);
  if(!fword){
    fword = this->verb->lookup(word,1);
  }
  if(!fword){
    fword = this->verb->lookup(word,2);
  }
  if(!fword){
    return word;
  }
  sword = static_cast<wordUnit*>(fword->second.back());
  verbs.append(sword->first);
  if(fword->second.size()==2){
    verbs.push_back('\t');
    sword = static_cast<wordUnit*>(fword->second.front());
    verbs.append(sword->first);
    verbs.push_back('\t');
  }
  return verbs;
}

void language::autofill(){
  cout<<FRED("language: autofilling...")<<endl;
  cout<<"  ";
  this->createsuffix();
  cout<<"  ";
  this->createprefix();
  cout<<"  ";
  this->createnoun();
  cout<<"  ";
  this->createverb();
  cout<<endl;
}

void language::createsuffix(string filename){
  if(this->suffix)
    delete[] this->suffix;
  this->suffix = new string[150];
  try{
    this->suffixSize = loadSuffix(this->suffix, filename);
  }catch(const system_error& e){
    clog << e.what() << " (" << e.code() << ")" << endl;
  }
}
void language::createprefix(string filename){
  if(this->prefix)
    delete this->prefix;
  this->prefix = new Wordmap;
  try{
    loadPrefix(this->prefix, filename);
  }catch(const system_error& e){
    clog << e.what() << " (" << e.code() << ")" << endl;
  }
}
void language::createnoun(string filename){
  if(this->noun)
    delete this->noun;
  this->noun = new Wordgraph;
  try{
    loadNoun(this->noun, filename);
  }catch(const system_error& e){
    clog << e.what() << " (" << e.code() << ")" << endl;
  }
}
void language::createverb(string filename){
  if(this->verb)
    delete this->verb;
  this->verb = new Wordgraph;
  try{
    loadVerb(this->verb, filename);
  }catch(const system_error& e){
    clog << e.what() << " (" << e.code() << ")" << endl;
  }
}
