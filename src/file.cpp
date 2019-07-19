#include "file.hh"

file::file(){
    myFile.open("output.txt",ios::app);
    //theTFile = new TFile("outputFile","RECREATE");

}
file::~file(){
    myFile.close();
}