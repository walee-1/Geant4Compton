#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Electron.hh"//particle sources
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "particle_gun.hh"
SimpleParticleSource::SimpleParticleSource() : G4VUserPrimaryGeneratorAction()
{

			myGun = new G4ParticleGun(1);
			//type of particles emitted
			myGun->SetParticleDefinition(G4Electron::ElectronDefinition());
			
			//set particle kinetic energy and direction of travel
			myGun->SetParticleEnergy(700*keV);
			
			myGun->SetParticlePosition(G4ThreeVector(0,0,-10*mm));
			
			//generate on instance of specified particle
			
}

SimpleParticleSource::~SimpleParticleSource(){}

void SimpleParticleSource::GeneratePrimaries(G4Event* evt)
{
	myGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));
	myGun->GeneratePrimaryVertex(evt);
}
