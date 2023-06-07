#ifndef file_h
#define file_h 1

#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "G4UImessenger.hh"
#include "globals.hh"

using namespace std;

class file{
    public:
	    file();
        file(G4String);
        file(G4String, G4bool);
        file(G4bool);
	    ~file();
        ofstream myFile;
        TFile* theTFile;
        void writeToFile(std::string);
    private:
        string fname;
};

#endif