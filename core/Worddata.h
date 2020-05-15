#ifndef WORDDATA_H
#define WORDDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <iterator>
#include "language.h"
#include "Wordgraph.h"
#include "files.h"
#include "colors.h"

class Worddata{
public:
  Worddata();
  ~Worddata();
  void testWorddata();

  void storemeta();//store data to meta file
  void fetchmeta();//retrieve data from meta file
  void findmatch();//finds possible matches
  void reviewMatch();//lets operator decide for certain matches

  void fetchdata(bool print = false, std::string wordfilename ="/home/ztang/Documents/words_barron/processeddata/barron.tsv", std::string textfilename="/home/ztang/Documents/words_barron/processeddata/wonders.csv");//get data from file

  
private:
  int  fetchword(std::string filename = "/home/ztang/Documents/words_barron/processeddata/barron.tsv", bool print = false);
  int  fetchtext(std::string filename ="/home/ztang/Documents/words_barron/processeddata/wonders.csv", bool print = false);
  void processword(const std::string& word, stdwordUnit* parent, Wordgraph* data, bool print = false);

  int checkforvocab(std::pair<std::string, int> word, std::pair<std::string, int> text);
  int checkparent(int wordN, int textN);
  
  Wordgraph* words;
  Wordgraph* texts;
  language*  lang;
  
  std::unordered_set<int>* possibleMatches; //list of possible matches
  std::string* existingMatches; //array of existing matches
  int nExistingMatches;
  
  std::vector<std::pair<stdwordUnit*, stdwordUnit*>>* unresolved;
  std::vector<std::pair<stdwordUnit*, stdwordUnit*>>* addedWords;
  
  
};

#endif

std::pair<int, int> match(std::string wordA, std::string wordB);//returns the max number of consecutive matches and the location of the first matching string
