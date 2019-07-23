#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(): G4UserRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);  
  analysisManager->SetFirstHistoId(1);
    
  // Creating histograms
  //
  analysisManager->CreateH1("Total Energy Deposited Per Event", //name of historgram
                            "energy (eV) deposited in all the detector", //title of histogram
                            3000., //nbins
                            0., //xmin
                            200000.); //xmax (it further has unitName and fcnName both are set as default to NONE)
  analysisManager->CreateH1("Total Energy Deposited Per Event in Silicon","Energy deposited in Silicon",3000.,0.,200000.);
  analysisManager->CreateH1("Range Histogram","Range in Entire Detector",3000,-151.,150.);
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
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

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
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
