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

    particleGun->SetParticleDefinition(G4Electron::ElectronDefinition());
<<<<<<< HEAD
    particleGun->SetParticleEnergy(700*MeV);
    particleGun->SetParticlePosition(G4ThreeVector(0,0,-10*mm));
=======

    // //for protons
    // particleGun->SetParticleDefinition(G4Proton::ProtonDefinition());


    particleGun->SetParticleEnergy(70*keV);
    particleGun->SetParticlePosition(G4ThreeVector(0,0,-100.*mm));
>>>>>>> 2cd52cef477b615c6c12ee94aa7c54be0fdc6330
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