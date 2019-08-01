#include "RunAction.hh"
#include "detector.hh"

#include <iostream>

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "StepMax.hh"
#include "generalParticleSource.hh"
#include "PhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(PhysicsList* phys): G4UserRunAction(),fPhysics(phys)
{
  analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);  
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
  G4double stepMax = fPhysics->GetStepMaxProcess()->GetMaxStep();

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

void RunAction::histoMaker()
{
  analysisManager->SetActivation(true);
  const G4int nHisto=6;
  const G4String id[]={"Total Energy Deposited Per Event",
                      "Maximum Range Histogram",
                      "Total Energy Deposited Primaries",
                      "Maximum Range Histogram Primaries",
                      "Final Position Histogram Primaries",
                      "Total Energy Deposited Secondaries"};
  const G4String title[]={"energy (eV) deposited in all the detector",
                          "Maximum range in detector",
                          "Total Energy (eV) Deposited by Primaries",
                          "Maximum Range (um) of Primaries in Detector",
                          "Final Position (um) of Primaries in Detector",
                          "Total Energy (eV) Deposited by Secondaries"};
  G4int nbins=3000.;
  G4double xmin=0;
  G4double xmax=15000.;

  for(G4int k=0;k<nHisto;k++){
    G4int ih = analysisManager->CreateH1(id[k],title[k],nbins,xmin,xmax);
    analysisManager->SetH1Activation(ih,true); //in case we want to turn of a specific histogram, we can put an if condition
  }
  // analysisManager->CreateH1("Total Energy Deposited Per Event", //name of historgram
  //                           "energy (eV) deposited in all the detector", //title of histogram
  //                           3000, //nbins
  //                           0., //xmin
  //                           15000.); //xmax (it further has unitName and fcnName both are set as default to NONE)
  //   analysisManager->CreateH1("Total Energy Deposited Per Event in Silicon","Energy deposited in Silicon",1000.,0.,15000.);
  //   analysisManager->CreateH1("Range Histogram","Range in Entire Detector",3000,-151.,-149.6);

}