#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "globals.hh"
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
 auto Track=aStep->GetTrack();
 G4int TrackID=Track->GetTrackID();

 G4double EdepStep = aStep->GetTotalEnergyDeposit();
 if (EdepStep > 0.) fEventAction->AddEdep(EdepStep);

 G4StepPoint* rangePoint;
 rangePoint = aStep->GetPostStepPoint();
 G4ThreeVector rangeThreeVector= rangePoint->GetPosition();
 G4double rangeStep= rangeThreeVector.getZ();
 fEventAction->MaxPosition(rangeStep,TrackID);
 //if()
 //example of saving random number seed of this event, under condition
 //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

