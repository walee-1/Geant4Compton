#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <array>
#include <vector>

const G4int kDim=2;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
   ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
    
    void AddEdep(G4double Edep)     {fTotalEnergyDeposit += Edep;};      
    G4double GetEnergyDeposit()     {return fTotalEnergyDeposit;};

    void MaxPosition(G4double range);  
        
  private:
    G4double fTotalEnergyDeposit;   // Energy deposited
    G4int fHCID; //for storing the sensitive detector id
    std::array<std::vector<G4double>, kDim> fEDep; //has no purpose for now, can ignore
    std::vector<G4int> histoIDs; //just for storing histogram ids.
    G4double maxRange;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    