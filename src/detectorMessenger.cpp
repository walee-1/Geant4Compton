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

#include "detectorMessenger.hh"

#include "detector.hh"
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

detectorMessenger::detectorMessenger(DetectorGeom* Det)
:G4UImessenger(), 
 fDetector(Det), fTestemDir(0), fDetDir(0), fDensityCmd(0), fPressureCmd(0),
 fTemperatureCmd(0), fgasCmd(0)
{ 
  fTestemDir = new G4UIdirectory("/vacuumSettings/");
  fTestemDir->SetGuidance("commands specific to vacuum settings");
  
  G4bool broadcast = false;
  fDetDir = new G4UIdirectory("/vacuumSettings/det/",broadcast);
  fDetDir->SetGuidance("detector construction commands");
        
  //For Density Set
    fDensityCmd = new G4UIcmdWithADoubleAndUnit("/vacuumSettings/det/setDensity",this);
    fDensityCmd->SetGuidance("Set Density");
    fDensityCmd->SetParameterName("Density",false);
    fDensityCmd->SetRange("Density>0.");
    //fDensityCmd->SetDefaultUnit("g/cm3");
    fDensityCmd->SetUnitCandidates("g/cm3 kg/m3 kg/cm3 g/m3");
    fDensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //For Pressure Set
    fPressureCmd = new G4UIcmdWithADoubleAndUnit("/vacuumSettings/det/setPressure",this);
    fPressureCmd->SetGuidance("Set Pressure");
    fPressureCmd->SetParameterName("Pressure",false);
    fPressureCmd->SetRange("Pressure>0.");
    fPressureCmd->SetDefaultUnit("bar");
    fPressureCmd->SetUnitCandidates("pascal bar atmosphere");
    fPressureCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //For Temperature Set
    fTemperatureCmd = new G4UIcmdWithADoubleAndUnit("/vacuumSettings/det/setTemperature",this);
    fTemperatureCmd->SetGuidance("Set Temperature");
    fTemperatureCmd->SetParameterName("Temperature",false);
    fTemperatureCmd->SetRange("Temperature>0.");
    fTemperatureCmd->SetDefaultUnit("kelvin");
    fTemperatureCmd->SetUnitCandidates("kelvin");
    fTemperatureCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //FOR All3 Pressure Density and TempSET
    fgasCmd = new G4UIcommand("/vacuumSettings/det/setGas",this);
    fgasCmd->SetGuidance("Set density, pressure and temperature of gas at once");
    fgasCmd->SetGuidance("density unit pressure unit temp unit");


    G4UIparameter* denPrm= new G4UIparameter("density",'d',false);
    denPrm->SetParameterRange("density>0");
    fgasCmd->SetParameter(denPrm);
    G4UIparameter* denUnt= new G4UIparameter("denUnt",'s',false);
    denUnt->SetGuidance("unit of density");
    G4String unitList = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("g/cm3"));
    denUnt->SetParameterCandidates(unitList);
    fgasCmd->SetParameter(denUnt);



    G4UIparameter* prePrm= new G4UIparameter("pressure",'d',false);
    prePrm->SetParameterRange("pressure>0");
    fgasCmd->SetParameter(prePrm);
    G4UIparameter* preUnt= new G4UIparameter("preUnt",'s',false);
    preUnt->SetGuidance("unit of pressure");
    G4String unitListpre = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("bar"));
    preUnt->SetParameterCandidates(unitListpre);
    fgasCmd->SetParameter(preUnt);

    G4UIparameter* temPrm= new G4UIparameter("temp",'d',false);
    temPrm->SetParameterRange("temp>0");
    fgasCmd->SetParameter(temPrm);
    G4UIparameter* temUnt= new G4UIparameter("temUnt",'s',false);
    temUnt->SetGuidance("unit of temperature");
    G4String unitListtem = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("kelvin"));
    temUnt->SetParameterCandidates(unitListtem);
    fgasCmd->SetParameter(temUnt);


    fgasCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fgasCmd->SetToBeBroadcasted(false);


    //For Offset setting
    fOffsetCmd = new G4UIcmdWithADoubleAndUnit("/vacuumSettings/det/setYOffset",this);
    fOffsetCmd->SetGuidance("Set Offset in Y");
    fOffsetCmd->SetParameterName("yOffset",false);
    fOffsetCmd->SetUnitCandidates("mm cm m");
    fOffsetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

detectorMessenger::~detectorMessenger()
{
  delete fTemperatureCmd;
  delete fDensityCmd;
  delete fPressureCmd;
  delete fDetDir;
  delete fTestemDir;
  delete fgasCmd;
  delete fOffsetCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void detectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == fDensityCmd )
   { 
    fDetector->DensitySet(fDensityCmd->GetNewDoubleValue(newValue));
   }
   
  if( command == fTemperatureCmd )
   { fDetector->TemperatureSet(fTemperatureCmd->GetNewDoubleValue(newValue));}
  if( command == fPressureCmd )
   { fDetector->PressureSet(fPressureCmd->GetNewDoubleValue(newValue));}
  if (command == fgasCmd)
   {
     G4double dens, pres, temp;
     G4String densU, presU, tempU;
     std::istringstream is(newValue);
     is >> dens >> densU >> pres >> presU >> temp >> tempU;
     dens *= G4UIcommand::ValueOf(densU);
     pres *=G4UIcommand::ValueOf(presU);
     temp *=G4UIcommand::ValueOf(tempU);
     fDetector->gasPropSet(dens,pres,temp);   
   }
   if (command == fOffsetCmd)
   {
      fDetector->setYOffset(fOffsetCmd->GetNewDoubleValue(newValue));
   }   

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
