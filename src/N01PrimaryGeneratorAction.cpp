#include "N01PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


N01PrimaryGeneratorAction::N01PrimaryGeneratorAction() 
{
    G4int n_particle=1;
    particleGun=new G4ParticleGun(n_particle);

    particleGun->SetParticleDefinition(G4Electron::ElectronDefinition());
    particleGun->SetParticleEnergy(700*MeV);
    particleGun->SetParticlePosition(G4ThreeVector(0,0,-10*mm));
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));
}

N01PrimaryGeneratorAction::~N01PrimaryGeneratorAction()
{
    delete particleGun;
}


void N01PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    
    particleGun->GeneratePrimaryVertex(anEvent);
}