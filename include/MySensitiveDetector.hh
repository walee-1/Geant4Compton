#ifndef MySensitiveDetector_h
#define MySensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"

class MySensitiveDetector : public G4VSensitiveDetector{
    public:
        MySensitiveDetector(G4String name);
        virtual ~MySensitiveDetector();

        virtual void Initialize(G4HCofThisEvent* HCE);
        virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* ROhist);

        virtual void EndOfEvent(G4HCofThisEvent*HCE);

    private:
       // MyHitsCollection* hitsCollection;
        G4int collectionID;

};

#endif