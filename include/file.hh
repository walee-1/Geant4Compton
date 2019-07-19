#ifndef file_h
#define file_h 1

#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH1F.h"

using namespace std;

class file{
    public:
	    file();
	    ~file();
        ofstream myFile;
        TFile* theTFile;
	
};

#endif