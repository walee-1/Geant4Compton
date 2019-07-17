#include "N01PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4Proton.hh"

N01PrimaryGeneratorAction::N01PrimaryGeneratorAction() 
{
    G4int n_particle=1;
    particleGun=new G4ParticleGun(n_particle);

    particleGun->SetParticleDefinition(G4Electron::ElectronDefinition());
    particleGun->SetParticleEnergy(700*keV);
    particleGun->SetParticlePosition(G4ThreeVector(0,0,-100.*mm));

    // //for protons
    // particleGun->SetParticleDefinition(G4Proton::ProtonDefinition());
    // particleGun->SetParticleEnergy(15.1*keV);
    // particleGun->SetParticlePosition(G4ThreeVector(0,0,-100.*mm));

}

N01PrimaryGeneratorAction::~N01PrimaryGeneratorAction()
{
    delete particleGun;
}


void N01PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));
    particleGun->GeneratePrimaryVertex(anEvent);
}