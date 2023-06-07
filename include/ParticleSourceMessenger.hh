#ifndef ParticleSourceMessenger_h
#define ParticleSourceMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class generalParticleSource;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ParticleSourceMessenger: public G4UImessenger
{
  public:
  
    ParticleSourceMessenger(generalParticleSource* );
   ~ParticleSourceMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);
   
    
  private:
  
    generalParticleSource*      fGPS;
    
    G4UIdirectory*             fTestemDir;
    G4UIdirectory*             fDetDir;
    G4UIcmdWithADoubleAndUnit* fRot;

    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

