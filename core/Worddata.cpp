#include "Worddata.h"

using namespace std;

Worddata::Worddata(){
  this->words = NULL;
  this->texts = NULL;
  this->lang = NULL;
  this->unresolved = new vector<pair<wordUnit*, wordUnit*>>;
  this->addedWords = new vector<pair<wordUnit*, wordUnit*>>;
  this->possibleMatches = new unordered_set<int>;
  this->existingMatches = new string[150];
  this->nExistingMatches = 0;
  //this->existingMatches[0] = "yes!";
  //this->existingMatches[1] = "yes!";
  //cout<<this->existingMatches->size()<<endl;
}

Worddata::~Worddata(){
  delete this->words;
  delete this->texts;
  delete this->lang;
  delete this->unresolved;
  delete this->addedWords;
  delete this->possibleMatches;
  delete[] this->existingMatches;
}

void Worddata::testWorddata(){
  pair<int, int> p;
  this->fetchdata(false, "/home/ztang/Documents/words_barron/core/test_data/word.tsv", "/home/ztang/Documents/words_barron/core/test_data/text.csv");
  //this->fetchdata(false, "/home/ztang/Documents/words_barron/processeddata/barron.tsv", "/home/ztang/Documents/words_barron/processeddata/wonders.csv");
  this->findmatch();
  
  //this->fetchmeta();
  this->reviewMatch();
  this->storemeta();
}

void Worddata::storemeta(){
  fstream meta;
  fstream matches;

  meta.open("/home/ztang/Documents/words_barron/core/Meta/barron.meta", ofstream::out | ofstream::trunc);
  matches.open("/home/ztang/Documents/words_barron/core/Meta/matches.meta", ofstream::out | ofstream::trunc);
  for(auto it = this->possibleMatches->begin(); it!= this->possibleMatches->end(); ++it){
    //cout<<*it<<endl;
    meta<<*it<<endl;
  }
  for(uint i = 0; i<150; i++){
    //cout<<*it<<endl;
    matches<<i<<endl;
    matches<<this->existingMatches[i];
  }
  cout<<"storemeta:\tstored "<<this->possibleMatches->size()<<" possible entries"<<endl;
  cout<<          "\t\tstored "<<this->nExistingMatches<<" existing matches"<<endl;
}

void Worddata::fetchmeta(){
  ifstream meta;
  ifstream matches;
  string linedata;
  int match, i;
  vector<int> buffer;
  meta.open("/home/ztang/Documents/words_barron/core/Meta/barron.meta");
  matches.open("/home/ztang/Documents/words_barron/core/Meta/matches.meta");
  i = 0;
  while(getline(meta, linedata)){
    match = stoi(linedata);
    buffer.insert(buffer.begin(), match);
    i++;
  }
  for(auto it=buffer.begin(); it!=buffer.end(); ++it)
    this->possibleMatches->insert(*it);
  cout<<"fetchmeta: "<<"retrieved "<<i<<" possible matches; ";
  i = 0;
  while(getline(matches, linedata)){
    if(48<=linedata[0]&&linedata[0]<=57)
      match = stoi(linedata);
    else{
      this->existingMatches[match]+= (linedata+'\n');
      i++;
    }
  }
  this->nExistingMatches = i;
  cout<<"retrieved "<<i<<" existing matches"<<endl;
}

int getWeek(const string& week){
  //cout<<"getting weeknum for "<< week<<endl;
  int n = 0;
  int weekint =0;
  for(uint i=0; i<week.size(); i++){
    if(week[i]>=48 && week[i]<=57){
      switch(n){
      case 0:
	//cout<<"G"<<week[i]-48-2<<' '<<weekint<<endl;
	weekint = 30 *(week[i]-48-2);
	break;
      case 1:
	weekint += 5*(week[i]-48-1);
	//cout<<"U"<<week[i]-48-1<<' '<<weekint<<endl;
	break;
      case 2:
	weekint += week[i]-48-1;
	//cout<<"W"<<week[i]-48-1<<' '<<weekint<<endl;
	break;
      default:
	return -1;
      }
      n++;
    }
  }
  return weekint;
}

void Worddata::reviewMatch(){
  int wordPos, textPos;
  int newMatches=0;
  wordUnit* wordPtr, *textPtr;
  string decision;
  string buff;
  int prevSize = this->possibleMatches->size();
  int saveSize = 0;
  bool isUndo = false;
  bool warn = true;
  auto prev=this->possibleMatches->begin();
  auto bprev = this->possibleMatches->begin();
  cout<<"input y if the two are related, n if the two are not:"<<endl;
  auto it=this->possibleMatches->begin();
  while(it!=this->possibleMatches->end()){
    //cout<<*it<<"match code: "<<endl;
    wordPos = (*it >> 16);
    textPos = (*it & 0xFFFF);
    cout<<KYEL<<wordPos<<'\t'<<textPos<<RST<<endl;
    wordPtr = this->words->lookup(wordPos, 1);
    textPtr = this->texts->lookup(textPos, 1);
    cout<<wordPtr->first<<'\t'<<textPtr->first<<"  ";
    if(((wordPtr->first == textPtr->first)||(wordPtr->first+'s'==textPtr->first)||(wordPtr->first==textPtr->first+'s'))&&!isUndo){
      decision = "y";
      cout<<FRED("auto resolved")<<endl;
    }
    else{
      getline(cin, decision);
    }
    if(decision == "y"||decision == "yes"){
      newMatches++;
      this->nExistingMatches++;
      for(auto wit=textPtr->second.begin(); wit!=textPtr->second.end();++wit){
	//cout<<"adding to existing matches"<<endl;
	if(wordPtr->first != textPtr->first)
	  buff = textPtr->first +'(' + wordPtr->first+")\n";
	else
	  buff = wordPtr->first +'\n';
	//cout<<"appedning words"<<endl;
	wordUnit* weekBuff = static_cast<wordUnit*>(*wit);
	//cout<<"static cast complete, position = "<<getWeek(weekBuff->first)<<endl;
	this->existingMatches[getWeek(weekBuff->first)].append(buff);
      }
      saveSize++;
      it = next(it, 1);
    }
    else if(decision == "stop"){
      this->possibleMatches->erase(this->possibleMatches->begin(), it);
      cout<<prevSize-this->possibleMatches->size()<<" entries processed, "<<newMatches<<" new matches found, "<<this->possibleMatches->size()<<" matches left"<<endl;
      return;
    }
    else if(decision == "save"){
      cout<<"warning: overwrite existing meta?"<<FGRN(" yes/no:  ");
      while(1){
	getline(cin, decision);
	if(decision == "yes"){
	  prev = it;
	  bprev = it;
	  this->possibleMatches->erase(this->possibleMatches->begin(), it);
	  this->storemeta();
	  saveSize = 0;
	  break;
	}
	else if(decision == "no")
	  break;
	else
	  cout<<"invalid argument, enter "<< FGRN("yes/no:  ");
      }
    }
    else if(decision == "z"||decision == "u"){
      if(bprev == it)
	cout<<"recent save, unable to undo"<<endl;
      else{
	isUndo = true;
	bprev = it;//save current location in order to return
	it = prev;//go back to redo location
      }
    }
    else{
      saveSize++;
      prev = it;//save redo location
      it = next(it,1);//go to next location
    }

    if(saveSize > 20 && warn &&!isUndo){
      cout<<FRED("processed 20 entries without saving, save and OVERWRITE? ")<< FGRN("yes/no  ");
      getline(cin, decision);
      if(decision == "yes"){
	prev = it;
	bprev = it;
	this->possibleMatches->erase(this->possibleMatches->begin(), it);
	this->storemeta();
      }
      else if(decision == "no"){
	cout<<"turn off warning? "<<FGRN("yes/no  ");
	getline(cin, decision);
	if(decision == "yes"){
	  cout<<FRED("warning turned ")<< FRED(BOLD("OFF"))<<endl;
	  warn = false;
	}
      }
      else
	cout<<"invalid argument, you will be warned again in"<< FRED(" 20 ")<<"entries"<<endl;
      saveSize = 0;
    }

    if(isUndo&&!(decision=="z"||decision == "u")){
    //cout<<"in return trip"<<endl;
    it = bprev;//return to location before undo
    isUndo = false;//redo is done
    }
  }

  
  this->possibleMatches->clear();
  cout<<"congratution! all matches reviewed"<<endl;
}

int Worddata::checkforvocab(pair<string, int> word,pair<string, int>  text){
  pair<int, int> charresult;
  //int possible = 0;
  charresult = match(word.first, text.first);
  if(charresult.first <3){
    return -1;
  }
  string longS, shortS;
  if(word.first.size()>text.first.size()){
    shortS = text.first;
    longS  = word.first;
  }
  else{
    shortS = word.first;
    longS  = text.first;
  }
  if(charresult.second!=0 && !this->lang->isprefix(longS.substr(0, charresult.second))){
    //cout<<shortS<<" : "<<longS<<endl;
    return -2;
  }
  if(charresult.first == int(shortS.size()) ){
    //if(shortS > longS)
    //cout<<shortS<<" =possible= "<<longS<<endl;
    if(this->checkparent(word.second, text.second)){
      return 1;
    }
    else
      return 0;
  }
  else
    return -1;
}

pair<int, int> match(string wordA, string wordB){
  string shortS;
  string longS;
  if(wordA.size()>wordB.size()){
    shortS = wordB;
    longS  = wordA;
  }
  else{
    shortS = wordA;
    longS  = wordB;
  }
  int maxMatch=0;
  int startPos=0;
  size_t i,j;
  for(i=0; i<=longS.size()-shortS.size(); i++){
    for(j=0; j<shortS.size(); j++){
      if(!(longS[i+j] == shortS[j]))
	break;
    }
    if(int(j)>maxMatch){
      maxMatch = j;
      startPos = i;
    }
  }
  pair<int, int> p(maxMatch, startPos);
  return p;
}

int Worddata::checkparent(int wordN, int textN){
  vector<void*> wordP, textP;
  wordP = this->words->getparent(wordN);
  textP = this->texts->getparent(textN);
  size_t compare;
  wordUnit* wordBuff;
  wordUnit* textBuff;
  int wordPos, textPos;
  string longS, shortS;
  for(vector<void*>::iterator iter=wordP.begin(); iter!=wordP.end(); ++iter){
    for(vector<void*>::iterator jter=textP.begin(); jter!=textP.end(); ++jter){
      wordBuff = static_cast<wordUnit*>(*iter);
      textBuff = static_cast<wordUnit*>(*jter);
      wordPos = this->words->getPosition(wordBuff->first, 1);
      textPos = this->texts->getPosition(textBuff->first, 1);
      int key = (wordPos<<16) | textPos;
      //cout<<key<<' '<<wordBuff->first<<' '<<textBuff->first<<endl;
      this->possibleMatches->insert(key);
      if(wordBuff->first.size()>textBuff->first.size()){
	longS = wordBuff->first;
	shortS= textBuff->first;
      }
      else{
	longS = textBuff->first;
	shortS= wordBuff->first;
      }
	compare = longS.find(shortS);
      if(compare!=string::npos){
	if(shortS.size() == longS.size()){
	  //cout<<"  "<<wordBuff->first<<" == "<<textBuff->first<<endl;
	}
	if((shortS.size() == longS.size()-1)&&longS.back() == 's'){
	  //cout<<"  "<<wordBuff->first<<" == "<<textBuff->first<<endl;
	}
	//if((shortS.size()>3) && (compare+shortS.size()>=longS.size()-1))
	//cout<<"  "<<wordBuff->first<<" == "<<textBuff->first<<endl;
      }
      else{
	this->unresolved->emplace_back(wordBuff, textBuff);
      }
    }    
  }
  return 0;//stub
}

void Worddata::findmatch(){
  pair<int, int> matchResult;
  pair<string, int>* allwords;
  pair<string, int>* alltexts;
  int wordSize, textSize;
  int possible = 0;
  allwords = this->words->topackage();
  wordSize = this->words->getnitems(0);
  alltexts = this->texts->topackage();
  textSize = this->texts->getnitems(0); 
  for(int i=0; i<wordSize; i++){
    for(int j=0; j<textSize; j++){
      if(this->checkforvocab(allwords[i], alltexts[j])>=0)
	possible++;
    }
  }
  cout<<"located matches: "<<possible<<"; possible matches: "<<this->possibleMatches->size()<<endl;
  delete[] allwords;
  cout<<"deleted buffer [allwords] "<<wordSize<<" entries"<<endl;
  delete[] alltexts;
  cout<<"deleted buffer [alltexts] "<<textSize<<" entries"<<endl;
  //cout<<endl;
}

void Worddata::fetchdata(bool print, string wordfilename, string textfilename){
  if(this->lang)
    delete this->lang;
  this->lang = new language;
  this->lang->autofill();
  try{
    fetchword(wordfilename, print);
  }catch(const system_error& e){
    clog << e.what() << " (" << e.code() << ")" << endl;
  }
  try{
    fetchtext(textfilename, print);
  }catch(const system_error& e){
    clog << e.what() << " (" << e.code() << ")" << endl;
  }
  cout<<endl;
}

int Worddata::fetchword(string filename, bool print){
  if(this->words)
    delete this->words;
  this->words = new Wordgraph;
  ifstream wordfile;
  string linedata;
  int size = 0;
  wordUnit* buff;
  wordfile.open(filename);
  if(!wordfile)
    throw system_error(errno, system_category(), "failed to open" + filename);
  while(getline(wordfile,linedata)){
    if(linedata.empty())
      continue;
    if(linedata[0]<=122 && linedata[0]>=97){
      if(print)
	cout<<"original: "<<linedata<<endl;
      buff = this->words->insert(linedata, NULL);
      this->processword(linedata, buff, this->words, print);
      size++;
    }
  }
  cout<<FRED("fetchword: ")<<endl;
  cout<<"inserted "<<this->words->getnitems(0)<<" morphed forms from "<<this->words->getnitems(1)<<" unique words, ";
  cout<<"checked "<<size<<" words"<<endl;
  return size;
}

int Worddata::fetchtext(string filename, bool print){
  if(this->texts)
    delete this->texts;
  this->texts = new Wordgraph;
  ifstream textfile;
  string linedata;
  int size = 0;
  size_t i ,j;
  wordUnit* buff;
  wordUnit* unitbuff;
  string unit, book, word;
  textfile.open(filename);
  if(!textfile)
    throw system_error(errno, system_category(), "failed to open" + filename);
  j = 0;
  while(getline(textfile,linedata)){
    word.clear();
    if(linedata.empty())
      continue;
    if(linedata.compare(0,4, "    ")==0){
      for(i=4; i<linedata.size(); i++){
	if(linedata[i] == ','){
	  if(word.size()>2){
	    if(print)
	      cout<<"original: "<<word<<endl;
	    buff = this->texts->insert(word, unitbuff);
	    this->processword(word, buff, this->texts, print);
	  }
	  size++;
	  word.clear();
	  
	}
	else{
	  word.push_back(linedata[i]);
	  if((i==linedata.size()-1) && word.size()>2){
	    if(print)
	      cout<<"original: "<<word<<endl;
	    buff = this->texts->insert(word, unitbuff);
	    this->processword(word, buff, this->texts, print);
	    size++;
	  }
	}
      }
    }
    else if(linedata.compare(0,2, "  ")==0){
      unit = linedata.substr(2, linedata.size()-2);
      unit.insert(0,1,' ');
      unit.insert(0,book);
      if(print)
	cout<<unit<<endl;
      unitbuff = this->texts->insert(unit, NULL, 2);
    }
    else{
      book = linedata.substr(1, linedata.size()-2);
    }
    j++;
  }
  cout<<FRED("fetchtext: ")<<endl;
  cout<<"inserted "<<this->texts->getnitems(0)<<" morphed forms from "<<this->texts->getnitems(1)<<" unique words, ";
  cout<<"checked "<<size<<" words"<<endl;
  return size;
}

void Worddata::processword(const string& word, wordUnit* parent, Wordgraph* data, bool print){
  string buff;
  size_t i;
  buff = this->lang->stripsuffix(word);
  if(print)
    cout<<"  desuffix: "<<buff<<endl;
  data->insert(buff, parent, 0);
  if(buff.back() == 'i')
    buff.back() = 'y';
  else if(buff.back() == 'q')
    buff.back() = 'c';
  data->insert(buff, parent, 0);
  
  buff = word;
  if(word.compare(word.size()-2, 2, "es")==0){
    if(word[word.size()-3]=='o'||word[word.size()-3]=='s')
      buff.erase(word.size()-2, 2);
    else
      buff.erase(word.size()-1,1);
    if(print)
      cout<<"  denouned: "<<buff<<endl;
    data->insert(buff, parent, 0);
  }
  else{
    buff =this->lang->processnoun(word);
    if(print)
      cout<<"  denouned: "<<buff<<endl;
    data->insert(buff, parent, 0);
  }
  
  buff = word;
  if(word.back()=='s'){
    buff.erase(word.size()-1, 1);
    if(print)
      cout<<"  deverbed: "<<buff<<endl;
  }
  else{
    buff = this->lang->processverb(word);
    if(print)
      cout<<"  deverbed: "<<buff;
    if(buff.back() == '\t'){
      for(i=0; i<buff.size(); i++){
	if(buff[i] == '\t'){
	  data->insert(buff.substr(0, i), parent, 0);
	  if(print)
	    cout<<": ["<<buff.substr(0, i)<<"] ";
	  data->insert(buff.substr(i+1, buff.size()-2-i), parent, 0);
	  if(print)
	    cout<<'['<<buff.substr(i+1, buff.size()-2-i)<<']';
	  break;
	}
      }
    }
    if(print)
      cout<<endl;
  }
}

