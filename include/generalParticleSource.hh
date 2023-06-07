#ifndef generalParticleSource_h
#define generalParticleSource_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
class ParticleSourceMessenger;
class DetectorGeom;
class generalParticleSource;
class G4Event;

class generalParticleSource : public G4VUserPrimaryGeneratorAction{
    public:
        generalParticleSource();
        virtual ~generalParticleSource();
        virtual void GeneratePrimaries(G4Event*);
        virtual void RotationSet(G4double);

        private:
            G4GeneralParticleSource* particleGun;
            ParticleSourceMessenger* fPSMessenger;
                   const DetectorGeom* detector;
};



#endif