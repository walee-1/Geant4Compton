#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsListMessenger;
class G4VPhysicsConstructor;
class StepMax;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList
{
  public:
    PhysicsList();
   ~PhysicsList();
   
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    
    void AddPhysicsList(const G4String& name);
    void AddStepMax();
    StepMax* GetStepMaxProcess() {return fStepMaxProcess;}
    virtual void SetCuts();
      
  private:
    G4VPhysicsConstructor*  fEmPhysicsList;
    G4String                fEmName;
    
    PhysicsListMessenger*   fMessenger;
    StepMax* fStepMaxProcess;         
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif