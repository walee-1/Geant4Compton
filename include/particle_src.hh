#ifndef particle_src_h
#define particle_src_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
 class G4GeneralParticleSource;
 class G4Event;

class GenParticleSource : public G4VUserPrimaryGeneratorAction{
	public:
	GenParticleSource();
	virtual ~GenParticleSource();
	virtual void GeneratePrimaries(G4Event*);
	
	private:
	G4GeneralParticleSource* myGun;
};
	

#endif
