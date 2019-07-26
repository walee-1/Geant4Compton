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
#include <G4RegionStore.hh>
#include "G4SystemOfUnits.hh"

#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>



#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4EmProcessOptions.hh"


#include "G4EmPenelopePhysics.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBetheBlochModel.hh"
#include "G4PhysicsListHelper.hh"
#include "G4hPairProduction.hh"
#include "G4hBremsstrahlung.hh"




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
  
// gamma
  G4Gamma::GammaDefinition();
  
// leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();


// Protons
  G4Proton::ProtonDefinition();


//baryon constructor //to avoid warnings
  G4BaryonConstructor bConsctructor;
  bConsctructor.ConstructParticle();

//meson constructor, used only to avoid warnings as before
  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();
  


// ions - need this for obvious reasons
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

  auto theParticleIterator = GetParticleIterator();
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  // 
 
  theParticleIterator->reset();
  while((*theParticleIterator)())
  {

    G4ParticleDefinition* particle = theParticleIterator->value();

    
    G4ProcessManager* pmanager = particle->GetProcessManager();
    pmanager->AddDiscreteProcess(stepLimiter);
    G4String particleName = particle->GetParticleName();


    //For using a particle GUn
    //for electrons

   // G4ProcessManager* pmanager = G4Electron::Electron()->GetProcessManager();

    // //for protons

    //G4ProcessManager* pmanager = G4Proton::Proton()->GetProcessManager(); //in case of protons


   
     
    if (particleName == "e-") {
      
        ph->RegisterProcess(new G4eMultipleScattering(), particle);            
        G4eIonisation* eIoni = new G4eIonisation();
        eIoni->SetStepFunction(0.1, 10*nm);      
        ph->RegisterProcess(eIoni, particle);
        ph->RegisterProcess(new G4eBremsstrahlung(), particle); 
        //pmanager->AddProcess(new G4SecondaryElectronEmission, -1, -1, 1);
        //pmanager->AddProcess(new G4SynchrotronRadiation,      -1,-1, 4);
        //pmanager->AddProcess(new G4SynchrotronRadiationInMat, -1,-1, 4); 
        //ph->RegisterProcess(new G4SecondaryElectronEmission(), particle); 
                          
    } else if( particleName == "proton" ||
                particleName == "pi-" ||
                particleName == "pi+"    ) {

        ph->RegisterProcess(new G4hMultipleScattering(), particle);      
        G4hIonisation* hIoni = new G4hIonisation();
        hIoni->SetStepFunction(0.1, 20*nm);
        ph->RegisterProcess(hIoni, particle);
        ph->RegisterProcess(new G4hBremsstrahlung(), particle);
        ph->RegisterProcess(new G4hPairProduction(), particle);
        //pmanager->AddProcess(new G4SynchrotronRadiation,      -1,-1, 4);
        //pmanager->AddProcess(new G4SynchrotronRadiationInMat, -1,-1, 4); 
     }
    
  }
  

  
  //emOptions.SetMscStepLimitation(fUseDistanceToBoundary); //uncommenting this causes segementation errors for now, have to look into it.


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void physicsList::SetCuts()
{
  G4EmProcessOptions emOptions;
  emOptions.SetMinEnergy(10*eV);
  emOptions.SetMaxEnergy(1*TeV); 
  //Setting this to <1MeV causes segmentation errors
  emOptions.SetDEDXBinning(12*15);
  emOptions.SetLambdaBinning(12*15);


  // default production thresholds for the world volume
  //SetCutsWithDefault();
  //set different than default thresholds for the world volume
  //G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(10*eV,1*MeV);
  //SetCutValue(10*nm,"e-");
  
  //go over each region as defined in detector.cpp and assign different cuts according to your requirement.
  // G4Region* region;
  // G4String regName;
  // G4ProductionCuts* cuts;

  // regName="detectorSi";
  // region=G4RegionStore::GetInstance()->GetRegion(regName); 
  // cuts= new G4ProductionCuts;
  // cuts->SetProductionCut(1*um); //changed from 0.1 um to 5nm for protons, change it back once done
  // region->SetProductionCuts(cuts);

  // regName="detectorAl";
  // region=G4RegionStore::GetInstance()->GetRegion(regName); 
  // cuts= new G4ProductionCuts;
  // cuts->SetProductionCut(100*nm);//this has a direct impact on the speed of calculation and how many steps are displayed later on
  // region->SetProductionCuts(cuts);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
