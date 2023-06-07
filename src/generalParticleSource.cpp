#include "G4SystemOfUnits.hh"
#include "generalParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "file.hh"
#include "EventAction.hh"
#include "G4SingleParticleSource.hh"
#include "ParticleSourceMessenger.hh"

generalParticleSource::generalParticleSource(): G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4GeneralParticleSource();
    fPSMessenger = new ParticleSourceMessenger(this);
}
generalParticleSource::~generalParticleSource(){
    delete particleGun;
}

void generalParticleSource::GeneratePrimaries(G4Event* event)
{

    file out("InputEn.txt",true);
    std::stringstream ss;
    G4double en=particleGun->GetParticleEnergy();
    G4double z=particleGun->GetParticlePosition().getZ();
    G4double y=particleGun->GetParticlePosition().getY();
    G4double x=particleGun->GetParticlePosition().getX();
    ss<<en/eV<<" "<<x/mm<<" "<<y/mm<<" "<<z/mm;
    out.writeToFile(ss.str());
    out.~file();
    G4AnalysisManager* anal=G4AnalysisManager::Instance();
    G4int id=anal->GetH1Id("Total Energy Deposited Per Event");
    anal->FillH1(id,en/eV);
    G4int idpos=anal->GetH2Id("Pos at emission");
    anal->FillH2(idpos,y/mm,z/mm);
    G4int idpos2=anal->GetH1Id("Pos at emission Z");
    anal->FillH1(idpos2,z/mm);
    G4int idpos3=anal->GetH1Id("Pos at emission Y");
    anal->FillH1(idpos3,y/mm);
  
    particleGun->GeneratePrimaryVertex(event);
}
//the following function does not work. Tried using it but can't seem to make it to work for now. So igore
void generalParticleSource::RotationSet(G4double phi)
{
    // G4double offsetTubex=(-50/2-165)*mm;
    // G4double offsetTubey=0*mm;
    // G4double zp = 0;
  	// G4double xp = offsetTubex*std::cos(phi);
  	// G4double yp = offsetTubey*std::cos(phi);
    // //particleGun->SetParticlePosition(G4ThreeVector(xp,yp,zp));

}