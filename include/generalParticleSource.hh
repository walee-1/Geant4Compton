#ifndef generalParticleSource_h
#define generalParticleSource_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class generalParticleSource;
class G4Event;

class generalParticleSource : public G4VUserPrimaryGeneratorAction{
    public:
        generalParticleSource();
        virtual ~generalParticleSource();
        virtual void GeneratePrimaries(G4Event*);

        private:
            G4GeneralParticleSource* particleGun;
};



#endif