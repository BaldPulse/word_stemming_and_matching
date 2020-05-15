#include <fstream>
#include <ctime>
#include <cstdio>
#include <iostream>
#include "language.h"
#include "files.h"
#include "Wordmap.h"
#include "Wordgraph.h"
#include "Worddata.h"
using namespace std;

int main(){
  /* Wordgraph* nounlist = new Wordgraph;
  loadNoun(nounlist, "/home/ztang/Documents/words_barron/processeddata/irregular_noun.tsv");
  wordUnit* link;
  link = static_cast<wordUnit*>(nounlist->lookup("symposium", 0)->second.back());
  cout<<link->first<<endl;
  link = static_cast<wordUnit*>(nounlist->lookup("wolves", 1)->second.back());
  cout<<link->first<<endl;
  return 0;*/
  /*Wordgraph* verblist = new Wordgraph;
  try{
    loadVerb(verblist, "/home/ztang/Documents/words_barron/processeddata/irregular_verb.tsv");
  }catch(const system_error& e){
    clog << e.what() << " (" << e.code() << ")" << endl;
    return 0;
  }
  wordUnit* link;
  link = static_cast<wordUnit*>(verblist->lookup("torn", 2)->second.front());
  cout<<link->first<<endl;
  link = static_cast<wordUnit*>(verblist->lookup("tear", 0)->second.front());
  cout<<link->first<<endl;
  return 0;*/
  /*language english;
  english.autofill();
  cout<<english.stripsuffix("occasion")<<endl;
  cout<<((english.isprefix("aero")) ? "aero is a prefix" : "aero isn't a prefix")<<endl;
  cout<<((english.isprefix("ero")) ? "aero is a prefix" : "ero isn't a prefix")<<endl;
  cout<<((english.isprefix("aearo")) ? "aero is a prefix" : "aearo isn't a prefix")<<endl;
  cout<<(english.processnoun("axes"))<<endl;
  cout<<(english.processnoun("tooth"))<<endl;
  cout<<(english.processnoun("axs"))<<endl;
  cout<<(english.processverb("become"))<<endl;
  cout<<(english.processverb("became"))<<endl;
  cout<<(english.processverb("fly"))<<endl;
  cout<<(english.processverb("flown"))<<endl;
  cout<<(english.processverb("flew"))<<endl;
  cout<<(english.processverb("where"))<<endl;*/
  clock_t start;
  double duration;

  start = clock();
  
  Worddata dat;
  dat.testWorddata();
  
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

  cout<<"printf: "<< duration <<'\n';
}
