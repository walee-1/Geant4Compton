#ifndef detectorMessenger_h
#define detectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorGeom;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class detectorMessenger: public G4UImessenger
{
  public:
  
    detectorMessenger(DetectorGeom* );
   ~detectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);
   
    
  private:
    //  fDetector(Det), fTestemDir(0), fDetDir(0), fDensityCmd(0), fPressureCmd(0),
    //  fTemperatureCmd(0), fgasCmd(0)
    DetectorGeom*      fDetector;
    
    G4UIdirectory*             fTestemDir;
    G4UIdirectory*             fDetDir;
    G4UIcmdWithADoubleAndUnit* fDensityCmd;
    G4UIcmdWithADoubleAndUnit* fPressureCmd;
    G4UIcmdWithADoubleAndUnit* fTemperatureCmd;
    G4UIcmdWithADoubleAndUnit* fOffsetCmd;
    G4UIcommand* fgasCmd;

    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif

