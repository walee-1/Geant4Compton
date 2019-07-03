#ifndef N01PrimaryGeneratorAction_h
#define N01PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class N01PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
    public: 
    N01PrimaryGeneratorAction();
    ~N01PrimaryGeneratorAction();
    public:
    void GeneratePrimaries(G4Event* anEvent);

    private:
    G4ParticleGun* particleGun;

};

#endif
