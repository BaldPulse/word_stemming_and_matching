#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <exception>
#include "Wordmap.h"
#include "Wordgraph.h"


int loadSuffix(std::string* suffix, std::string filename);

int loadPrefix(Wordmap* preffix, std::string filename);

int loadNoun(Wordgraph* noun, std::string filename);

int loadVerb(Wordgraph* noun, std::string filename);

void outputMeta();
#endif
