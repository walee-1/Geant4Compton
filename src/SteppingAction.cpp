#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "globals.hh"
#include "file.hh"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* EvAct)
:G4UserSteppingAction(),fEventAction(EvAct)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    // auto Track=aStep->GetTrack();
    // G4int TrackID=Track->GetTrackID();
    // G4AnalysisManager* anal=G4AnalysisManager::Instance(); 
    // G4StepPoint* p1=aStep->GetPreStepPoint();
    // G4StepPoint* p2=aStep->GetPostStepPoint();
    // G4String volName=p1->GetPhysicalVolume()->GetName();
    // G4double z,y,en;


    // if (TrackID!=1 && p2->GetStepStatus()==fWorldBoundary && p1->GetPosition().getX()/cm>=12.92/cm) {
    //         G4String parName=Track->GetDefinition()->GetParticleName();
    //         G4double zSec=p2->GetPosition().getZ();
    //         G4double ySec=p2->GetPosition().getY();
    //         G4double enSec=p2->GetKineticEnergy();
    //         G4int secEnH=anal->GetH1Id("Secondary En");
    //         anal->FillH1(secEnH,enSec/eV);
    //         G4int posH=anal->GetH2Id("OverAll YZ Secondaries");
    //         anal->FillH2(posH,ySec/cm,zSec/cm);
    //         file* outSec=new file("Secondary_output.txt",true);
    //         std::stringstream sss;
    //         sss<<ySec/cm<<" "<<zSec/cm<<" "<<enSec/eV<<" "<<parName;
    //         outSec->writeToFile(sss.str());
    //         outSec->~file();
    //         return;
    // }
    // if (p2->GetStepStatus()==fWorldBoundary && TrackID==1 && p1->GetPosition().getX()/cm>=12.92/cm)
    // {
    //         G4int idh2,id2;
    //         z=p2->GetPosition().getZ();
    //         y=p2->GetPosition().getY();
    //         en=p2->GetKineticEnergy();
    //         idh2=anal->GetH2Id("OverAll YZ");

    //         id2=anal->GetH1Id("All ENs");
    //         anal->FillH2(idh2,y/cm,z/cm);
    //         anal->FillH1(id2,en/eV);
    //         file* outAll=new file("output_All.txt",true);
    //         std::stringstream ssAll;
    //         ssAll<<y/cm<<" "<<z/cm<<" "<<en/eV;
    //         outAll->writeToFile(ssAll.str());
    //         outAll->~file();
    //     if(p1->GetPosition().getY()/mm<=27/2/mm && p1->GetPosition().getY()/mm>=-27/2/mm
    //      && p1->GetPosition().getZ()/mm<=19/2/mm && p1->GetPosition().getZ()/mm>=-19/2/mm)
    //     {
    //         z=p1->GetPosition().getZ();
    //         y=p1->GetPosition().getY();
    //         en=p1->GetKineticEnergy();
    //         idh2=anal->GetH2Id("2D Tracking");

    //         id2=anal->GetH1Id("Total Energy");
    //         anal->FillH2(idh2,y/mm,z/mm);
    //         anal->FillH1(id2,en/eV);
    //         file* out=new file("output.txt",true);
    //         std::stringstream ss;
    //         ss<<y/mm<<" "<<z/mm<<" "<<en/eV;
    //         out->writeToFile(ss.str());
    //         out->~file();
    //     }
            
    // }

    //  G4double EdepStep = aStep->GetTotalEnergyDeposit();
    //  //if (EdepStep > 0.) fEventAction->AddEdep(EdepStep);
    //  G4StepPoint* rangePoint;
    //  rangePoint = aStep->GetPostStepPoint();
    //  G4ThreeVector rangeThreeVector= rangePoint->GetPosition();

    //  G4double kinEn=aStep->GetPostStepPoint()->GetKineticEnergy();
    //  if (aStep->GetPostStepPoint()->GetStepStatus() == fWorldBoundary)
    //  {
    //         G4AnalysisManager* anal=G4AnalysisManager::Instance();
    //         G4int idh2=anal->GetH2Id("2D Tracking");
    //         G4int id=anal->GetH1Id("Maximum Range Histogram");
    //         G4double z= aStep->GetPostStepPoint()->GetPosition().getZ()/cm;
    //         G4double x=aStep->GetPostStepPoint()->GetPosition().getX()/cm;
    //         G4double y=aStep->GetPostStepPoint()->GetPosition().getY()/cm;
    //         file out("output.txt",true);
    //         std::stringstream ss;
    //         ss<<x<<" "<<y<<" "<<z;
    //         out.writeToFile(ss.str());
    //         out.~file();
    //         anal->FillH2(idh2,x,y);
    //         anal->FillH1(id,z);
    //  }

    //  G4AnalysisManager* anal=G4AnalysisManager::Instance();
    //  G4int idh2=anal->GetH2Id("2D Stepping");

    //     if(rangeStep>31/cm && TrackID==1)
    //     {  
            
    //         anal->FillH2(idh2,xPos/cm,yPos/cm);
    //         anal->FillH1(1,kinEn/eV);
    //     }
        // if(xPos>35*cm){
        // //     write a test histogram here as well
        // }
    //fEventAction->MaxPosition(rangeStep,TrackID);
    //if()
    //example of saving random number seed of this event, under condition
 //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

