#include "EventAction.hh"
#include "Analysis.hh"
//#include "TrackerHit.hh"
//#include "TrackerSD.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "TrackingAction.hh"
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
:G4UserEventAction()
{ 
    histoIDs={-1,-1,-1,-1,-1,-1,-1};
    maxRange=-160;

    //set printing per each event -> shows seed, bad idea for large number of events
    //G4RunManager::GetRunManager()->SetPrintProgress(1);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::MaxPosition(G4double range, G4int TrackID){

  if(maxRange<range){
    maxRange=range;

    if(TrackID==1){
    maxRangePrime=maxRange;
    }
  }
}

void EventAction::BeginOfEventAction( const G4Event*)
{ 
 //initializations   
 //fTotalEnergyDeposit = 0.;


    //G4SDManager* sdManager=G4SDManager::GetSDMpointer();
    auto analysisManager=G4AnalysisManager::Instance();

    //fHCID_Si=sdManager->GetCollectionID("active/HC_Si");
    //fHCID_Al=sdManager->GetCollect4inionID("SD_Al/HC_Al");

    // if(histoIDs[0]<0){
    //   histoIDs[0]=analysisManager->GetH1Id("Total Energy Deposited Per Event");
    // }
    // if(histoIDs[1]<0){
    //   histoIDs[1]=analysisManager->GetH1Id("Maximum Range Histogram");
    // }
    // //if(histoIDs[2]<0){
    //   //histoIDs[2]=analysisManager->GetH1Id("Total Energy Deposited Per Event in Aluminium");
    // //} 
    // if(histoIDs[2]<0){
    //   histoIDs[2]=analysisManager->GetH1Id("Total Energy Deposited Primaries");
    // }
    // if(histoIDs[3]<0){
    //   histoIDs[3]=analysisManager->GetH1Id("Maximum Range Histogram Primaries");
    // }
    // if(histoIDs[4]<0){
    //   histoIDs[4]=analysisManager->GetH1Id("Final Position Histogram Primaries");
    // }
    // if(histoIDs[5]<0){
    //   histoIDs[5]=analysisManager->GetH1Id("Total Energy Deposited Secondaries");
    // }
    // histoIDs[6]=analysisManager->GetH2Id("2D Position Map");
    // histoIDs[7]=analysisManager->GetH2Id("2D Position Map Test");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction( const G4Event* event)
{                          
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  ///auto hc_Si = GetHC(event, fHCID_Si);

  //auto hc_Al = GetHC(event, fHCID_Al);

  //if(! (hc_Si) ) return;

  // G4double TotEnDepSi_prime=0; //can use to extract total energy deposited per event/particle in Silicon alone
  // G4double TotEnDepSi_second=0;
  // G4double finalZPrime;

  //G4double totalEnDepAl=0;

  // for (unsigned long i=0; i<hc_Si->GetSize();i++){
  //     G4double edep_Si=0;

  //     auto hit_Si = static_cast<TrackerHit*>(hc_Si->GetHit(i));
  //     G4int Track_ID=hit_Si->GetTrackID();
  //     edep_Si=hit_Si->GetEdep();

  //     if(edep_Si>0.){

  //       if(Track_ID==1){
  //         TotEnDepSi_prime += edep_Si;

  //         G4ThreeVector final_pos=hit_Si->GetPos();
  //         finalZPrime=final_pos.getZ();
  //       }
  //       else{
  //         TotEnDepSi_second += edep_Si;

  //       }   
  //     }

  //         //analysisManager->FillH1(histoIDs[1],totalEnDep/eV); //arguments: id of histogram, value to fill, weight - by default set to 1
  // }

  /* for (unsigned long j=0; j<hc_Al->GetSize();j++){
      G4double edep_Al=0;
      auto hit_Al = static_cast<TrackerHit*>(hc_Al->GetHit(j));
      edep_Al=hit_Al->GetEdep();
      if(edep_Al>0.){
          totalEnDepAl += edep_Al;
      }
  }*/
  
  

  // analysisManager->FillH1(histoIDs[0],fTotalEnergyDeposit/eV); //arguments: id of histogram, value to fill, weight - by default set to 1
  // //analysisManager->FillH1(histoIDs[2],totalEnDepAl/eV);
 // analysisManager->FillH1(histoIDs[1],maxRange/um);
  // analysisManager->FillH1(histoIDs[2],TotEnDepSi_prime/eV);
  // analysisManager->FillH1(histoIDs[3],maxRangePrime/um);
  // analysisManager->FillH1(histoIDs[4],finalZPrime/um);
  // analysisManager->FillH1(histoIDs[5],TotEnDepSi_second/eV);
 // analySisManager->FillH2(histoIDs[6],position/um);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
