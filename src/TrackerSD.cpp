// $Id: TrackerSD.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file TrackerSD.cc
/// \brief Implementation of the TrackerSD class

#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4Track.hh"

#include "file.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name)
{
  hcID=-1;
  fHitsCollection=NULL;
  collectionName.insert(hitsCollectionName);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(const G4String& name) 
 : G4VSensitiveDetector(name)
{
  hcID=-1;
  fHitsCollection=NULL;
  collectionName.insert("hits");
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::~TrackerSD() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection 
    = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  if(hcID<0){
    hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
  }
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerSD::ProcessHits(G4Step* aStep, 
                                     G4TouchableHistory*)
{
  //auto charge =aStep->GetTrack()->GetDefinition()->GetPDGCharge();  //in case if we ever want to exclude gamma contribution, put an if statement
                                                                    //on the charge
  // energy deposit
  auto edep = aStep->GetTotalEnergyDeposit();

  if (edep==0.) return false; //return false if there is no energy deposited.

  auto newHit = new TrackerHit();

  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID()); //get the trackID -> maybe redundant for us? Not sure
  newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle() //get the chamber number where the hit took place, again maybe redundant for us
                                               ->GetCopyNumber());
  newHit->SetEdep(edep); //get energy deposited in said hit, useful
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition()); //get the position of the particle AFTER the step/hit. 

  fHitsCollection->insert( newHit );

  //newHit->Print();
  //newHit->Draw();
  //newHit->Write();


  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
  // if ( verboseLevel>=0 ) { 
  //    G4int nofHits = fHitsCollection->entries();
  //    G4cout << G4endl
  //           << "-------->Hits Collection: in this event they are " << nofHits 
  //           << " hits in the tracker chambers: " << G4endl;
  //    for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  // }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
