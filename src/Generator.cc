#include "Generator.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
#include "G4GeneralParticleSourceMessenger.hh"


Generator::Generator()
{
    
    //G4int n_part = 1;// Number of particles 
    gun = new G4ParticleGun();//G4GeneralParticleSource();
//    gpsMess = new G4GeneralParticleSourceMessenger(gun);
    
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;

    gun->SetParticleDefinition(particleTable->FindParticle(particleName="proton"));
    gun->SetParticleEnergy(177.0*MeV);
    gun->SetParticlePosition(G4ThreeVector(0.0,0.0,0.0));// Can be modified later...
}

Generator::~Generator()
{
    delete gun;
}

// This would be where to introduce gaussian spread in energy I think
void Generator::GeneratePrimaries(G4Event* anEvent)
{
    gun->GeneratePrimaryVertex(anEvent);
}

void Generator::SetEnergy(G4double val)
{
    gun->SetParticleEnergy(val);
}
