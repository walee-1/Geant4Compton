#include "file.hh"
//opens a new file called output.txt or whatever you want, and then writes in it. 
//caveat, if used in some other class then you have to call it a new, meaning the new file will overwrite any other files of the same name
//being written. Tried to counter it by using fileSingle which is a singleton class but haven't implemented it.
file::file(){
    fname="output.txt";
    myFile.open(fname,ios::app);

    //theTFile = new TFile("outputFile","RECREATE");

}
//overridden constructor used when I want to have a file named a specific name
file::file(G4String name){
    fname=name;
    myFile.open(fname,ios::app);

    //theTFile = new TFile("outputFile","RECREATE");

}
file::file(G4String name, G4bool append){
    fname=name;
    if (append)
    {
        myFile.open(fname,ios::app);
    }
    else{
        myFile.open(fname);
    }
    //theTFile = new TFile("outputFile","RECREATE");

}
file::file(G4bool append){
    if (append)
    {
        myFile.open(fname,ios::app);
    }
    else{
        myFile.open(fname);
    }
}
file::~file(){
    myFile.close();
}

void file::writeToFile(std::string text)
{
    this->myFile<<text;
   this-> myFile<<"\n";
}
