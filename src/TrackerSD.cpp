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
#include "RunAction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
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

    auto Track=aStep->GetTrack();
    G4int TrackID=Track->GetTrackID();

    G4StepPoint* p1=aStep->GetPreStepPoint();
    G4StepPoint* p2=aStep->GetPostStepPoint();
    G4String volName=p2->GetPhysicalVolume()->GetName();
    G4double z,y,en;
    G4AnalysisManager* anal=G4AnalysisManager::Instance(); 
  


    if (TrackID!=1 && aStep->IsFirstStepInVolume()) {
            G4String parName=Track->GetDefinition()->GetParticleName();
            G4double zSec=p1->GetPosition().getZ();
            G4double ySec=p1->GetPosition().getY();
            G4double enSec=p1->GetKineticEnergy();
            G4int secEnH=anal->GetH1Id("Secondary En");
            anal->FillH1(secEnH,enSec/eV);
            G4int posH=anal->GetH2Id("OverAll YZ Secondaries");
            anal->FillH2(posH,ySec/mm,zSec/mm);
            file* outSec=new file("Secondary_output.txt",true);
            std::stringstream sss;
            sss<<ySec/mm<<" "<<zSec/mm<<" "<<enSec/eV<<" "<<parName;
            outSec->writeToFile(sss.str());
            outSec->~file();
            return true;
    }
    if (TrackID==1 && aStep->IsFirstStepInVolume())
    {
            G4int idh2,id2;
            z=p1->GetPosition().getZ();
            y=p1->GetPosition().getY();
            en=p1->GetKineticEnergy();
            idh2=anal->GetH2Id("2D Tracking");

            id2=anal->GetH1Id("Total Energy");
            anal->FillH2(idh2,y/mm,z/mm);
            anal->FillH1(id2,en/eV);
            file* out=new file("output.txt",true);
            std::stringstream ss;
            ss<<y/mm<<" "<<z/mm<<" "<<en/eV;
            out->writeToFile(ss.str());
            out->~file();
    }
    return true;
  
}     





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
