#include "fileSingle.hh"

//this is a singleton class so basically I should use it only if I need a single instance of the same class at multiple locations!

//This is currently not used anywhere and there are some bugs which I havent gotten around to remove. Feel free to fix it if you want
//a singleton class for file writing
fileSingle::fileSingle(){
    fname="outputSingle.txt";
    myFile.open(fname);
    writeToFile("xStart yStart EnergyStart xEnd yEnd zEnd"); //just put in whatever you wish to write here and then you can write it.
    writeToFile("\n"); //so we can control where to insert a new line and where not to. This way we can fetch things and write them in a single line from various
    //other locations 
    //theTFile = new TFile("outputFile","RECREATE");

}

fileSingle::~fileSingle()
{
    myFile.close();
}

void fileSingle::writeToFile(std::string text)
{
    this->myFile<<text;

}

fileSingle* fileSingle::inst_=NULL;

fileSingle* fileSingle::getInstance()
{
    if (inst_==NULL)
    {
        inst_=new fileSingle();
    }
    return (inst_);
}
