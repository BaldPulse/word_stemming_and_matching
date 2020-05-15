#include "Wordmap.h"

using namespace std;

Wordmap::Wordmap(){
  this->slots = new string*[30];
  this->nslots = 30;
  this->nitems = 0;

  for(int i=0; i<nslots;i++){
    this->slots[i]=NULL;
  }
}

Wordmap::Wordmap(const string* arr, const int& size){
  for(int i=0; i<size;i++){
    this->insert(arr[i]);
  }
}

Wordmap::~Wordmap(){
  for(int i = 0; i<this->nslots; i++)
    delete this->slots[i];
  delete[] this->slots;
}

void Wordmap::insert(const std::string& value){
  this->nitems++;
  if(this->nitems > this->nslots/2-1){
    this->rehash();
  }
  uint64_t stringVal;
  uint64_t hashVal;
  stringVal = this->strhash(value);
  hashVal = this->inthash(stringVal);
  
  for(int i = 0;; i++){	
    if(this->slots[(hashVal+i*i)%this->nslots] == NULL){
      this->slots[(hashVal+i*i)%this->nslots] = new string(value);
      break;
    }
  }
}

bool Wordmap::lookup(const std::string& value){
  uint64_t stringVal;
  uint64_t hashVal;
  stringVal = this->strhash(value);
  hashVal = this->inthash(stringVal);
  
  for(int i = 0;; i++){	
    if(this->slots[(hashVal+i*i)%this->nslots] == NULL)
      return false;
    if(*(this->slots[(hashVal+i*i)%this->nslots]) == value)
      return true;
  }
}

uint64_t Wordmap::strhash(const std::string& input){
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

uint64_t Wordmap::inthash(int input){
  return input * (23 + 1) % this->nslots;
}

void Wordmap::rehash(){
  this->nslots = 2*this->nslots;
  std::string** oldSlots = this->slots;
  int i;
  this->slots = new std::string*[this->nslots];
  for(i = 0; i< this->nslots; i++){
    this->slots[i] = NULL;
  }
  for(i = 0; i<this->nslots/2; i++){
    if(oldSlots[i]){
      this->insert(*(oldSlots[i]));
    }
  }
  for(i = 0; i<this->nslots/2; i++)
    delete oldSlots[i];
  delete[] oldSlots;
}
