#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "particle_src.hh"

GenParticleSource::GenParticleSource() : G4VUserPrimaryGeneratorAction()
{

			myGun = new G4GeneralParticleSource();
			
}

GenParticleSource::~GenParticleSource(){}

void GenParticleSource::GeneratePrimaries(G4Event* evt)
{
	myGun->GeneratePrimaryVertex(evt);
}
