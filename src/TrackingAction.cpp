#include "TrackingAction.hh"

//#include "Run.hh"
#include "EventAction.hh"
#include "file.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4StepStatus.hh"
#include "G4ParticleTypes.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


TrackingAction::TrackingAction(EventAction* event):
G4UserTrackingAction(), fEventAction(event)
{  }
void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
}

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
    // G4int trackID=track->GetTrackID();
//     const G4ParticleDefinition* particle=track->GetParticleDefinition();
    // G4AnalysisManager* anal=G4AnalysisManager::Instance();
// //    G4String name = particle->GetParticleName;
//  //   G4double energy= track->GetKineticEnergy;

//     G4int idh2=anal->GetH2Id("2D Tracking");
//     G4int id=anal->GetH1Id("Maximum Range Histogram");

//     if (trackID>1) return;
//         G4double z=track->GetStep()->GetPostStepPoint()->GetPosition().z()/cm;


    
//         if (z<31./cm) return;
//         if((track->GetVolume() == NULL) || (track->GetVolume()->GetName() == "World")) return;
//         file out("output.txt",true);
//         G4double x=track->GetStep()->GetPostStepPoint()->GetPosition().x()/cm;
//         G4double y=track->GetStep()->GetPostStepPoint()->GetPosition().y()/cm;
//          G4double z2=track->GetStep()->GetPostStepPoint()->GetPosition().z()/cm;
//         G4double en=track->GetStep()->GetPostStepPoint()->GetKineticEnergy()/keV;
//         G4double en2=track->GetStep()->GetPostStepPoint()->GetTotalEnergy()/keV;
//         std::stringstream ss;
//         ss<<x<<" "<<y<<" "<<z2<<" "<<en<<" "<<en2;
//         out.writeToFile(ss.str());
//         out.~file();
//         anal->FillH2(idh2,x,y);
//         anal->FillH1(id,z2);

//         anal->FillH1(id,en2/eV);
//fill histograms here
//fill eneergy histogram here as well?
}

