#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4Proton.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() 
{
    G4int n_particle=1;
    particleGun=new G4ParticleGun(n_particle);

    // particleGun->SetParticleDefinition(G4Electron::ElectronDefinition());

    // //for protons
    particleGun->SetParticleDefinition(G4Proton::ProtonDefinition());


    particleGun->SetParticleEnergy(15*keV);
    particleGun->SetParticlePosition(G4ThreeVector(0,0,-100.*mm));
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));
    particleGun->GeneratePrimaryVertex(anEvent);
}