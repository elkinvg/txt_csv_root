#ifndef DF_h
#define DF_h

#include "TFile.h"
#include "TH1.h"

#include <string>
#include <string.h>
#include <fstream>

#include <sstream>

using std::endl;
using std::string;
using std::ios;

enum TypeOfOutFile {CSV=0, TXT=1};
void makeCsvFileFromHist(TH1 ** hist,const int numOfHist, int typeOfOut, string suffix = "");
template <typename T> void makeCsvFileFromHistTemp(T** hist, const int numOfHist, int typeOfOut, string suffix = "");
string replacePoint(double data);


#endif