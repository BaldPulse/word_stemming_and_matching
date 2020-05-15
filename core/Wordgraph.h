#ifndef WORDGRAPH_H
#define WORDGRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <exception>
#include <utility>

#define stdwordUnit std::pair<std::string, std::vector<void*>>
#define wordUnit pair<string, vector<void*>>
class Wordgraph
{
public:
  Wordgraph();//default constructor
  ~Wordgraph();//destructor
  stdwordUnit* insert(const std::string& value, stdwordUnit* related, int layernum=1);
  stdwordUnit* lookup(const std::string& value, int layernum);
  stdwordUnit* lookup(const int& position, int layernum);
  int getPosition(const std::string& value, int layernum);
  std::pair<std::string, int>* topackage(size_t layernum=0);
  std::vector<void*> getparent(int location, size_t layernum=0); //return all the parents of the subword at a certain location
  int getnitems(int layernum);//returns the value of nitems
  void testWordlist();//tool for testing wordlist
  
private:
  struct Wordlist
  {
    Wordlist();//default constructor
    ~Wordlist();//destructor
    stdwordUnit* insert(const std::string& value, stdwordUnit* const parent);//insert method, return pointer to new entry
    int lookup(const std::string& value);//return the position of element, return position of NULL if entry DNE
    std::pair<std::string, int>* topackage();//return all the subword and position of the subword in the Wordlist, used by data to compare sub words
    uint64_t strhash(const std::string& input);
    uint64_t inthash(uint64_t input);
    void rehash();//rehashes if item takes up half the space
    stdwordUnit** slots;
    int nslots;
    int nitems;
  };
  Wordlist** layer;
  
    
};

#endif
