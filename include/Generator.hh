#ifndef GENERATOR_H
#define GENERATOR_H 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4GeneralParticleSourceMessenger.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;


class Generator : public G4VUserPrimaryGeneratorAction
{
    public:
        Generator();
        ~Generator();

    public:
        void GeneratePrimaries(G4Event* anEvent);
        void SetEnergy(G4double val);

    private:
//        G4GeneralParticleSource* gun;
        G4ParticleGun* gun;
        G4GeneralParticleSourceMessenger* gpsMess;
};
#endif
