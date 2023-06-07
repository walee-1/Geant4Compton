#include "ActionInitialization.hh"

#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"
#include "generalParticleSource.hh"
#include "PhysicsList.hh"
#include "TrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  PhysicsList* phys = new PhysicsList();
  SetUserAction(new RunAction(phys));
  //SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new generalParticleSource);
  EventAction* eventAction = new EventAction;
  SetUserAction(eventAction);
  SetUserAction(new SteppingAction(eventAction));
  SetUserAction(new TrackingAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{

  PhysicsList* phys = new PhysicsList();
  SetUserAction(new RunAction(phys));
  //SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new generalParticleSource);
  EventAction* eventAction = new EventAction;
  SetUserAction(eventAction);
  SetUserAction(new SteppingAction(eventAction));
  SetUserAction(new TrackingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const
{
  return new SteppingVerbose();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
