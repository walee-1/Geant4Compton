#include "RunAction.hh"
#include "detector.hh"
#include "file.hh"

#include <iostream>
#include <fstream>

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


#include "generalParticleSource.hh"
#include "PhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(PhysicsList* phys): G4UserRunAction(),fPhysics(phys)
{
  analysisManager = G4AnalysisManager::Instance();

  analysisManager->SetVerboseLevel(0);  
  analysisManager->SetFirstHistoId(1);
    
  // Creating histograms
  //
  histoMaker();
 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
   delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();

  
   // Get analysis manager
  analysisManager = G4AnalysisManager::Instance();
  //G4double stepMax = fPhysics->GetStepMaxProcess()->GetMaxStep();



  analysisManager->SetVerboseLevel(0);

  // Open an output file
  //
  G4String fileName = "output";
  analysisManager->OpenFile(fileName);    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{  
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();         

  //save histograms      
  analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//All histograms that we write in root are defined here. They can be activated/deactivated or more can be added as necessary.

void RunAction::histoMaker()
{
  analysisManager->SetActivation(true);
 // const G4int nHisto=6;
  const G4String id[]={"Total Energy Deposited Per Event",
                      "Maximum Range Histogram",
                      "Total Energy",
                      "Input th",
                      "Input ph",
                      "Total Energy Deposited Secondaries",
                      "Pos at emission"};
  const G4String title[]={"Input Energy (eV)",
                          "Z (cm) After MuMetal",
                          "Energy (eV) After MuMetal",
                          "Theta",
                          "Phi",
                          "Total Energy (eV) Deposited by Secondaries",
                          "Emission Y-Z Pos (mm)"};
  G4int nbins=3000.;
  G4double xmin=0;
  G4double xmax=2.3e6;
  G4int ih = analysisManager->CreateH1(id[0],title[0],nbins,xmin,xmax);
  analysisManager->SetH1Activation(ih,true); 


  G4int ih2 = analysisManager->CreateH1(id[1],title[1],1000,27,29);
  analysisManager->SetH1Activation(ih2,false);

  G4int ih3 = analysisManager->CreateH1(id[2],title[2],nbins,xmin,xmax);
  analysisManager->SetH1Activation(ih3,true);

  G4int ih4 = analysisManager->CreateH1("Secondary En","Secondary Particles Energy (eV)",nbins,xmin,xmax);
  analysisManager->SetH1Activation(ih4,true);

  G4int ih5 = analysisManager->CreateH1("All ENs","Energy of All Particles (eV)",nbins,xmin,xmax);
  analysisManager->SetH1Activation(ih5,true);

  G4int ih6 = analysisManager->CreateH1("Pos at emission Z","Z Pos input(mm)",1000,-50,50);
  analysisManager->SetH1Activation(ih6,true);
  G4int ih7 = analysisManager->CreateH1("Pos at emission Y","Y Pos input (mm)",1000,-100,10);
  analysisManager->SetH1Activation(ih7,true);


  // G4int ih4 = analysisManager->CreateH1(id[3],title[3],nbins,-10,10);
  // analysisManager->SetH1Activation(ih4,true); //just for testing the input theta and phi distribution of the particles

  // G4int ih5 = analysisManager->CreateH1(id[4],title[4],nbins,-10,10);
  // analysisManager->SetH1Activation(ih5,true);

  // analysisManager->CreateH1("Total Energy Deposited Per Event", //name of historgram
  //                           "energy (eV) deposited in all the detector", //title of histogram
  //                           3000, //nbins
  //                           0., //xmin
  //                           15000.); //xmax (it further has unitName and fcnName both are set as default to NONE)
  //   analysisManager->CreateH1("Total Energy Deposited Per Event in Silicon","Energy deposited in Silicon",1000.,0.,15000.);
  //   analysisManager->CreateH1("Range Histogram","Range in Entire Detector",3000,-151.,-149.6);
  G4int ij2=analysisManager->CreateH2("2D Tracking","2D Position Map (mm)",nbins,-18+10,18+10,nbins,-18,18);
  analysisManager->SetH2Activation(ij2,true);
  G4int ij3 = analysisManager->CreateH2("OverAll YZ","Y-Z map (cm)",nbins,-18+20,18+20,nbins,-18,18);
  analysisManager->SetH2Activation(ij3,true);

  G4int ij4 = analysisManager->CreateH2("OverAll YZ Secondaries","Y-Z map of Secondary Particles (cm)",nbins,-18+10,18+10,nbins,-18,18);
  analysisManager->SetH2Activation(ij4,true);

  G4int ij5=analysisManager->CreateH2(id[6],title[6],nbins,-100,10,1000,-50,50);
  analysisManager->SetH2Activation(ij5,true);


}

