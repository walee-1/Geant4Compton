#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Electron.hh"//particle sources
#include "G4Proton.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "particle_gun.hh"
#include <stdlib.h> 
#include <time.h> 

SimpleParticleSource::SimpleParticleSource() : G4VUserPrimaryGeneratorAction()
{

			myGun = new G4ParticleGun(1);
			//type of particles emitted
			myGun->SetParticleDefinition(G4Electron::ElectronDefinition());
			//myGun->SetParticleDefinition(G4Proton::ProtonDefinition());


			//set particle kinetic energy and direction of travel
			myGun->SetParticleEnergy(2*MeV);

			//srand(time(0));
			//G4float randx=rand()/RAND_MAX+1;
			//G4float randy=rand()/RAND_MAX+1;
			myGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));

			myGun->SetParticlePosition(G4ThreeVector(0,0,-10*mm));
			
			//generate on instance of specified particle
			
}

SimpleParticleSource::~SimpleParticleSource(){}

void SimpleParticleSource::GeneratePrimaries(G4Event* evt)
{
	myGun->GeneratePrimaryVertex(evt);
}
