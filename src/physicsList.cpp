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
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "physicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include <G4ParticleDefinition.hh>
#include <G4RegionStore.hh>

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"
#include "G4ProcessManager.hh"

#include "G4EmPenelopePhysics.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"

#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

physicsList::physicsList()
: G4VUserPhysicsList()
{
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

physicsList::~physicsList()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void physicsList::ConstructParticle()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
  
// gamma
  G4Gamma::GammaDefinition();
  
// leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();  

// mesons
  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();

// barions
  G4BaryonConstructor bConstructor;
  bConstructor.ConstructParticle();

// ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();


  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void physicsList::ConstructProcess()
{
  AddTransportation();
  G4StepLimiter* stepLimiter=new G4StepLimiter();
  G4EmPenelopePhysics* emPhys=new G4EmPenelopePhysics();
  emPhys->ConstructProcess();
  G4ProcessManager* pmanagerE = G4Electron::Electron()->GetProcessManager();
 
  pmanagerE->AddDiscreteProcess(stepLimiter);
  
  
  //pmanagerE->AddProcess(new G4eMultipleScattering(),-1,1,1);
  // G4eIonisation* theIonisation = new G4eIonisation(); 
  // theIonisation->SetEmModel(new G4PenelopeIonisationModel()); 
  // pmanagerE->AddProcess(theIonisation,-1,1,1);
  // G4eBremsstrahlung* bremy=new G4eBremsstrahlung();
  // bremy->SetEmModel(new G4PenelopeBremsstrahlungModel());
  // pmanagerE->AddProcess(bremy,-1,1,1);
  // G4eMultipleScattering* multiscattering=new G4eMultipleScattering();
  // pmanagerE->AddProcess(multiscattering,-1,1,1);

  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void physicsList::SetCuts()
{

// default production thresholds for the world volume
  SetCutsWithDefault();

  // Production thresholds for detector regions
//   G4Region* Perkeo;
// //   G4String regName;
//   G4ProductionCuts* cuts;
// 
// //   regName = "Perkeo";
// //   region = G4RegionStore::GetInstance()->GetRegion(regName);
//   cuts = new G4ProductionCuts;
//   cuts->SetProductionCut(0.1*mm); // same cuts for gamma, e- and e+
//   Perkeo->SetProductionCuts(cuts);

//   regName = "calorimeter";
//   region = G4RegionStore::GetInstance()->GetRegion(regName);
//   cuts = new G4ProductionCuts;
//   cuts->SetProductionCut(0.01*mm,G4ProductionCuts::GetIndex("gamma"));
//   cuts->SetProductionCut(0.1*mm,G4ProductionCuts::GetIndex("e-"));
//   cuts->SetProductionCut(0.1*mm,G4ProductionCuts::GetIndex("e+"));
//   region->SetProductionCuts(cuts);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
