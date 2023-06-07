#ifndef fileSingle_h
#define fileSingle_h 1

#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "G4UImessenger.hh"
#include "globals.hh"




class fileSingle{
    public:
	  static fileSingle* getInstance();
      void writeToFile(std::string text);
    private:
      static fileSingle* inst_;
      fileSingle();
      ~fileSingle();
      std::string fname;
      std::ofstream myFile;
      //fileSingle()
};

#endif