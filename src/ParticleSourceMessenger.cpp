//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file detectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ParticleSourceMessenger.hh"

#include "generalParticleSource.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ParticleSourceMessenger::ParticleSourceMessenger(generalParticleSource* fGPS)
:G4UImessenger(), 
 fRot(0), fTestemDir(0), fDetDir(0) 
{ 
  fTestemDir = new G4UIdirectory("/rotation/");
  fTestemDir->SetGuidance("commands specific to rotation settings");
  
  G4bool broadcast = false;
  fDetDir = new G4UIdirectory("/rotation/GPS/",broadcast);
  fDetDir->SetGuidance("Rotation of Particle Source");
        
  //For rotation
    fRot = new G4UIcmdWithADoubleAndUnit("/rotation/GPS/Rotation",this);
    fRot->SetGuidance("Set Rotation of GPS");
    fRot->SetParameterName("Rotation",false);
    //fDensityCmd->SetDefaultUnit("g/cm3");
    fRot->SetUnitCandidates("deg rad mrad sr");
    fRot->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  //
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ParticleSourceMessenger::~ParticleSourceMessenger()
{
  delete fGPS;
  delete fDetDir;
  delete fTestemDir;
  delete fRot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ParticleSourceMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  // if( command == fRot )
  //  { 
  //   fGPS->RotationSet(fRot->GetNewDoubleValue(newValue));
  //  }
   

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
