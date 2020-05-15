#ifndef LANGUAGE_H
#define LANGUAGE_H

//language.h
//contains methods for processing words

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Wordmap.h"
#include "Wordgraph.h"
#include "files.h"
#include "colors.h"

class language{
public:
  language();
  ~language();
  //word processing methods
  std::string stripsuffix(const std::string&word);
  bool isprefix(const std::string&word);
  std::string processnoun(const std::string&word);
  std::string processverb(const std::string&word);
  //language library management methods
  void autofill();
  void createsuffix(std::string filename="/home/ztang/Documents/words_barron/processeddata/suffix.tsv");
  void createprefix(std::string filename="/home/ztang/Documents/words_barron/processeddata/prefix.tsv");
  void createnoun(std::string filename="/home/ztang/Documents/words_barron/processeddata/irregular_noun.tsv");
  void createverb(std::string filename="/home/ztang/Documents/words_barron/processeddata/irregular_verb.tsv");
private:
  std::string* suffix;
  int suffixSize;
  Wordmap* prefix;
  Wordgraph* noun;
  Wordgraph* verb;
};




#endif
