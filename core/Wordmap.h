#ifndef WORDMAP_H
#define WORDMAP_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <exception>

class Wordmap//simple hash table for string
{
 public:
  Wordmap(); //default constructor
  Wordmap(const std::string* arr, const int& size); //constrution from array
  ~Wordmap(); //destructor
  void insert(const std::string& value); //insertion method
  bool lookup(const std::string& value); //lookup method
  
 private:
  std::string** slots;//array of strings used as table
  int nslots;//number of slots
  int nitems;//number of items
  uint64_t strhash(const std::string& input);
  uint64_t inthash(int value);
  void rehash();
};

#endif
