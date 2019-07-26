#include "G4SystemOfUnits.hh"
#include "generalParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

generalParticleSource::generalParticleSource(): G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4GeneralParticleSource();
}
generalParticleSource::~generalParticleSource(){
    delete particleGun;
}

void generalParticleSource::GeneratePrimaries(G4Event* event)
{
    particleGun->GeneratePrimaryVertex(event);
}