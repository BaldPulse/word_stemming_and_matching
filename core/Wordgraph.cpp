#include "Wordgraph.h"

using namespace std;

Wordgraph::Wordlist::Wordlist(){
  this->slots = new wordUnit*[30];  
  this->nslots = 30;
  this->nitems = 0;
  for(int i=0; i<this->nslots; i++)
    slots[i] = NULL;
}

Wordgraph::Wordlist::~Wordlist(){
  for(int i=0; i<nslots; i++){
    if(this->slots[i])
      delete slots[i];
  }
  delete[] slots;
}

wordUnit* Wordgraph::Wordlist::insert(const string& value, wordUnit* const parent){
  int hashVal = this->lookup(value);
  if(!this->slots[hashVal]){//word does not exist, return pointer to new word
    this->nitems++;
    if(this->nitems > this->nslots/2-1)
      this->rehash();
    hashVal = this->lookup(value);
    this->slots[hashVal] = new wordUnit;
    this->slots[hashVal]->first = value;
    if(parent)
      this->slots[hashVal]->second.push_back(parent);
    return this->slots[hashVal];
  }
  else{//word already existed, return NULL pointer
    if(parent){
      for(vector<void*>::iterator iter=this->slots[hashVal]->second.begin();
	  iter!=this->slots[hashVal]->second.end(); ++iter){
	if(*iter == parent){
	  return NULL;
	}
      }
      this->slots[hashVal]->second.push_back(parent);
    }
    return NULL;
  }
}

int Wordgraph::Wordlist::lookup(const string& value){
  uint64_t stringVal;
  uint64_t hashVal;
  stringVal = this->strhash(value);
  hashVal = this->inthash(stringVal);
  for(int i = 0;; i++){
    if(this->slots[(hashVal+i*i)%this->nslots]==NULL){
      return (hashVal+i*i)%this->nslots;
    }
    else if(this->slots[(hashVal+i*i)%this->nslots]->first == value){
      return (hashVal+i*i)%this->nslots;
    }
  }
}

pair<string, int>* Wordgraph::Wordlist::topackage(){
  pair<string, int>* package;
  package = new pair<string, int>[this->nitems];
  int i, j;
  j = 0;
  for(i=0; i<this->nslots; i++){
    if(this->slots[i]){
      package[j].first = this->slots[i]->first;
      package[j].second= i;
      j++;
    }
  }
  return package;
}

uint64_t Wordgraph::Wordlist::strhash(const std::string& input){
  uint32_t hash = 0;
  for(uint8_t byte: input) {
    hash += byte;
    hash += hash << 10;
    hash ^= hash >> 6;
  }

  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

uint64_t Wordgraph::Wordlist::inthash(uint64_t input){
  return input % this->nslots;
}

void Wordgraph::Wordlist::rehash(){
  this->nslots = 2*this->nslots;
  wordUnit** oldSlots = this->slots;//temporary buffer
  int i;
  int hashVal;
  this->slots = new wordUnit*[this->nslots];
  for(i = 0; i< this->nslots; i++)
    this->slots[i] = NULL;
  for(i = 0; i<this->nslots/2; i++){//iterate through old
    if(oldSlots[i]){
      hashVal = this->lookup(oldSlots[i]->first);
      this->slots[hashVal] = oldSlots[i];
    }
  }
  //for(i = 0; i<this->nslots/2; i++)
  //  delete oldSlots[i];
  delete[] oldSlots;//delete buffer
}

Wordgraph::Wordgraph(){
  this->layer = new Wordlist*[3];
  layer[0] = NULL;
  layer[1] = NULL;
  layer[2] = NULL;
}

Wordgraph::~Wordgraph(){
  for(int i = 0; i<3; i++){
    if(layer[i])
      delete layer[i];
  }
  delete[] layer;
}

int Wordgraph::getnitems(int layernum){
  return this->layer[layernum]->nitems;
}

void Wordgraph::testWordlist(){
  //stubed
}

wordUnit* Wordgraph::insert(const std::string& value, wordUnit* related, int layernum){
  if(!this->layer[layernum]){
    this->layer[layernum] = new Wordlist;
  }
  return this->layer[layernum]->insert(value, related);
}

wordUnit* Wordgraph::lookup(const string& value, int layernum){
  return this->layer[layernum]->slots[this->layer[layernum]->lookup(value)];
}

wordUnit* Wordgraph::lookup(const int& position, int layernum){
  return this->layer[layernum]->slots[position];
}

int Wordgraph::getPosition(const string& value, int layernum){
  return this->layer[layernum]->lookup(value);
}

pair<string, int>* Wordgraph::topackage(size_t layernum){
  return this->layer[layernum]->topackage();
}

vector<void*> Wordgraph::getparent(int location, size_t layernum){
  vector<void*> buff;
  buff = this->layer[layernum]->slots[location]->second;
  return buff;
}
