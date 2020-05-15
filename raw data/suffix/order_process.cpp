#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void propagateDown(string *heap, int size, int n){
  if(2*n >= size)
    return;
  string temp;
  int next;
  if(size > (2*n+1)){
    if(heap[n].size()<heap[2*n].size()||heap[n].size()<heap[2*n+1].size()){
      next =(heap[2*n].size()>heap[2*n+1].size() ? 2*n: 2*n+1);
      temp = heap[n];
      heap[n] = heap[next];
      heap[next] = temp;
      propagateDown(heap, size, next);
    }
  }
  else if(heap[n].size()<heap[2*n].size()){
    temp = heap[n];
    heap[n] = heap[2*n];
    heap[2*n] = temp;
    propagateDown(heap, size, 2*n);
  }
}

void buildHeap(string *heap, int size){
  int max = 2;
  while(size > max){
    max = max *2;
  }
  for(int i = 1; i<max/2; i++){
    propagateDown(heap, size, max/2-i);
  }
}

string deleteMax(string *heap,int& size){
  heap[0] = heap[1];
  heap[1] = heap[size--];
  propagateDown(heap, size, 1);
  return heap[0];
}

void insertArr(string value, string *heap, int& size){
  heap[size] = value;
  size++;
}

int main(){
  fstream data, pdata;
  data.open("suffixProcess.tsv");
  pdata.open("suffix.tsv");
  string linedata;
  string word;
  string suffixHeap[200];
  int size = 1;
  int i;
  word.clear();
  while(getline(data, linedata)){
    for(i = 0; i<linedata.size(); i++){
      if(linedata[i]>=97 && linedata[i]<=122){
	word.push_back(linedata[i]);
      }
      else if(!word.empty()){
	insertArr(word, suffixHeap, size);
	cout<<word<<endl;
	word.clear();
      }
      if(i == (linedata.size()-1) && !word.empty()){
	insertArr(word, suffixHeap, size);
	cout<<word<<endl;
	word.clear();
      }
    }
  }
  buildHeap(suffixHeap, size);
  while(size!=1){
    //cout<<deleteMax(suffixHeap, size)<<", ";
    pdata<<deleteMax(suffixHeap, size)<<endl;
  }
  return 0;
}
