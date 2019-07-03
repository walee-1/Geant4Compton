#ifndef particle_gun_h
#define particle_gun_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
 class G4ParticleGun;
 class G4Event;

class SimpleParticleSource : public G4VUserPrimaryGeneratorAction{
	public:
	SimpleParticleSource();
	virtual ~SimpleParticleSource();
	virtual void GeneratePrimaries(G4Event*);
	
	private:
	G4ParticleGun* myGun;
};
	

#endif
