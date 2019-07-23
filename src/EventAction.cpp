#include "EventAction.hh"
#include "Analysis.hh"
#include "TrackerHit.hh"
#include "TrackerSD.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"

using std::array;
using std::vector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace {

// Utility function which finds a hit collection with the given Id, see documentation in example B5 for more info
// and print warnings if not found 
G4VHitsCollection* GetHC(const G4Event* event, G4int collId) {
  auto hce = event->GetHCofThisEvent();
  if (!hce) {
      G4ExceptionDescription msg;
      msg << "No hits collection of this event found." << G4endl; 
      G4Exception("EventAction::EndOfEventAction()",
                  "Code001", JustWarning, msg);
      return nullptr;
  }

  auto hc = hce->GetHC(collId);
  if ( ! hc) {
    G4ExceptionDescription msg;
    msg << "Hits collection " << collId << " of this event not found." << G4endl; 
    G4Exception("EventAction::EndOfEventAction()",
                "Code001", JustWarning, msg);
  }
  return hc;  
}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
:G4UserEventAction(),
 fTotalEnergyDeposit(0.)//
{ 
    histoIDs={-1,-1};
    //set printing per each event -> shows seed, bad idea for large number of events
    //G4RunManager::GetRunManager()->SetPrintProgress(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction( const G4Event*)
{ 
 //initializations   
 fTotalEnergyDeposit = 0.;


 //Theory: When you know everything but nothing works;
 //Experiment: When everything works but you don't know why 
 //below: Perfect combination of a place where theory and experiment meet. Nothing works and I have no idea why.


    G4SDManager* sdManager=G4SDManager::GetSDMpointer();
    auto analysisManager=G4AnalysisManager::Instance();
    G4String for_hits="hits";
    fHCID=sdManager->GetCollectionID(for_hits);
    if(histoIDs[0]<0){
      histoIDs[0]=analysisManager->GetH1Id("Total Energy Deposited Per Event");
    }
    if(histoIDs[1]<0){
      histoIDs[1]=analysisManager->GetH1Id("Total Energy Deposited Per Event in Silicon");
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction( const G4Event* event)
{                          
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  auto hc = GetHC(event, fHCID);
  if(! hc) return;
  G4double totalEnDep=0; //can use to extract total energy deposited per event/particle in Silicon alone

  for (unsigned long i=0; i<hc->GetSize();i++){
      G4double edep=0;
      auto hit = static_cast<TrackerHit*>(hc->GetHit(i));
      edep=hit->GetEdep();
      if(edep>0.){
          totalEnDep += edep;
          //analysisManager->FillH1(histoIDs[1],totalEnDep/eV); //arguments: id of histogram, value to fill, weight - by default set to 1
      }
  }
  
  analysisManager->FillH1(histoIDs[1],totalEnDep/eV); //arguments: id of histogram, value to fill, weight - by default set to 1


  analysisManager->FillH1(histoIDs[0], fTotalEnergyDeposit/eV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

